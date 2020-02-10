//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		iOS�p�T�E���h�v���O����
// 
//  	Ver 3.21d
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_SOUND

// �C���N���[�h----------------------------------------------------------------
#include "DxSoundHTML5.h"
#include "DxFileHTML5.h"
#include "DxSystemHTML5.h"
#include "../DxSound.h"
#include "../DxSystem.h"
#include "../DxMemory.h"
#include "../DxLog.h"
#include <unistd.h>
#include <sched.h>
#include <pthread.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����`------------------------------------------------------------------

// �X�g���[���Đ��p�̃o�b�t�@��ӂ�̃T���v����
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(512)
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(735)
#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(1024)
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(2048)
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES  (3072)
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(4096)
//#define STREAM_SOUND_BUFFER_UNIT_SAPMLES	(8192)

// �j���˗��������Ă�����ۂɔj������܂ł̎���
#define SOUND_RELEASE_WAIT		(200)

// �^��`----------------------------------------------------------------------

// typedef ALvoid AL_APIENTRY ( *alBufferDataStaticProcPtr )( const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq ) ;
// static alBufferDataStaticProcPtr alBufferDataStaticProc ;

// �f�[�^�錾------------------------------------------------------------------

// 8bit�g�`��16bit�g�`�ɕϊ����邽�߂̃e�[�u��
static short Bit8To16Table[ 256 ] ;

// �����f�[�^
static BYTE g_NoneSound8bit[  STREAM_SOUND_BUFFER_UNIT_SAPMLES ] ;
static WORD g_NoneSound16bit[ STREAM_SOUND_BUFFER_UNIT_SAPMLES ] ;

// �֐��v���g�^�C�v�錾 -------------------------------------------------------

static void SetupSoundBuffer( SOUNDBUFFER *Buffer, int *IsNext, int TargetBuffer ) ;	// �T�E���h�o�b�t�@�Ƀf�[�^���Z�b�g����
static void SourceQueueSoundBuffer( SOUNDBUFFER *Buffer ) ;							// AL�o�b�t�@��AL�\�[�X�ɒǉ�����
static void *StreamSoundThreadFunction( void *argc ) ;

static void SoundBuffer_Add_StopSoundBufferList( SOUNDBUFFER *Buffer ) ;			// ��~�҂��T�E���h�o�b�t�@���X�g�Ɏw��̃T�E���h�o�b�t�@��������
static void SoundBuffer_Sub_StopSoundBufferList( SOUNDBUFFER *Buffer ) ;			// ��~�҂��T�E���h�o�b�t�@���X�g����w��̃T�E���h�o�b�t�@���O��

static void SoundBuffer_Add_PlaySoundBufferList( SOUNDBUFFER *Buffer ) ;			// �Đ����T�E���h�o�b�t�@���X�g�Ɏw��̃T�E���h�o�b�t�@��������
static void SoundBuffer_Sub_PlaySoundBufferList( SOUNDBUFFER *Buffer ) ;			// �Đ����T�E���h�o�b�t�@���X�g����w��̃T�E���h�o�b�t�@���O��

static int SoundReleaseInfo_Initialize( void ) ;									// AL���\�[�X��������̏�����
static int SoundReleaseInfo_Terminate( void ) ;										// AL���\�[�X��������̌�n��
static int SoundReleaseInfo_Process( void ) ;										// AL���\�[�X��������̖��t���[���s������
static int SoundReleaseInfo_Add( SOUNDBUFFER *Buffer ) ;							// AL���\�[�X������X�g�ɒǉ�

// �v���O����------------------------------------------------------------------

// �f�V�x���l���� XAudio2 �̗��l�ɕϊ�����֐�
__inline float D_XAudio2DecibelsToAmplitudeRatio( float Decibels )
{
    return _POW( 10.0f, Decibels / 20.0f ) ;
}

// �T�E���h�o�b�t�@�Ƀf�[�^���Z�b�g����
static void SetupSoundBuffer( SOUNDBUFFER *Buffer, int *IsNext, int TargetBuffer )
{
	int CompPos = Buffer->CompPos ;
	int Loop    = Buffer->Loop ;
	DWORD BufferSetSamples ;
	DWORD SamplePerBytes ;
	void *SrcBuffer ;

	SrcBuffer = Buffer->Wave->DoubleSizeBuffer ? Buffer->Wave->DoubleSizeBuffer : Buffer->Wave->Buffer ;
	SamplePerBytes = Buffer->Format.nChannels * Buffer->Format.wBitsPerSample / 8 ;

	BufferSetSamples = 0 ;
	while( BufferSetSamples < STREAM_SOUND_BUFFER_UNIT_SAPMLES )
	{
		if( CompPos >= Buffer->SampleNum )
		{
			if( Loop )
			{
				CompPos = 0 ;
				goto COPYDATA ;
			}
			else
			{
				break ;
			}
		}
		else
		{
			DWORD CopySamples ;

COPYDATA :
			CopySamples = ( DWORD )( Buffer->SampleNum - CompPos ) ;
			if( CopySamples > STREAM_SOUND_BUFFER_UNIT_SAPMLES - BufferSetSamples )
			{
				CopySamples = STREAM_SOUND_BUFFER_UNIT_SAPMLES - BufferSetSamples ;
			}

			_MEMCPY(
				( BYTE * )Buffer->PF.ALBufferImage[ TargetBuffer ] + BufferSetSamples * SamplePerBytes,
				( BYTE * )SrcBuffer                                + CompPos          * SamplePerBytes,
				CopySamples * SamplePerBytes
			) ;

			CompPos          += CopySamples ;
			BufferSetSamples += CopySamples ;
		}
	}
	Buffer->CompPos = CompPos ;

	Buffer->PF.ALBufferValidBytes[ TargetBuffer ] = BufferSetSamples * SamplePerBytes ;
	Buffer->PF.ALBufferEndPos[ TargetBuffer ] = Buffer->CompPos ;

	if( Loop == FALSE && Buffer->SampleNum == Buffer->CompPos )
	{
		*IsNext = FALSE ;
	}
	else
	{
		*IsNext = TRUE ;
	}
}

// ��~�҂��T�E���h�o�b�t�@���X�g�Ɏw��̃T�E���h�o�b�t�@��������
static void SoundBuffer_Add_StopSoundBufferList( SOUNDBUFFER *Buffer )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;

	// ���X�g�ɒǉ�
	if( Buffer->PF.StopSoundBufferValid == FALSE )
	{
		Buffer->PF.StopSoundBufferValid = TRUE ;

		Buffer->PF.StopSoundBufferPrev = NULL ;
		Buffer->PF.StopSoundBufferNext = SoundSysData.PF.StopSoundBuffer ;
		if( SoundSysData.PF.StopSoundBuffer != NULL )
		{
			SoundSysData.PF.StopSoundBuffer->PF.StopSoundBufferPrev = Buffer ;
		}
		SoundSysData.PF.StopSoundBuffer = Buffer ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;
}

// ��~�҂��T�E���h�o�b�t�@���X�g����w��̃T�E���h�o�b�t�@���O��
static void SoundBuffer_Sub_StopSoundBufferList( SOUNDBUFFER *Buffer )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;

	if( Buffer->PF.StopSoundBufferValid )
	{
		Buffer->PF.StopSoundBufferValid = FALSE ;

		if( Buffer->PF.StopSoundBufferNext != NULL )
		{
			Buffer->PF.StopSoundBufferNext->PF.StopSoundBufferPrev = Buffer->PF.StopSoundBufferPrev ;
		}

		if( Buffer->PF.StopSoundBufferPrev != NULL )
		{
			Buffer->PF.StopSoundBufferPrev->PF.StopSoundBufferNext = Buffer->PF.StopSoundBufferNext ;
		}
		else
		{
			SoundSysData.PF.StopSoundBuffer = Buffer->PF.StopSoundBufferNext ;
		}

		Buffer->PF.StopSoundBufferNext = NULL ;
		Buffer->PF.StopSoundBufferPrev = NULL ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;
}

