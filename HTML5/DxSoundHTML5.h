// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		iOS�p�T�E���h�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.21d
// 
// -------------------------------------------------------------------------------

#ifndef DX_SOUNDIOS_H
#define DX_SOUNDIOS_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_SOUND

// �C���N���[�h ------------------------------------------------------------------
#include "../DxLib.h"
#include "../DxThread.h"

#include <AL/al.h>
#include <AL/alc.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �X�g���[���֌W�̒�`
#define STS_BUFSEC_FILE						(256)			// �X�g���[�����T�E���h�Đ����Ɋm�ۂ���T�E���h�o�b�t�@�̎���( �P�ʂ� STS_DIVNUM����1�b )( �t�@�C������̃X�g���[���Đ��p )
#define STS_ADVANCECOPYSEC_FILE				(192)			// �X�g���[�����T�E���h�Đ����ɉ����f�[�^���s�W�J���Ă����ő厞��( �P�ʂ� STS_DIVNUM����1�b )( �t�@�C������̃X�g���[���Đ��p )
#define STS_MINADVANCECOPYSEC_FILE			(96)			// �X�g���[�����T�E���h�Đ����ɉ����f�[�^���s�W�J���Ă����ŏ�����( �P�ʂ� STS_DIVNUM����1�b )( �t�@�C������̃X�g���[���Đ��p )

// ��̃T�E���h�\�[�X�̃o�b�t�@��
#define SOUNDSOURCE_BUFFER_NUM				(6)

// �T�E���h�o�b�t�@�Đ������p���̍ő吔
#define SOUNDBUFFERPLAYINFO_MAX_NUM			(512)

// �\���̒�` --------------------------------------------------------------------

// �T�E���h�j�������p�\����
struct SOUNDRELEASE_INFO
{
	int								UseFlag ;
	int								NextIndex ;

	ALuint							ALSource ;
	ALuint							ALBuffer[ SOUNDSOURCE_BUFFER_NUM ] ;

	DWORD							ReleaseTime ;
} ;

// �T�E���h�o�b�t�@���ˑ����\����
struct SOUNDBUFFER_PF
{
	DX_CRITICAL_SECTION				CriticalSection ;					// �N���e�B�J���Z�N�V����

	int								BufferEndPlayEnqueueNum ;			// �o�b�t�@�L���[�ɍĐ��I����̃L���[��ς񂾉�

	int								PlaySetupComp ;						// �Đ��������ς�ł��邩�ǂ���
 	ALuint							ALBuffer[ SOUNDSOURCE_BUFFER_NUM ] ; // AL�o�b�t�@
	void *							ALBufferImage[ SOUNDSOURCE_BUFFER_NUM ] ; // AL�o�b�t�@�C���[�W
	DWORD							ALBufferValidBytes[ SOUNDSOURCE_BUFFER_NUM ] ;	// AL�o�b�t�@�̗L���ȃf�[�^�̃o�C�g��
	DWORD							ALBufferEndPos[ SOUNDSOURCE_BUFFER_NUM ] ;	// AL�o�b�t�@�̗L���f�[�^�̏I���ʒu���T�E���h�o�b�t�@�̂ǂ̈ʒu�ɑ������邩�A�̏��
 	ALuint							ALSource ;							// AL�\�[�X

	int								StopSoundBufferValid ;
	struct SOUNDBUFFER *			StopSoundBufferPrev ;
	struct SOUNDBUFFER *			StopSoundBufferNext ;

	int								PlaySoundBufferValid ;
	struct SOUNDBUFFER *			PlaySoundBufferPrev ;
	struct SOUNDBUFFER *			PlaySoundBufferNext ;

	struct SOUNDBUFFER *			RePlaySoundBufferPrev ;
	struct SOUNDBUFFER *			RePlaySoundBufferNext ;
} ;

// �T�E���h�V�X�e���p���ˑ��f�[�^�\����
struct SOUNDSYSTEMDATA_PF
{
	ALCdevice *					ALCdeviceObject ;						// AL�f�o�C�X�I�u�W�F�N�g
	ALCcontext *				ALCcontectObject ;						// AL�R���e�L�X�g�I�u�W�F�N�g

	pthread_t					ProcessALBufferThread ;					// ALBuffer�̍Đ��������s���X���b�h��ID
	volatile int				ProcessALBufferThreadEndRequest ;		// ALBuffer�̍Đ��������s���X���b�h���I�����邩�ǂ���

	pthread_t					ProcessSoundThread ;					// ProcessStreamSoundMemAll �����ĂԃX���b�h��ID
	volatile int				ProcessSoundThreadEndRequest ;			// ProcessStreamSoundMemAll �����ĂԃX���b�h���I�����邩�ǂ���

	int							DXSoundProcessStart ;					// �c�w���C�u�����̃T�E���h�������J�n�������ǂ���

	DX_CRITICAL_SECTION			StopSoundBufferCriticalSection ;		// �N���e�B�J���Z�N�V����
	struct SOUNDBUFFER *		StopSoundBuffer ;

	DX_CRITICAL_SECTION			PlaySoundBufferCriticalSection ;		// �N���e�B�J���Z�N�V����
	struct SOUNDBUFFER *		PlaySoundBuffer ;

	int							SoundReleaseInitialize ;
	DX_CRITICAL_SECTION			SoundReleaseCriticalSection ;
	int							SoundReleaseInfoMaxNum ;
	int							SoundReleaseInfoNum ;
	SOUNDRELEASE_INFO *			SoundReleaseInfo ;
	int							SoundReleaseInfoFirstIndex ;
	int							SoundReleaseInfoNextUseIndex ;
} ;

// �l�h�c�h�f�[�^���ˑ����
struct MIDIHANDLEDATA_PF
{
	int							Dummy ;
} ;

// �l�h�c�h�V�X�e���p���ˑ��f�[�^�\����
struct MIDISYSTEMDATA_PF
{
	int							Dummy ;
} ;

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

extern	int		MidiCallBackProcess( void ) ;																			// �l�h�c�h���t�I�����Ă΂��R�[���o�b�N�֐�

extern	void	SoundBuffer_Apply_StopSoundBufferList( void ) ;							// ��~�҂��T�E���h�o�b�t�@���X�g�ɓo�^����Ă���T�E���h�o�b�t�@���~����


// AL�f�o�C�X��AL�R���e�L�X�g���Z�b�g����
extern	void	SoundSystem_iOS_SetALDeviceAndALContext( void *ALCDevice, void *ALCContext ) ;

// �Đ����� ALBuffer ���č쐬���ččĐ�����
extern	void	SoundSystem_iOS_ALBuffer_RePlay( void ) ;

extern	int		UpdateSound_PF( void ) ;


#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_SOUND

#endif // DX_SOUNDIOS_H
