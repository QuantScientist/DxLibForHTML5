// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		iOS�p�V�X�e���v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.21d
// 
// -------------------------------------------------------------------------------

#ifndef DX_SYSTEMIOS_H
#define DX_SYSTEMIOS_H

// �C���N���[�h ------------------------------------------------------------------
#include "../DxCompileConfig.h"
#include <pthread.h>
#include <sched.h>
#include <GLES2/gl2.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

// �\�t�g���A�N�e�B�u���ǂ������`�F�b�N����
#define CheckActiveState()					\
		if( g_iOSSys.NonActiveRunFlag == FALSE )\
		{\
			DxActiveWait_iOS() ;\
		}

// �\���̒�` --------------------------------------------------------------------

struct DXLIB_IOS_SYSTEMINFO
{
	volatile void				( *LostFocusCallbackFunction )( void *Data ) ;		// �A�v���̃t�H�[�J�X������ꂽ�ۂɌĂ΂��R�[���o�b�N�֐�
	volatile void				*LostFocusCallbackFunctionData ;					// �A�v���̃t�H�[�J�X������ꂽ�ۂɌĂ΂��R�[���o�b�N�֐��ɓn���|�C���^
	volatile void				( *GainedFocusCallbackFunction )( void *Data ) ;	// �A�v���̃t�H�[�J�X������ꂽ�ۂɌĂ΂��R�[���o�b�N�֐�
	volatile void				*GainedFocusCallbackFunctionData ;					// �A�v���̃t�H�[�J�X������ꂽ�ۂɌĂ΂��R�[���o�b�N�֐��ɓn���|�C���^
	
	volatile int				NonActiveRunFlag ;					// �A�v�����A�N�e�B�u�ł͂Ȃ��Ă����������s���邩�ǂ����̃t���O

	int							ViewWidth;
	int							ViewHeight;
	GLuint						ViewFrameBuffer ;					// �t���[���o�b�t�@
	GLuint						ViewDepthBuffer ;					// �t���[���o�b�t�@
	GLuint						ViewRenderBuffer ;					// �t���[���o�b�t�@
} ;

// �e�[�u��-----------------------------------------------------------------------

// �������ϐ��錾 --------------------------------------------------------------

extern DXLIB_IOS_SYSTEMINFO g_iOSSys ;
extern int g_iOSRunFlag ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// �A�N�e�B�u�ɂȂ�܂ŉ������Ȃ�
extern void DxActiveWait_iOS( void ) ;

// �A�v���̊O���f�[�^�ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetDocumentsDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

// �A�v���̃f�[�^�ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetLibraryPreferencesDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

// �A�v���̃L���b�V���t�@�C���ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetLibraryCachesDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

// �A�v���̈ꎞ�t�@�C���ۑ��p�̃f�B���N�g���p�X���擾����
extern int GetTmpDirPathForChar( char *PathBuffer, size_t PathBufferBytes ) ;

extern int GetGraphicsViewFramebufferInfo( unsigned int *ViewFrameBuffer, int *Width, int *Height ) ;

extern void GraphicsViewRenderBufferPresent( void ) ;

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_SYSTEMIOS_H