// ��~�҂��T�E���h�o�b�t�@���X�g�ɓo�^����Ă���T�E���h�o�b�t�@���~����
extern void SoundBuffer_Apply_StopSoundBufferList( void )
{
	for(;;)
	{
		SOUNDBUFFER *StopSoundBuffer = NULL ;

		// �N���e�B�J���Z�N�V�����̎擾
		CRITICALSECTION_LOCK( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;

		StopSoundBuffer = SoundSysData.PF.StopSoundBuffer ;

		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;

		// �o�^����Ă���T�E���h�o�b�t�@��������ΏI��
		if( StopSoundBuffer == NULL )
		{
			break ;
		}

		// �Đ��̒�~
		SoundBuffer_Stop( StopSoundBuffer ) ;
	}

}

// �Đ����T�E���h�o�b�t�@���X�g�Ɏw��̃T�E���h�o�b�t�@��������
static void SoundBuffer_Add_PlaySoundBufferList( SOUNDBUFFER *Buffer )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.PlaySoundBufferCriticalSection ) ;

	// ���X�g�ɒǉ�
	if( Buffer->PF.PlaySoundBufferValid == FALSE )
	{
		Buffer->PF.PlaySoundBufferValid = TRUE ;

		Buffer->PF.PlaySoundBufferPrev = NULL ;
		Buffer->PF.PlaySoundBufferNext = SoundSysData.PF.PlaySoundBuffer ;
		if( SoundSysData.PF.PlaySoundBuffer != NULL )
		{
			SoundSysData.PF.PlaySoundBuffer->PF.PlaySoundBufferPrev = Buffer ;
		}
		SoundSysData.PF.PlaySoundBuffer = Buffer ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.PlaySoundBufferCriticalSection ) ;
}

// �Đ����T�E���h�o�b�t�@���X�g����w��̃T�E���h�o�b�t�@���O��
static void SoundBuffer_Sub_PlaySoundBufferList( SOUNDBUFFER *Buffer )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.PlaySoundBufferCriticalSection ) ;

	if( Buffer->PF.PlaySoundBufferValid )
	{
		Buffer->PF.PlaySoundBufferValid = FALSE ;

		if( Buffer->PF.PlaySoundBufferNext != NULL )
		{
			Buffer->PF.PlaySoundBufferNext->PF.PlaySoundBufferPrev = Buffer->PF.PlaySoundBufferPrev ;
		}

		if( Buffer->PF.PlaySoundBufferPrev != NULL )
		{
			Buffer->PF.PlaySoundBufferPrev->PF.PlaySoundBufferNext = Buffer->PF.PlaySoundBufferNext ;
		}
		else
		{
			SoundSysData.PF.PlaySoundBuffer = Buffer->PF.PlaySoundBufferNext ;
		}

		Buffer->PF.PlaySoundBufferNext = NULL ;
		Buffer->PF.PlaySoundBufferPrev = NULL ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.PlaySoundBufferCriticalSection ) ;
}

// AL���\�[�X��������̏�����
static int SoundReleaseInfo_Initialize( void )
{
	// ���ɏ������ς݂̏ꍇ�͉��������ɏI��
	if( SoundSysData.PF.SoundReleaseInitialize )
	{
		return 0 ;
	}

	// �N���e�B�J���Z�N�V������������
	if( CriticalSection_Initialize( &SoundSysData.PF.SoundReleaseCriticalSection ) < 0 )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x41\x00\x4c\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xea\x30\xbd\x30\xfc\x30\xb9\x30\xe3\x89\x3e\x65\xe6\x51\x06\x74\x28\x75\x6e\x30\xaf\x30\xea\x30\xc6\x30\xa3\x30\xab\x30\xeb\x30\xbb\x30\xaf\x30\xb7\x30\xe7\x30\xf3\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenAL �̃T�E���h���\�[�X��������p�̃N���e�B�J���Z�N�V�����̍쐬�Ɏ��s���܂���\n" @*/ )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// �T�E���h�j�������p�̃��������m��
	SoundSysData.PF.SoundReleaseInfoMaxNum = 256 ;
	SoundSysData.PF.SoundReleaseInfoNum = 0 ;
	SoundSysData.PF.SoundReleaseInfo = ( SOUNDRELEASE_INFO * )DXCALLOC( SoundSysData.PF.SoundReleaseInfoMaxNum * sizeof( SOUNDRELEASE_INFO ) ) ;
	if( SoundSysData.PF.SoundReleaseInfo == NULL )
	{
		// �T�E���h�j�������p�̃N���e�B�J���Z�N�V�������폜
		CriticalSection_Delete( &SoundSysData.PF.SoundReleaseCriticalSection ) ;

		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x41\x00\x4c\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xea\x30\xbd\x30\xfc\x30\xb9\x30\xe3\x89\x3e\x65\xe6\x51\x06\x74\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenAL �̃T�E���h���\�[�X��������p�̃������m�ۂɎ��s���܂���\n" @*/ )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// ���̑��̏���������
	SoundSysData.PF.SoundReleaseInfoFirstIndex = -1 ;
	SoundSysData.PF.SoundReleaseInfoNextUseIndex = 0 ;

	// �������t���O�𗧂Ă�
	SoundSysData.PF.SoundReleaseInitialize = TRUE ;

	// ����I��
	return 0 ;
}

// AL���\�[�X��������̌�n��
static int SoundReleaseInfo_Terminate( void )
{
	int ind ;

	// ����������Ă��Ȃ������牽�����Ȃ�
	if( SoundSysData.PF.SoundReleaseInitialize == FALSE )
	{
		return 0 ;
	}

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.SoundReleaseCriticalSection ) ;

	// �j���\��̃T�E���h�����ׂč폜����
	for( ind = SoundSysData.PF.SoundReleaseInfoFirstIndex ; ind != -1 ; ind = SoundSysData.PF.SoundReleaseInfo[ ind ].NextIndex )
	{
		// AL�\�[�X���폜
		if( SoundSysData.PF.SoundReleaseInfo[ ind ].ALSource != 0 )
		{
			alSourceStop( SoundSysData.PF.SoundReleaseInfo[ ind ].ALSource ) ;
			alDeleteSources( 1, &SoundSysData.PF.SoundReleaseInfo[ ind ].ALSource ) ;
			SoundSysData.PF.SoundReleaseInfo[ ind ].ALSource = 0 ;
		}

		// AL�o�b�t�@���폜
		if( SoundSysData.PF.SoundReleaseInfo[ ind ].ALBuffer[ 0 ] != 0 )
		{
			alDeleteBuffers( SOUNDSOURCE_BUFFER_NUM, SoundSysData.PF.SoundReleaseInfo[ ind ].ALBuffer );
			_MEMSET( SoundSysData.PF.SoundReleaseInfo[ ind ].ALBuffer, 0, sizeof( SoundSysData.PF.SoundReleaseInfo[ ind ].ALBuffer ) ) ;
		}

		// �g�p���t���O��|��
		SoundSysData.PF.SoundReleaseInfo[ ind ].UseFlag = FALSE ;
	}

	// �T�E���h�j�������p�Ɋm�ۂ��Ă������������������
	DXFREE( SoundSysData.PF.SoundReleaseInfo ) ;
	SoundSysData.PF.SoundReleaseInfo = NULL ;

	// �������t���O��|��
	SoundSysData.PF.SoundReleaseInitialize = FALSE ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.SoundReleaseCriticalSection ) ;

	// �T�E���h�j�������p�̃N���e�B�J���Z�N�V�������폜
	CriticalSection_Delete( &SoundSysData.PF.SoundReleaseCriticalSection ) ;

	// ����I��
	return 0 ;
}

// AL���\�[�X��������̖��t���[���s������
static int SoundReleaseInfo_Process( void )
{
	int NowTime ;
	int prev_ind ;
	int ind ;

	// ���݂̎��Ԃ��擾
	NowTime = NS_GetNowCount() ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.SoundReleaseCriticalSection ) ;

	// �j������O�ɑ҂��Ԃ��o�߂��Ă���T�E���h�����邩�m�F����
	prev_ind = -1 ;
	for( ind = SoundSysData.PF.SoundReleaseInfoFirstIndex ; ind != -1 && SoundSysData.PF.SoundReleaseInfo[ ind ].ReleaseTime + SOUND_RELEASE_WAIT > NowTime ; ind = SoundSysData.PF.SoundReleaseInfo[ ind ].NextIndex )
	{
		prev_ind = ind ;
	}

	// �j�����ׂ��T�E���h�������ꍇ�͉��������ɏI��
	if( ind == -1 )
	{
		return 0 ;
	}

	// �j�����ׂ��T�E���h�����X�g����O��
	if( ind == SoundSysData.PF.SoundReleaseInfoFirstIndex )
	{
		SoundSysData.PF.SoundReleaseInfoFirstIndex = -1 ;
	}
	else
	if( prev_ind != -1 )
	{
		SoundSysData.PF.SoundReleaseInfo[ prev_ind ].NextIndex = -1 ;
	}

	// �j�����ׂ��T�E���h��j������
	for( ; ind != -1 ; ind = SoundSysData.PF.SoundReleaseInfo[ ind ].NextIndex )
	{
		// AL�\�[�X���폜
		if( SoundSysData.PF.SoundReleaseInfo[ ind ].ALSource != 0 )
		{
			alSourceStop( SoundSysData.PF.SoundReleaseInfo[ ind ].ALSource ) ;
			alDeleteSources( 1, &SoundSysData.PF.SoundReleaseInfo[ ind ].ALSource ) ;
			SoundSysData.PF.SoundReleaseInfo[ ind ].ALSource = 0 ;
		}

		// AL�o�b�t�@���폜
		if( SoundSysData.PF.SoundReleaseInfo[ ind ].ALBuffer[ 0 ] != 0 )
		{
			alDeleteBuffers( SOUNDSOURCE_BUFFER_NUM, SoundSysData.PF.SoundReleaseInfo[ ind ].ALBuffer );
			_MEMSET( SoundSysData.PF.SoundReleaseInfo[ ind ].ALBuffer, 0, sizeof( SoundSysData.PF.SoundReleaseInfo[ ind ].ALBuffer ) ) ;
		}

		// �g�p���t���O��|��
		SoundSysData.PF.SoundReleaseInfo[ ind ].UseFlag = FALSE ;

		// �j�����̐������炷
		SoundSysData.PF.SoundReleaseInfoNum -- ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.SoundReleaseCriticalSection ) ;

	// ����I��
	return 0 ;
}

