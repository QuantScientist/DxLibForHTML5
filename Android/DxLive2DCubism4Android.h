// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Live2D Cubism4�֌W�w�b�_�t�@�C��( Android )
// 
// 				Ver 3.21d
// 
// -------------------------------------------------------------------------------

#ifndef DX_LIVE2DCUBISM4ANDROID_H
#define DX_LIVE2DCUBISM4ANDROID_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_LIVE2D_CUBISM4

// �C���N���[�h ------------------------------------------------------------------
#include "../DxLib.h"
#include "DxGraphicsAndroid.h"

// #ifndef DX_NON_NAMESPACE
// 
// namespace DxLib
// {
// 
// #endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

#define LIVE2D_CUBISM4_FUNC		

#define LIVE2D_SHADER_SetupMask_SetupMask										0
#define LIVE2D_SHADER_NormalMasked_NormalMaskedPremultipliedAlpha				1
#define LIVE2D_SHADER_NormalMasked_NormalMaskedInvertedPremultipliedAlpha		2
#define LIVE2D_SHADER_NormalMasked_NormalMasked									3
#define LIVE2D_SHADER_NormalMasked_NormalMaskedInverted							4
#define LIVE2D_SHADER_Normal_NormalPremultipliedAlpha							5
#define LIVE2D_SHADER_Normal_Normal												6
#define LIVE2D_SHADER_Num														7

// �\���̒�` --------------------------------------------------------------------

// Live2D Cubism4 �V�X�e�����ˑ��p�f�[�^�\����
struct LIVE2DCUBISM4SYSTEMDATA_PF
{
	GRAPHICS_ANDROID_SHADER Shader[ LIVE2D_SHADER_Num ] ;
} ;

// �������ϐ��錾 --------------------------------------------------------------

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

// Live2D Cubism4 �Ŏg�p���Ă���S�ẴV�F�[�_�[���J������
extern int Live2D_Cubism4_Android_ReleaseShaderAll( void ) ;

// #ifndef DX_NON_NAMESPACE
// 
// }
// 
// #endif // DX_NON_NAMESPACE

#endif // DX_NON_LIVE2D_CUBISM4

#endif // DX_LIVE2DCUBISM4ANDROID_H