// AL���\�[�X������X�g�ɒǉ�
static int SoundReleaseInfo_Add( SOUNDBUFFER *Buffer )
{
	int ind ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.SoundReleaseCriticalSection ) ;

	// ���ɐ����ő吔�ɒB���Ă�����o�b�t�@��傫������
	if( SoundSysData.PF.SoundReleaseInfoNum >= SoundSysData.PF.SoundReleaseInfoMaxNum )
	{
		int OldMaxNum = SoundSysData.PF.SoundReleaseInfoMaxNum ;

		SoundSysData.PF.SoundReleaseInfoMaxNum *= 2 ;
		SoundSysData.PF.SoundReleaseInfo = ( SOUNDRELEASE_INFO * )DXREALLOC( SoundSysData.PF.SoundReleaseInfo, sizeof( SOUNDRELEASE_INFO ) * SoundSysData.PF.SoundReleaseInfoMaxNum ) ;
		if( SoundSysData.PF.SoundReleaseInfo == NULL )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xb5\x30\xa6\x30\xf3\x30\xc9\x30\x34\x78\xc4\x68\xe6\x51\x06\x74\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\x18\x98\xdf\x57\x6e\x30\xe1\x62\x35\x5f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�E���h�j�������p�̃������̈�̊g���Ɏ��s���܂���\n" @*/ )) ;

			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &SoundSysData.PF.SoundReleaseCriticalSection ) ;

			return -1 ;
		}

		// �g�����̃�������������
		_MEMSET( SoundSysData.PF.SoundReleaseInfo + OldMaxNum, 0, sizeof( SOUNDRELEASE_INFO ) * ( SoundSysData.PF.SoundReleaseInfoMaxNum - OldMaxNum ) ) ;
	}

	// �g�p����Ă��Ȃ��v�f��T��
	ind = SoundSysData.PF.SoundReleaseInfoNextUseIndex ;
	while( SoundSysData.PF.SoundReleaseInfo[ ind ].UseFlag )
	{
		ind = ind == SoundSysData.PF.SoundReleaseInfoMaxNum ? 0 : ind + 1 ;
	}
	SoundSysData.PF.SoundReleaseInfoNextUseIndex = ind == SoundSysData.PF.SoundReleaseInfoMaxNum ? 0 : ind + 1 ;

	// �f�[�^���Z�b�g
	SoundSysData.PF.SoundReleaseInfo[ ind ].UseFlag = TRUE ;
	SoundSysData.PF.SoundReleaseInfo[ ind ].ALSource = Buffer->PF.ALSource ;
	_MEMCPY( SoundSysData.PF.SoundReleaseInfo[ ind ].ALBuffer, Buffer->PF.ALBuffer, sizeof( Buffer->PF.ALBuffer ) ) ;
	SoundSysData.PF.SoundReleaseInfo[ ind ].ReleaseTime = NS_GetNowCount() ;

	// ���X�g�ɒǉ�
	SoundSysData.PF.SoundReleaseInfo[ ind ].NextIndex = SoundSysData.PF.SoundReleaseInfoFirstIndex ;
	SoundSysData.PF.SoundReleaseInfoFirstIndex = ind ;
    
    // �T�E���h�j�����̐��𑝂₷
    SoundSysData.PF.SoundReleaseInfoNum ++ ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.SoundReleaseCriticalSection ) ;

	// ����I��
	return 0 ;
}

// AL�o�b�t�@��AL�\�[�X�ɒǉ�����
static void SourceQueueSoundBuffer( SOUNDBUFFER *Buffer )
{
	DWORD BytesRequired ;
	int Processed ;
    ALenum Format ;
	int i ;
	ALint state ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &Buffer->PF.CriticalSection ) ;

	if( Buffer->State == FALSE )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;
		return ;
	}

    if( Buffer->Format.wBitsPerSample == 8 )
    {
        Format = Buffer->Format.nChannels == 1 ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8 ;
    }
    else
    {
        Format = Buffer->Format.nChannels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16 ;
    }

	// �Đ����~�܂��Ă��܂��Ă�����ēx�Đ�����
//	alGetSourcei( Buffer->PF.ALSource, AL_SOURCE_STATE, &state ) ;
//	if( state != AL_PLAYING )
//	{
//		if( state == AL_PAUSED || state == AL_STOPPED )
//		{
//			alSourcePlay( Buffer->PF.ALSource ) ;
//		}
//	}

	// �Đ����I�������L���[��������Ή������Ȃ�
	alGetSourcei( Buffer->PF.ALSource, AL_BUFFERS_PROCESSED, &Processed );
	if( Processed == 0 )
	{
		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;
		return ;
	}

	for( i = 0 ; i < Processed ; i ++ )
	{
		int TargetBuffer ;
		ALuint ALBuffer ;
		int IsNext ;

		// �Đ������������o�b�t�@���擾
		alSourceUnqueueBuffers( Buffer->PF.ALSource, 1, &ALBuffer );

		for( TargetBuffer = 0; TargetBuffer < SOUNDSOURCE_BUFFER_NUM && ALBuffer != Buffer->PF.ALBuffer[ TargetBuffer ]; TargetBuffer ++ ){}
		if( TargetBuffer == SOUNDSOURCE_BUFFER_NUM )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\x61\x00\x6c\x00\x53\x00\x6f\x00\x75\x00\x72\x00\x63\x00\x65\x00\x55\x00\x6e\x00\x71\x00\x75\x00\x65\x00\x75\x00\x65\x00\x42\x00\x75\x00\x66\x00\x66\x00\x65\x00\x72\x00\x73\x00\x20\x00\x4c\x30\x7f\x4f\x28\x75\x57\x30\x66\x30\x44\x30\x6a\x30\x44\x30\x20\x00\x41\x00\x4c\x00\x42\x00\x75\x00\x66\x00\x66\x00\x65\x00\x72\x00\x20\x00\x92\x30\xd4\x8f\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"alSourceUnqueueBuffers ���g�p���Ă��Ȃ� ALBuffer ��Ԃ��܂���\n" @*/ )) ;

			// �N���e�B�J���Z�N�V�����̉��
			CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;
			return ;
		}

		// �Đ��ʒu���X�V
		Buffer->PlayPos = Buffer->PF.ALBufferEndPos[ TargetBuffer ] ;

		// ���[�v�����A���o�b�t�@�̍Ō�܂ŃZ�b�g���I����Ă���ꍇ�͍Đ��I�����������ďI��
		if( Buffer->Loop == FALSE && Buffer->SampleNum == Buffer->CompPos )
		{
			// �Đ���Ԃ��I��
			Buffer->State = FALSE ;

			// �Đ����Ă���T�E���h�̃��X�g����O��
			SoundBuffer_Sub_PlaySoundBufferList( Buffer ) ;

			// �T�E���h�j���˗��ɒǉ�
			SoundReleaseInfo_Add( Buffer ) ;

			// �Đ�����������Ԃ�����
			Buffer->PF.PlaySetupComp = FALSE ;

			goto END ;
		}

		// �o�b�t�@���Z�b�g�A�b�v
		SetupSoundBuffer( Buffer, &IsNext, TargetBuffer ) ;
		alBufferData( Buffer->PF.ALBuffer[ TargetBuffer ], Format, Buffer->PF.ALBufferImage[ TargetBuffer ], Buffer->PF.ALBufferValidBytes[ TargetBuffer ], Buffer->Format.nSamplesPerSec ) ;

		// �o�b�t�@���L���[�ɒǉ�
		alSourceQueueBuffers( Buffer->PF.ALSource, 1, &Buffer->PF.ALBuffer[ TargetBuffer ] ) ;
	}

END :

	// �Đ����~�܂��Ă��܂��Ă�����ēx�Đ�����
	alGetSourcei( Buffer->PF.ALSource, AL_SOURCE_STATE, &state ) ;
	if( state != AL_PLAYING )
	{
		if( state == AL_PAUSED || state == AL_STOPPED )
		{
			alSourcePlay( Buffer->PF.ALSource ) ;
		}
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;
}

static void UpdateALBuffer() {
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &HandleManageArray[ DX_HANDLETYPE_SOUND ].CriticalSection ) ;

	// �Đ��I���������s��
	SoundReleaseInfo_Process() ;

	// �Đ��������s��
	{
		SOUNDBUFFER *Buffer ;
		SOUNDBUFFER *NextBuffer ;

		// �N���e�B�J���Z�N�V�����̎擾
		CRITICALSECTION_LOCK( &SoundSysData.PF.PlaySoundBufferCriticalSection ) ;

		Buffer = SoundSysData.PF.PlaySoundBuffer ;
		while( Buffer != NULL )
		{
			NextBuffer = Buffer->PF.PlaySoundBufferNext ;
			SourceQueueSoundBuffer( Buffer ) ;
			Buffer = NextBuffer ;
		}

		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &SoundSysData.PF.PlaySoundBufferCriticalSection ) ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &HandleManageArray[ DX_HANDLETYPE_SOUND ].CriticalSection ) ;
}

// �T�E���h�o�b�t�@�Đ������p�X���b�h
static void *ALBufferPlayThreadFunction( void *argc )
{
	while( SoundSysData.PF.ProcessSoundThreadEndRequest == FALSE )
	{
		UpdateALBuffer();

		// �҂�
		usleep( 1000 ) ;
	}

	return NULL ;
}

static void UpdateStreamSound() {
		// �N���e�B�J���Z�N�V�����̎擾
		CRITICALSECTION_LOCK( &HandleManageArray[ DX_HANDLETYPE_SOUND ].CriticalSection ) ;

		// ��~�҂��T�E���h�o�b�t�@���X�g�ɓo�^����Ă���T�E���h�o�b�t�@���~����
		SoundBuffer_Apply_StopSoundBufferList() ;

		// �X�g���[�~���O����
		NS_ProcessStreamSoundMemAll() ;

		// �Đ����I��������n���h�����폜���鏈�����s��
//		ProcessPlayFinishDeleteSoundMemAll() ;

		// �R�c�T�E���h���Đ����Ă���T�E���h�n���h���ɑ΂��鏈�����s��
		ProcessPlay3DSoundMemAll() ;

		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &HandleManageArray[ DX_HANDLETYPE_SOUND ].CriticalSection ) ;


		// �N���e�B�J���Z�N�V�����̎擾
		CRITICALSECTION_LOCK( &HandleManageArray[ DX_HANDLETYPE_SOFTSOUND ].CriticalSection ) ;

		// �X�g���[�~���O����
		ST_SoftSoundPlayerProcessAll() ;

		// �N���e�B�J���Z�N�V�����̉��
		CriticalSection_Unlock( &HandleManageArray[ DX_HANDLETYPE_SOFTSOUND ].CriticalSection ) ;
}

// �X�g���[���T�E���h�����p�X���b�h
static void *StreamSoundThreadFunction( void *argc )
{
	while( SoundSysData.PF.ProcessALBufferThreadEndRequest == FALSE )
	{
		UpdateStreamSound();

		// �҂�
		Thread_Sleep( 10 ) ;
	}

	return NULL ;
}

// �T�E���h�V�X�e��������������֐��̊��ˑ��������s���֐�
extern int InitializeSoundSystem_PF_Timing0( void )
{
	int i ;

	if( SoundSysData.PF.ALCdeviceObject != NULL )
	{
		return 0 ;
	}

	DXST_LOGFILE_ADDUTF16LE( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x41\x00\x4c\x00\x1d\x52\x1f\x67\x16\x53\x8b\x95\xcb\x59\x0a\x00\x00"/*@ L"OpenAL�������J�n\n" @*/ ) ;

	DXST_LOGFILE_TABADD ;

	// �X�g�b�v�T�E���h�o�b�t�@�p�̃N���e�B�J���Z�N�V������������
	if( CriticalSection_Initialize( &SoundSysData.PF.StopSoundBufferCriticalSection ) < 0 )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x41\x00\x4c\x00\x20\x00\x6e\x30\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x5c\x50\x62\x6b\xe6\x51\x06\x74\x28\x75\x6e\x30\xaf\x30\xea\x30\xc6\x30\xa3\x30\xab\x30\xeb\x30\xbb\x30\xaf\x30\xb7\x30\xe7\x30\xf3\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenAL �̃T�E���h�o�b�t�@��~�����p�̃N���e�B�J���Z�N�V�����̍쐬�Ɏ��s���܂���\n" @*/ )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// 8bit�g�`��16bit�g�`�ɕϊ����邽�߂̃e�[�u����������
	for( i = 0 ; i < 256 ; i ++ )
	{
		Bit8To16Table[ i ] = ( short )( ( ( int )i * 65535 ) / 255 - 32768 ) ;
	}

	// �����f�[�^�̏�����
	for( i = 0 ; i < STREAM_SOUND_BUFFER_UNIT_SAPMLES ; i ++ )
	{
		g_NoneSound8bit[ i ]  = 128 ;
		g_NoneSound16bit[ i ] = 0 ;
	}

	// API �̃A�h���X���擾
//	alBufferDataStaticProc = ( alBufferDataStaticProcPtr )alcGetProcAddress( NULL, "alBufferDataStatic" ) ;

	// AL�f�o�C�X�̍쐬
	SoundSysData.PF.ALCdeviceObject = alcOpenDevice( alcGetString( NULL, ALC_DEFAULT_DEVICE_SPECIFIER ) ) ;
	if( SoundSysData.PF.ALCdeviceObject == NULL )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x41\x00\x4c\x00\x20\x00\x6e\x30\xc7\x30\xd0\x30\xa4\x30\xb9\x30\xaa\x30\xd6\x30\xb8\x30\xa7\x30\xaf\x30\xc8\x30\x6e\x30\xaa\x30\xfc\x30\xd7\x30\xf3\x30\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenAL �̃f�o�C�X�I�u�W�F�N�g�̃I�[�v���Ɏ��s���܂���\n" @*/ )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

	// AL�R���e�L�X�g�̍쐬
	SoundSysData.PF.ALCcontectObject = alcCreateContext( SoundSysData.PF.ALCdeviceObject, NULL ) ;
	if( SoundSysData.PF.ALCcontectObject == NULL )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x41\x00\x4c\x00\x20\x00\x6e\x30\xb3\x30\xf3\x30\xc6\x30\xad\x30\xb9\x30\xc8\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"OpenAL �̃R���e�L�X�g�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
		DXST_LOGFILE_TABSUB ;
		return -1 ;
	}

//	// �}�C�N���m�F����������܂ő҂�
//	while( CheckRecordPermissionProcessEnd() == FALSE )
//	{
//		usleep( 1000 ) ;
//	}

	// �J�����gAL�R���e�L�X�g�̐ݒ�
	alcMakeContextCurrent( SoundSysData.PF.ALCcontectObject ) ;

	// �T�E���h�j�������̏��������s��
	SoundReleaseInfo_Initialize() ;

	// ALBuffer �̍Đ��������s���X���b�h�̊J�n
	// {
	// 	pthread_attr_t attr ;
	// 	sched_param param ;
	// 	int returnCode ;

	// 	pthread_attr_init( &attr ) ;
	// 	pthread_attr_setstacksize( &attr, 128 * 1024 ) ;

	// 	returnCode = pthread_create(
	// 		&SoundSysData.PF.ProcessALBufferThread,
	// 		&attr,
	// 		ALBufferPlayThreadFunction,
	// 		NULL
	// 	) ;
	// 	if( returnCode != 0 )
	// 	{
	// 		DXST_LOGFILEFMT_ADDUTF16LE(( "\x41\x00\x4c\x00\x42\x00\x75\x00\x66\x00\x66\x00\x65\x00\x72\x00\x20\x00\x6e\x30\x8d\x51\x1f\x75\xe6\x51\x06\x74\x92\x30\x4c\x88\x46\x30\xb9\x30\xec\x30\xc3\x30\xc9\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"ALBuffer �̍Đ��������s���X���b�h�̍쐬�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, returnCode )) ;
	// 		DXST_LOGFILE_TABSUB ;
	// 		return -1 ;
	// 	}

	// 	_MEMSET( &param, 0, sizeof( param ) ) ;
	// 	param.sched_priority = sched_get_priority_max( 0 /* SCHED_NORMAL */ ) ;
	// 	pthread_setschedparam( SoundSysData.PF.ProcessALBufferThread, 0 /* SCHED_NORMAL */, &param ) ;
	// }
 
	// ProcessStreamSoundMemAll �����ĂԃX���b�h�̊J�n
	// {
	// 	pthread_attr_t attr ;
	// 	int returnCode ;

	// 	pthread_attr_init( &attr ) ;
	// 	pthread_attr_setstacksize( &attr, 128 * 1024 ) ;

	// 	returnCode = pthread_create(
	// 		&SoundSysData.PF.ProcessSoundThread,
	// 		&attr,
	// 		StreamSoundThreadFunction,
	// 		NULL
	// 	) ;
	// 	if( returnCode != 0 )
	// 	{
	// 		DXST_LOGFILEFMT_ADDUTF16LE(( "\x50\x00\x72\x00\x6f\x00\x63\x00\x65\x00\x73\x00\x73\x00\x53\x00\x74\x00\x72\x00\x65\x00\x61\x00\x6d\x00\x53\x00\x6f\x00\x75\x00\x6e\x00\x64\x00\x4d\x00\x65\x00\x6d\x00\x41\x00\x6c\x00\x6c\x00\x20\x00\x49\x7b\x92\x30\x7c\x54\x76\x30\xb9\x30\xec\x30\xc3\x30\xc9\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x20\x00\x45\x00\x72\x00\x72\x00\x6f\x00\x72\x00\x20\x00\x43\x00\x6f\x00\x64\x00\x65\x00\x20\x00\x3a\x00\x20\x00\x30\x00\x78\x00\x25\x00\x30\x00\x38\x00\x58\x00\x0a\x00\x00"/*@ L"ProcessStreamSoundMemAll �����ĂԃX���b�h�̍쐬�Ɏ��s���܂��� Error Code : 0x%08X\n" @*/, returnCode )) ;
	// 		DXST_LOGFILE_TABSUB ;
	// 		return -1 ;
	// 	}
	// }
	
	DXST_LOGFILE_TABSUB ;

	DXST_LOGFILE_ADDUTF16LE( "\x4f\x00\x70\x00\x65\x00\x6e\x00\x41\x00\x4c\x00\x1d\x52\x1f\x67\x16\x53\x8c\x5b\x86\x4e\x0a\x00\x00"/*@ L"OpenAL����������\n" @*/ ) ;

	// �I��
	return 0 ;
}


// �T�E���h�V�X�e��������������֐��̊��ˑ��������s���֐�( ���s�ӏ���ʂP )
extern	int		InitializeSoundSystem_PF_Timing1( void )
{
#ifndef DX_NON_MULTITHREAD
	SoundSysData.PF.DXSoundProcessStart = TRUE ;
#endif // DX_NON_MULTITHREAD

	// ����I��
	return 0 ;
}




// �T�E���h�V�X�e���̌�n��������֐��̊��ˑ��������s���֐�( ���s�ӏ���ʂO )
extern	int		TerminateSoundSystem_PF_Timing0( void )
{
#ifndef DX_NON_MULTITHREAD
	SoundSysData.PF.DXSoundProcessStart = FALSE ;
#endif // DX_NON_MULTITHREAD

	// ProcessStreamSoundMemAll �����ĂԃX���b�h���I������
	SoundSysData.PF.ProcessSoundThreadEndRequest = TRUE ;
	pthread_join( SoundSysData.PF.ProcessSoundThread, NULL ) ;

	// ALBuffer �̍Đ��������s���X���b�h���I������
	SoundSysData.PF.ProcessALBufferThreadEndRequest = TRUE ;
	pthread_join( SoundSysData.PF.ProcessALBufferThread, NULL ) ;

	// ����I��
	return 0 ;
}


// �T�E���h�V�X�e���̌�n��������֐��̊��ˑ��������s���֐�( ���s�ӏ���ʂP )
extern	int		TerminateSoundSystem_PF_Timing1( void )
{
	// �T�E���h�j�������̌�n�����s��
	SoundReleaseInfo_Terminate() ;

	// �J�����gAL�R���e�L�X�g�̉���
	alcMakeContextCurrent( NULL ) ;

	// AL�R���e�L�X�g�̌�n��
	if( SoundSysData.PF.ALCcontectObject )
	{
		alcDestroyContext( SoundSysData.PF.ALCcontectObject ) ;
		SoundSysData.PF.ALCcontectObject = NULL ;
	}

	// AL�f�o�C�X�̌�n��
	if( SoundSysData.PF.ALCdeviceObject )
	{
		alcCloseDevice( SoundSysData.PF.ALCdeviceObject ) ;
		SoundSysData.PF.ALCdeviceObject = NULL ;
	}

	// �X�g�b�v�T�E���h�o�b�t�@�p�̃N���e�B�J���Z�N�V�������폜
	CriticalSection_Delete( &SoundSysData.PF.StopSoundBufferCriticalSection ) ;

	// ����I��
	return 0 ;
}

// �T�E���h�V�X�e���̏������`�F�b�N�̊��ˑ��������s���֐�( TRUE:����������Ă���  FALSE:����������Ă��Ȃ� )
extern	int		CheckSoundSystem_Initialize_PF( void )
{
	return SoundSysData.PF.ALCdeviceObject != NULL ? TRUE : FALSE ;
}

extern	int 	UpdateSound_PF( void )
{
	int isInited = CheckSoundSystem_Initialize_PF();

	if (isInited == FALSE) {
		return -1;
	}

	UpdateALBuffer();
	UpdateStreamSound();

	return 0 ;
}

// �T�E���h�V�X�e���̑��Đ����Ԃ��擾����
extern	int		GetSoundSystemTotalPlaySamples_PF( ULONGLONG *TotalPlaySamples, ULONGLONG *Frequency )
{
	// ��Ή�
	return -1 ;
}

// �l�h�c�h�n���h���̌�n�����s���֐��̊��ˑ�����
extern	int		TerminateMidiHandle_PF( MIDIHANDLEDATA *MusicData )
{
	// ����I��
	return 0 ;
}

// �v���Z�b�g�̂R�c�T�E���h�p�̃��o�[�u�p�����[�^���擾���鏈���̊��ˑ��������s���֐�
extern	int		Get3DPresetReverbParamSoundMem_PF( SOUND3D_REVERB_PARAM *ParamBuffer, int PresetNo /* DX_REVERB_PRESET_DEFAULT �� */ )
{
	return 0 ;
}

// �R�c�T�E���h�̃��X�i�[�̈ʒu�ƃ��X�i�[�̑O���ʒu�ƃ��X�i�[�̏�����ʒu��ݒ肷�鏈���̊��ˑ��������s���֐�
extern int Set3DSoundListenerPosAndFrontPosAndUpVec_PF( VECTOR Position, VECTOR FrontPosition, VECTOR UpVector )
{
	return 0 ;
}

// �R�c�T�E���h�̃��X�i�[�̈ړ����x��ݒ肷�鏈���̊��ˑ��������s���֐�
extern int Set3DSoundListenerVelocity_PF( VECTOR Velocity )
{
	return 0 ;
}

// �R�c�T�E���h�̃��X�i�[�̉��p�x�͈͂�ݒ肷�鏈���̊��ˑ��������s���֐�
extern int Set3DSoundListenerConeAngle_PF( float InnerAngle, float OuterAngle )
{
	return 0 ;
}

// �R�c�T�E���h�̃��X�i�[�̉��p�x�͈͂̉��ʔ{����ݒ肷�鏈���̊��ˑ��������s���֐�
extern int Set3DSoundListenerConeVolume_PF( float InnerAngleVolume, float OuterAngleVolume )
{
	return 0 ;
}

// LoadMusicMemByMemImage �̎������֐��̊��ˑ��������s���֐�
extern int LoadMusicMemByMemImage_Static_PF( MIDIHANDLEDATA *MusicData, int ASyncThread )
{
	return 0 ;
}

// �ǂݍ��񂾂l�h�c�h�f�[�^�̉��t���J�n���鏈���̊��ˑ��������s���֐�
extern int PlayMusicMem_PF( MIDIHANDLEDATA *MusicData, int PlayType )
{
	return 0 ;
}

// �l�h�c�h�f�[�^�̉��t���~���鏈���̊��ˑ��������s��
extern int StopMusicMem_PF( MIDIHANDLEDATA *MusicData )
{
	return 0 ;
}

// �l�h�c�h�f�[�^�����t�����ǂ������擾����( TRUE:���t��  FALSE:��~�� )�����̊��ˑ��������s���֐�
extern int CheckMusicMem_PF( MIDIHANDLEDATA *MusicData )
{
	return 0 ;
}

// �l�h�c�h�f�[�^�̎����I�����̊��ˑ��������s���֐�
extern int ProcessMusicMem_PF( MIDIHANDLEDATA *MusicData )
{
	return 0 ;
}

// �l�h�c�h�f�[�^�̌��݂̍Đ��ʒu���擾���鏈���̊��ˑ��������s���֐�
extern int GetMusicMemPosition_PF( MIDIHANDLEDATA *MusicData )
{
	return 0 ;
}

// �l�h�c�h�̍Đ����ʂ��Z�b�g���鏈���̊��ˑ��������s���֐�
extern int SetVolumeMusic_PF( int Volume )
{
	return 0 ;
}

// �l�h�c�h�̌��݂̍Đ��ʒu���擾���鏈���̊��ˑ��������s���֐�
extern int GetMusicPosition_PF( void )
{
	return 0 ;
}









extern int SoundBuffer_Initialize_Timing0_PF( SOUNDBUFFER *Buffer, DWORD Bytes, WAVEFORMATEX *Format, SOUNDBUFFER *Src, int Is3DSound )
{
	int i ;
	int InitializeCriticalSection = FALSE ;

	// �[��������
	_MEMSET( &Buffer->PF, 0, sizeof( Buffer->PF ) ) ;

	// �N���e�B�J���Z�N�V������������
	if( CriticalSection_Initialize( &Buffer->PF.CriticalSection ) < 0 )
	{
		goto ERR ;
	}
	InitializeCriticalSection = TRUE ;

	// AL�\�[�X���쐬
//	alGetError() ;
//	alGenSources( 1, &Buffer->PF.ALSource ) ;
//	if( alGetError() != AL_NO_ERROR )
//	{
//		DXST_LOGFILEFMT_ADDUTF16LE(( "\x67\x7e\x75\xff\x67\x7e\x66\xff\x5d\x7e\x73\xff\x5d\x7e\xe8\x5c\xf0\x30\x5d\x7e\x00\x00\xf5\x30\x67\x7e\x61\xff\x15\x90\x68\xff\x3a\x7e\x6e\xff\x41\x00\x4c\x00\x67\x7e\x7d\xff\x5d\x7e\x7c\xff\x67\x7e\x79\xff\x3a\x7e\x6e\xff\xf4\x83\xc8\x61\x00\x00\x3a\x7e\x6b\xff\x9f\x87\x71\xff\x28\x8b\xb1\x52\x20\xff\x3a\x7e\x7e\xff\x3a\x7e\xb1\x52\xc6\x25\x0a\x00\x00"/*@ L"�T�E���h�o�b�t�@�p��AL�\�[�X�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
//		goto ERR ;
//	}
//
//	// AL�p�o�b�t�@���쐬
//	alGetError() ;
//	alGenBuffers( SOUNDSOURCE_BUFFER_NUM, Buffer->PF.ALBuffer ) ;
//	if( alGetError() != AL_NO_ERROR )
//	{
//		DXST_LOGFILEFMT_ADDUTF16LE(( "\x67\x7e\x75\xff\x67\x7e\x66\xff\x5d\x7e\x73\xff\x5d\x7e\xe8\x5c\xf0\x30\x5d\x7e\x00\x00\xf5\x30\x67\x7e\x61\xff\x15\x90\x68\xff\x3a\x7e\x6e\xff\x41\x00\x4c\x00\x5d\x7e\x0c\x82\xe3\x30\x5d\x7e\x14\x8f\x43\x30\x3a\x7e\x6e\xff\xf4\x83\xc8\x61\x00\x00\x3a\x7e\x6b\xff\x9f\x87\x71\xff\x28\x8b\xb1\x52\x20\xff\x3a\x7e\x7e\xff\x3a\x7e\xb1\x52\xc6\x25\x0a\x00\x00"/*@ L"�T�E���h�o�b�t�@�p��AL�o�b�t�@�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
//		goto ERR ;
//	}

	// �T�E���h�o�b�t�@�p�̃��������m��
	if( Src != NULL )
	{
		Buffer->SampleNum	= Src->SampleNum ;
		Buffer->Format		= Src->Format ;
		Buffer->Wave		= DuplicateWaveData( Src->Wave ) ;
	}
	else
	{
		Buffer->Format		= *Format ;
		Buffer->SampleNum	= ( int )( Bytes / Format->nBlockAlign ) ;
		Buffer->Wave		= AllocWaveData( ( int )Bytes, FALSE ) ;
	}
	if( Buffer->Wave == NULL )
	{
		DXST_LOGFILEFMT_ADDUTF16LE(( "\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�E���h�o�b�t�@�p�̃������̊m�ۂɎ��s���܂���\n" @*/ )) ;
		goto ERR ;
	}

	// AL�p�o�b�t�@�̃������̊m��
	for( i = 0 ; i < SOUNDSOURCE_BUFFER_NUM ; i ++ )
	{
		Buffer->PF.ALBufferImage[ i ] = DXALLOC( STREAM_SOUND_BUFFER_UNIT_SAPMLES * Buffer->Format.wBitsPerSample * Buffer->Format.nChannels / 8 ) ;
		if( Buffer->PF.ALBufferImage[ i ] == NULL )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\x41\x00\x4c\x00\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x28\x75\x6e\x30\xe1\x30\xe2\x30\xea\x30\x6e\x30\xba\x78\xdd\x4f\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"AL�T�E���h�o�b�t�@�p�̃������̊m�ۂɎ��s���܂���\n" @*/ )) ;
			goto ERR ;
		}
	}

	// ����I��
	return 0 ;

	// �G���[����
ERR :

//	if( Buffer->PF.ALSource != 0 )
//	{
//		alSourceStop( Buffer->PF.ALSource ) ;
//		alDeleteSources( 1, &Buffer->PF.ALSource ) ;
//		Buffer->PF.ALSource = 0 ;
//	}
//
//	if( Buffer->PF.ALBuffer[ 0 ] != 0 )
//	{
//		alDeleteBuffers( SOUNDSOURCE_BUFFER_NUM, Buffer->PF.ALBuffer );
//		_MEMSET( Buffer->PF.ALBuffer, 0, sizeof( Buffer->PF.ALBuffer ) ) ;
//	}

	for( i = 0 ; i < SOUNDSOURCE_BUFFER_NUM ; i ++ )
	{
		if( Buffer->PF.ALBufferImage[ i ] != NULL )
		{
			DXFREE( Buffer->PF.ALBufferImage[ i ] ) ;
			Buffer->PF.ALBufferImage[ i ] = NULL ;
		}
	}

	if( InitializeCriticalSection )
	{
		CriticalSection_Delete( &Buffer->PF.CriticalSection ) ;
	}

	return -1 ;
}

extern int SoundBuffer_Initialize_Timing1_PF( SOUNDBUFFER *Buffer, SOUNDBUFFER *Src, int Is3DSound )
{
	return 0 ;
}

extern int SoundBuffer_Terminate_PF( SOUNDBUFFER *Buffer )
{
    int i ;

	// AL�\�[�X�����
//	if( Buffer->PF.ALSource != 0 )
//	{
//		alSourceStop( Buffer->PF.ALSource ) ;
//		alDeleteSources( 1, &Buffer->PF.ALSource ) ;
//		Buffer->PF.ALSource = 0 ;
//	}
//
//	// AL�o�b�t�@�����
//	if( Buffer->PF.ALBuffer[ 0 ] != 0 )
//	{
//		alDeleteBuffers( SOUNDSOURCE_BUFFER_NUM, Buffer->PF.ALBuffer );
//		_MEMSET( Buffer->PF.ALBuffer, 0, sizeof( Buffer->PF.ALBuffer ) ) ;
//	}

	// AL�o�b�t�@�p�̃����������
	for( i = 0 ; i < SOUNDSOURCE_BUFFER_NUM ; i ++ )
	{
		if( Buffer->PF.ALBufferImage[ i ] != NULL )
		{
			DXFREE( Buffer->PF.ALBufferImage[ i ] ) ;
			Buffer->PF.ALBufferImage[ i ] = NULL ;
		}
	}

	// �N���e�B�J���Z�N�V�����̍폜
	CriticalSection_Delete( &Buffer->PF.CriticalSection ) ;

	return 0 ;
}

extern int SoundBuffer_CheckEnable_PF( SOUNDBUFFER *Buffer )
{
	return TRUE ;
}

extern int SoundBuffer_Play_PF( SOUNDBUFFER *Buffer, int Loop )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &Buffer->PF.CriticalSection ) ;

	// ��~�҂��T�E���h�o�b�t�@���X�g����T�E���h�o�b�t�@���O��
	SoundBuffer_Sub_StopSoundBufferList( Buffer ) ;

	// �Đ�����������Ă��Ȃ������珀�����s��
	if( Buffer->PF.PlaySetupComp == FALSE )
	{
		// AL�\�[�X���쐬
		alGetError() ;
		alGenSources( 1, &Buffer->PF.ALSource ) ;
		if( alGetError() != AL_NO_ERROR )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x28\x75\x6e\x30\x41\x00\x4c\x00\xbd\x30\xfc\x30\xb9\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�E���h�o�b�t�@�p��AL�\�[�X�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
			goto ERR ;
		}

		// AL�p�o�b�t�@���쐬
		alGetError() ;
		alGenBuffers( SOUNDSOURCE_BUFFER_NUM, Buffer->PF.ALBuffer ) ;
		if( alGetError() != AL_NO_ERROR )
		{
			DXST_LOGFILEFMT_ADDUTF16LE(( "\xb5\x30\xa6\x30\xf3\x30\xc9\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x28\x75\x6e\x30\x41\x00\x4c\x00\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�T�E���h�o�b�t�@�p��AL�o�b�t�@�̍쐬�Ɏ��s���܂���\n" @*/ )) ;
			goto ERR ;
		}

		// �Đ���������
		Buffer->PF.PlaySetupComp = TRUE ;

		// ���ʂ̐ݒ�
		SoundBuffer_RefreshVolume_PF( Buffer ) ;

		// �s�b�`�̐ݒ�
		if( Buffer->Frequency >= 0 )
		{
			SoundBuffer_SetFrequency_PF( Buffer, Buffer->Frequency ) ;
		}
	}

	// �Đ���ԂɃZ�b�g
	Buffer->State = TRUE ;

	// AL�T�E���h�o�b�t�@��AL�T�E���h�\�[�X�ɒǉ�
	{
		int IsNext ;
		ALenum Format ;
		DWORD AddBufferCount = 0 ;

		if( Buffer->Format.wBitsPerSample == 8 )
		{
			Format = Buffer->Format.nChannels == 1 ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8 ;
		}
		else
		{
			Format = Buffer->Format.nChannels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16 ;
		}

		// ��ڂ̃T�E���h�o�b�t�@���Z�b�g�A�b�v
		SetupSoundBuffer( Buffer, &IsNext, 0 ) ;
		alBufferData( Buffer->PF.ALBuffer[ 0 ], Format, Buffer->PF.ALBufferImage[ 0 ], Buffer->PF.ALBufferValidBytes[ 0 ], Buffer->Format.nSamplesPerSec ) ;
		AddBufferCount ++ ;

		if( Buffer->CompPos < Buffer->SampleNum )
		{
			// ��ڂ̃T�E���h�o�b�t�@���Z�b�g�A�b�v
			SetupSoundBuffer( Buffer, &IsNext, 1 ) ;
			alBufferData( Buffer->PF.ALBuffer[ 1 ], Format, Buffer->PF.ALBufferImage[ 1 ], Buffer->PF.ALBufferValidBytes[ 1 ], Buffer->Format.nSamplesPerSec ) ;
			AddBufferCount ++ ;

			if( Buffer->CompPos < Buffer->SampleNum )
			{
				// �O�ڂ̃T�E���h�o�b�t�@���Z�b�g�A�b�v
				SetupSoundBuffer( Buffer, &IsNext, 2 ) ;
				alBufferData( Buffer->PF.ALBuffer[ 2 ], Format, Buffer->PF.ALBufferImage[ 2 ], Buffer->PF.ALBufferValidBytes[ 2 ], Buffer->Format.nSamplesPerSec ) ;
				AddBufferCount ++ ;

				if( Buffer->CompPos < Buffer->SampleNum )
				{
					// �l�ڂ̃T�E���h�o�b�t�@���Z�b�g�A�b�v
					SetupSoundBuffer( Buffer, &IsNext, 3 ) ;
					alBufferData( Buffer->PF.ALBuffer[ 3 ], Format, Buffer->PF.ALBufferImage[ 3 ], Buffer->PF.ALBufferValidBytes[ 3 ], Buffer->Format.nSamplesPerSec ) ;
					AddBufferCount ++ ;

					if( Buffer->CompPos < Buffer->SampleNum )
					{
						// �܂ڂ̃T�E���h�o�b�t�@���Z�b�g�A�b�v
						SetupSoundBuffer( Buffer, &IsNext, 4 ) ;
						alBufferData( Buffer->PF.ALBuffer[ 4 ], Format, Buffer->PF.ALBufferImage[ 4 ], Buffer->PF.ALBufferValidBytes[ 4 ], Buffer->Format.nSamplesPerSec ) ;
						AddBufferCount ++ ;

						if( Buffer->CompPos < Buffer->SampleNum )
						{
							// �Z�ڂ̃T�E���h�o�b�t�@���Z�b�g�A�b�v
							SetupSoundBuffer( Buffer, &IsNext, 5 ) ;
							alBufferData( Buffer->PF.ALBuffer[ 5 ], Format, Buffer->PF.ALBufferImage[ 5 ], Buffer->PF.ALBufferValidBytes[ 5 ], Buffer->Format.nSamplesPerSec ) ;
							AddBufferCount ++ ;
						}
					}
				}
			}
		}

		// �o�b�t�@���L���[�ɒǉ�
		alSourceQueueBuffers( Buffer->PF.ALSource, AddBufferCount, Buffer->PF.ALBuffer ) ;
	}

	Buffer->StopTimeState = 1 ;
	Buffer->StopTime = 0 ;

	// �Đ����J�n
	alSourcePlay( Buffer->PF.ALSource ) ;

	// �Đ����Ă���T�E���h�̃��X�g�ɉ�����
	SoundBuffer_Add_PlaySoundBufferList( Buffer ) ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;

	return 0 ;

ERR :
	if( Buffer->PF.ALSource != 0 )
	{
		alSourceStop( Buffer->PF.ALSource ) ;
		alDeleteSources( 1, &Buffer->PF.ALSource ) ;
		Buffer->PF.ALSource = 0 ;
	}

	if( Buffer->PF.ALBuffer[ 0 ] != 0 )
	{
		alDeleteBuffers( SOUNDSOURCE_BUFFER_NUM, Buffer->PF.ALBuffer );
		_MEMSET( Buffer->PF.ALBuffer, 0, sizeof( Buffer->PF.ALBuffer ) ) ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;

	return -1 ;
}

extern int SoundBuffer_Stop_PF(	SOUNDBUFFER *Buffer, int EffectStop )
{
	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &Buffer->PF.CriticalSection ) ;

	// �Đ��̏������s���Ă���ꍇ�̂ݏ���
	if( Buffer->PF.PlaySetupComp )
	{
		if( Buffer->PF.ALSource != 0 )
		{
			alSourceStop( Buffer->PF.ALSource ) ;
			alDeleteSources( 1, &Buffer->PF.ALSource ) ;
			Buffer->PF.ALSource = 0 ;
		}

		if( Buffer->PF.ALBuffer[ 0 ] != 0 )
		{
			alDeleteBuffers( SOUNDSOURCE_BUFFER_NUM, Buffer->PF.ALBuffer ) ;
			_MEMSET( Buffer->PF.ALBuffer, 0, sizeof( Buffer->PF.ALBuffer ) ) ;
		}

		Buffer->PF.PlaySetupComp = FALSE ;
	}

	Buffer->State = FALSE ;

	// �Đ����Ă���T�E���h�̃��X�g����O��
	SoundBuffer_Sub_PlaySoundBufferList( Buffer ) ;

	// ��~�҂��T�E���h�o�b�t�@���X�g����T�E���h�o�b�t�@���O��
	SoundBuffer_Sub_StopSoundBufferList( Buffer ) ;

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;

	return 0 ;
}

extern int SoundBuffer_CheckPlay_PF( SOUNDBUFFER *Buffer )
{
	return Buffer->State ;
}

extern int SoundBuffer_Lock_PF( SOUNDBUFFER *Buffer, DWORD WritePos , DWORD WriteSize, void **LockPos1, DWORD *LockSize1, void **LockPos2, DWORD *LockSize2 )
{
	return 2 ;
}

extern int SoundBuffer_Unlock_PF( SOUNDBUFFER *Buffer, void *LockPos1, DWORD LockSize1, void *LockPos2, DWORD LockSize2 )
{
	DWORD i ;

	// �_�u���T�C�Y�̏ꍇ�̓X�e���I�f�[�^�ɂ���
	if( Buffer->Wave->DoubleSizeBuffer != NULL )
	{
		switch( Buffer->Format.wBitsPerSample )
		{
		case 8 :
			{
				BYTE *Src8bit ;
				WORD *Dest8bit ;
				DWORD SampleNum ;

				Src8bit = ( BYTE * )LockPos1 ;
				Dest8bit = ( WORD * )Buffer->Wave->DoubleSizeBuffer + ( ( BYTE * )LockPos1 - ( BYTE * )Buffer->Wave->Buffer ) ;
				SampleNum = LockSize1 ;
				for( i = 0 ; i < SampleNum ; i ++ )
				{
					Dest8bit[ i ] = ( WORD )( Src8bit[ i ] + ( Src8bit[ i ] << 8 ) ) ;
				}

				Src8bit = ( BYTE * )LockPos2 ;
				Dest8bit = ( WORD * )Buffer->Wave->DoubleSizeBuffer + ( ( BYTE * )LockPos2 - ( BYTE * )Buffer->Wave->Buffer ) ;
				SampleNum = LockSize2 ;
				for( i = 0 ; i < SampleNum ; i ++ )
				{
					Dest8bit[ i ] = ( WORD )( Src8bit[ i ] + ( Src8bit[ i ] << 8 ) ) ;
				}
			}
			break ;

		case 16 :
			{
				WORD *Src16bit ;
				DWORD *Dest16bit ;
				DWORD SampleNum ;

				Src16bit = ( WORD * )LockPos1 ;
				Dest16bit = ( DWORD * )Buffer->Wave->DoubleSizeBuffer + ( ( WORD * )LockPos1 - ( WORD * )Buffer->Wave->Buffer ) ;
				SampleNum = LockSize1 / 2 ;
				for( i = 0 ; i < SampleNum ; i ++ )
				{
					Dest16bit[ i ] = ( DWORD )( Src16bit[ i ] + ( Src16bit[ i ] << 16 ) ) ;
				}

				Src16bit = ( WORD * )LockPos2 ;
				Dest16bit = ( DWORD * )Buffer->Wave->DoubleSizeBuffer + ( ( WORD * )LockPos2 - ( WORD * )Buffer->Wave->Buffer ) ;
				SampleNum = LockSize2 / 2 ;
				for( i = 0 ; i < SampleNum ; i ++ )
				{
					Dest16bit[ i ] = ( DWORD )( Src16bit[ i ] + ( Src16bit[ i ] << 16 ) ) ;
				}
			}
			break ;
		}
	}

	return 0 ;
}

extern int SoundBuffer_SetFrequency_PF( SOUNDBUFFER *Buffer, DWORD Frequency )
{
	// �Đ����������������ꍇ�̂ݏ������s��
	if( Buffer->PF.PlaySetupComp )
	{
		alSourcef( Buffer->PF.ALSource, AL_PITCH, ( float )Frequency / Buffer->Format.nSamplesPerSec ) ;
	}

	return 0 ;
}

extern int SoundBuffer_GetFrequency_PF( SOUNDBUFFER *Buffer, LPDWORD Frequency )
{
	return 2 ;
}

extern int SoundBuffer_RefreshVolume_PF( SOUNDBUFFER *Buffer )
{
	// �Đ����������������ꍇ�̂ݏ������s��
	if( Buffer->PF.PlaySetupComp )
	{
		int db ;
		float Position[ 3 ] ;

		Position[ 0 ] = Buffer->Pan / 10000.0f ;
		Position[ 1 ] = 0.0f ;
		Position[ 2 ] = 0.0f ;
		alSourcefv( Buffer->PF.ALSource, AL_POSITION, Position ) ;
		alSourcei( Buffer->PF.ALSource, AL_SOURCE_RELATIVE, AL_FALSE ) ;
		alSourcef( Buffer->PF.ALSource, AL_MAX_DISTANCE, 1.0f ) ;
		alSourcef( Buffer->PF.ALSource, AL_REFERENCE_DISTANCE, 0.5f ) ;

		db = Buffer->Volume[ 0 ] ;
		if( db <= -10000 )
		{
			db = -10000 ;
		}
		else
		if( db >= 0 )
		{
			db = 0 ;
		}
		alSourcef( Buffer->PF.ALSource, AL_GAIN, D_XAudio2DecibelsToAmplitudeRatio( db / 100.0f ) ) ;
	}

	return 0 ;
}

extern int SoundBuffer_GetCurrentPosition_PF(	SOUNDBUFFER *Buffer, LPDWORD PlayPos, LPDWORD WritePos )
{
	return 2 ;
}

extern int SoundBuffer_SetCurrentPosition_PF( SOUNDBUFFER *Buffer, DWORD NewPos )
{
	int OldState = Buffer->State ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &Buffer->PF.CriticalSection ) ;

	if( OldState == TRUE )
	{
		SoundBuffer_Stop( Buffer ) ;
	}

	Buffer->PlayPos  = ( int )( NewPos / Buffer->Format.nBlockAlign ) ;
	Buffer->CompPos  = Buffer->PlayPos ;
	Buffer->CompPosF = _FTOL( Buffer->CompPos ) ;
	if( Buffer->Frequency < 0 || Buffer->Frequency == Buffer->Format.nSamplesPerSec )
	{
		Buffer->EnableComPosF = FALSE ;
	}

	if( OldState == TRUE )
	{
		SoundBuffer_Play( Buffer, Buffer->Loop ) ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &Buffer->PF.CriticalSection ) ;

	return 0 ;
}

extern int SoundBuffer_CycleProcess_PF( SOUNDBUFFER *Buffer )
{
	return -1 ;
}

extern int SoundBuffer_Set3DPosition_PF( SOUNDBUFFER *Buffer, VECTOR *Position )
{
	return 0 ;
}

extern int SoundBuffer_Set3DRadius_PF( SOUNDBUFFER *Buffer, float Radius )
{
	return 0 ;
}

extern int SoundBuffer_Set3DInnerRadius_PF(	SOUNDBUFFER *Buffer, float Radius )
{
	return 0 ;
}

extern int SoundBuffer_Set3DVelocity_PF( SOUNDBUFFER *Buffer, VECTOR *Velocity )
{
	return 0 ;
}

extern int SoundBuffer_Set3DFrontPosition_PF( SOUNDBUFFER *Buffer, VECTOR *FrontPosition, VECTOR *UpVector )
{
	return 0 ;
}

extern int SoundBuffer_Set3DConeAngle_PF( SOUNDBUFFER *Buffer, float InnerAngle, float OuterAngle )
{
	return 0 ;
}

extern int SoundBuffer_Set3DConeVolume_PF( SOUNDBUFFER *Buffer, float InnerAngleVolume, float OuterAngleVolume )
{
	return 0 ;
}

extern int SoundBuffer_Refresh3DSoundParam_PF(	SOUNDBUFFER *Buffer, int AlwaysFlag )
{
	// �I��
	return 0 ;
}

extern int SoundBuffer_SetReverbParam_PF( SOUNDBUFFER *Buffer, SOUND3D_REVERB_PARAM *Param )
{
	return 0 ;
}

extern int SoundBuffer_SetPresetReverbParam_PF( SOUNDBUFFER *Buffer, int PresetNo )
{
	return 0 ;
}





















// �l�h�c�h���t�I�����Ă΂��R�[���o�b�N�֐�
extern int MidiCallBackProcess( void )
{
	return 0 ;
}






// AL�f�o�C�X��AL�R���e�L�X�g���Z�b�g����
extern void SoundSystem_iOS_SetALDeviceAndALContext( void *ALCDevice, void *ALCContext )
{
	SoundSysData.PF.ALCdeviceObject = ( ALCdevice * )ALCDevice ;
	SoundSysData.PF.ALCcontectObject = ( ALCcontext * )ALCContext ;
}








// �Đ����� ALBuffer ���č쐬���ččĐ�����
extern void SoundSystem_iOS_ALBuffer_RePlay( void )
{
	SOUNDBUFFER *RePlayBufferFirst ;
	SOUNDBUFFER *Buffer ;

	// �N���e�B�J���Z�N�V�����̎擾
	CRITICALSECTION_LOCK( &SoundSysData.PF.PlaySoundBufferCriticalSection ) ;

	// �Đ����̃T�E���h�o�b�t�@��ۑ�
	RePlayBufferFirst = SoundSysData.PF.PlaySoundBuffer ;
	Buffer = RePlayBufferFirst ;
	while( Buffer != NULL )
	{
		Buffer->PF.RePlaySoundBufferPrev = Buffer->PF.PlaySoundBufferPrev ;
		Buffer->PF.RePlaySoundBufferNext = Buffer->PF.PlaySoundBufferNext ;

		Buffer = Buffer->PF.PlaySoundBufferNext ;
	}

	// �Đ����̃T�E���h�o�b�t�@�̍Đ����~
	Buffer = RePlayBufferFirst ;
	while( Buffer != NULL )
	{
		SoundBuffer_Stop( Buffer ) ;

		Buffer = Buffer->PF.RePlaySoundBufferNext ;
	}

	// �Đ����̃T�E���h�o�b�t�@���ēx�Đ�
	Buffer = RePlayBufferFirst ;
	while( Buffer != NULL )
	{
		SoundBuffer_Play( Buffer, Buffer->Loop ) ;

		Buffer = Buffer->PF.RePlaySoundBufferNext ;
	}

	// �N���e�B�J���Z�N�V�����̉��
	CriticalSection_Unlock( &SoundSysData.PF.PlaySoundBufferCriticalSection ) ;
}










#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_SOUND

