//-----------------------------------------------------------------------------
// 
// 		�c�w���C�u����		iOS�p�}�X�N�f�[�^�Ǘ��v���O����
// 
//  	Ver 3.21d
// 
//-----------------------------------------------------------------------------

// �c�w���C�u�����쐬���p��`
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_MASK

// �C���N���[�h ---------------------------------------------------------------
#include "DxGraphicsHTML5.h"
#include "DxMaskHTML5.h"
#include "../DxModel.h"
#include "../DxSystem.h"
#include "../DxLog.h"
#include "../DxMask.h"
#include "../DxMemory.h"

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` -----------------------------------------------------------------

// �\���̐錾 -----------------------------------------------------------------

// �f�[�^��` -----------------------------------------------------------------

MASKMANAGEDATA_IOS MaskManageData_iOS ;

// �֐��錾 -------------------------------------------------------------------

// �v���O���� -----------------------------------------------------------------

// ���ˑ��֐�

// �}�X�N�X�N���[�����쐬����֐�
extern	int			Mask_CreateScreenFunction_Timing0_PF( void )
{
	MASKIOS.MaskScreenOldFrameBuffer   = MASKIOS.MaskScreenFrameBuffer ;
	MASKIOS.MaskScreenOldTextureBuffer = MASKIOS.MaskScreenTextureBuffer ;
	MASKIOS.MaskScreenOldDepthBuffer   = MASKIOS.MaskScreenDepthBuffer ;

	if( MASKIOS.MaskImageTextureBuffer != 0 )
	{
		glDeleteTextures( 1, &MASKIOS.MaskImageTextureBuffer ) ;
		MASKIOS.MaskImageTextureBuffer = 0 ;
	}

	// ����I��
	return 0 ;
}

// �}�X�N�X�N���[�����쐬����֐�
extern	int			Mask_CreateScreenFunction_Timing1_PF( int Width, int Height )
{
	MASKIOS.MaskTextureSizeX = Width ;
	MASKIOS.MaskTextureSizeY = Height ;

	// �}�X�N�p�C���[�W�e�N�X�`���̍쐬
	if( MASKIOS.MaskImageTextureBuffer == 0 )
	{
		PIXELFORMAT_INFO_IOS *PixelFormat ;

		PixelFormat = &g_iOSPixelFormat[ GIOS.Device.Caps.MaskAlphaFormat ] ;
		glGenTextures( 1, &MASKIOS.MaskImageTextureBuffer ) ;
		glActiveTexture( GL_TEXTURE0 ) ;
		glBindTexture( GL_TEXTURE_2D, MASKIOS.MaskImageTextureBuffer ) ;

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ) ;

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ) ;

		if( PixelFormat->IsExtFormat )
		{
			glCompressedTexImage2D(
				GL_TEXTURE_2D,
				0,
				PixelFormat->InternalFormat,
				MASKIOS.MaskTextureSizeX,
				MASKIOS.MaskTextureSizeY,
				0,
				0,
				0
			) ;
		}
		else
		{
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				PixelFormat->InternalFormat,
				MASKIOS.MaskTextureSizeX,
				MASKIOS.MaskTextureSizeY,
				0,
				PixelFormat->Format,
				PixelFormat->Type,
				0
			) ;
		}

		// �}�X�N�p�C���[�W�̓]��
		{
			RECT SrcRect ;
			RECT DestRect ;
			BASEIMAGE MaskBaseImage ;
			BASEIMAGE AlphaBaseImage ;

			SrcRect.left   = 0 ;
			SrcRect.top    = 0 ;
			SrcRect.right  = MASKIOS.MaskTextureSizeX ;
			SrcRect.bottom = MASKIOS.MaskTextureSizeY ;
			DestRect = SrcRect ;

			_MEMSET( &AlphaBaseImage, 0, sizeof( AlphaBaseImage ) ) ;
			MaskBaseImage.ColorData			= *Graphics_iOS_GetDataFormatColorData( GIOS.Device.Caps.MaskAlphaFormat ) ;
			MaskBaseImage.Width				= MASKIOS.MaskTextureSizeX ;
			MaskBaseImage.Height			= MASKIOS.MaskTextureSizeY ;
			MaskBaseImage.Pitch				= MASKD.MaskBufferPitch ;
			MaskBaseImage.GraphData			= MASKD.MaskBuffer ;
			MaskBaseImage.MipMapCount		= 0 ;
			MaskBaseImage.GraphDataCount	= 0 ;

			Graphics_iOS_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
				&SrcRect,
				&DestRect,
				MASKIOS.MaskImageTextureBuffer,
				1,
				MASKIOS.MaskTextureSizeX,
				MASKIOS.MaskTextureSizeY,
				MASKIOS.MaskTextureSizeX,
				MASKIOS.MaskTextureSizeY,
				&MaskBaseImage,
				&AlphaBaseImage,
				GIOS.Device.Caps.MaskAlphaFormat,
				FALSE,
				FALSE,
				0,
				FALSE
			) ;
		}
	}

	// �}�X�N�p�X�N���[���e�N�X�`���̍쐬
	if( MASKIOS.MaskScreenFrameBuffer == 0 )
	{
		// Offscreen position framebuffer texture target
		glGenTextures( 1, &MASKIOS.MaskScreenTextureBuffer ) ;
		glActiveTexture( GL_TEXTURE0 ) ;
		glBindTexture( GL_TEXTURE_2D, MASKIOS.MaskScreenTextureBuffer ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ) ;
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ) ;
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, MASKIOS.MaskTextureSizeX, MASKIOS.MaskTextureSizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 0 ) ;

		glGenFramebuffers( 1, &MASKIOS.MaskScreenFrameBuffer ) ;
		glBindFramebuffer( GL_FRAMEBUFFER, MASKIOS.MaskScreenFrameBuffer ) ;

		// �����_�[�o�b�t�@���ʎq�𐶐����܂��B
		glGenRenderbuffers( 1, &MASKIOS.MaskScreenDepthBuffer ) ;

		// �����_�[�o�b�t�@���ʎq�ɑΉ����������_�[�o�b�t�@�I�u�W�F�N�g�𐶐����܂��B
		glBindRenderbuffer( GL_RENDERBUFFER, MASKIOS.MaskScreenDepthBuffer ) ;

		// �����_�[�o�b�t�@�̕��ƍ������w�肵�܂��B
		glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, MASKIOS.MaskTextureSizeX, MASKIOS.MaskTextureSizeY ) ;

		// �t���[���o�b�t�@�̃A�^�b�`�����g�Ƃ��ă����_�[�o�b�t�@���A�^�b�`���܂��B
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, MASKIOS.MaskScreenDepthBuffer ) ;

		// �t���[���o�b�t�@�̃A�^�b�`�����g�Ƃ��� 2D �e�N�X�`�����A�^�b�`���܂��B
		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, MASKIOS.MaskScreenTextureBuffer, 0 ) ;

		// �t���[���o�b�t�@�����S���ǂ����`�F�b�N���܂��B
		GLint status = glCheckFramebufferStatus( GL_FRAMEBUFFER ) ;
		if( status != GL_FRAMEBUFFER_COMPLETE )
		{
			DXST_LOGFILE_ADDUTF16LE( "\xde\x30\xb9\x30\xaf\x30\x28\x75\xd5\x30\xec\x30\xfc\x30\xe0\x30\xd0\x30\xc3\x30\xd5\x30\xa1\x30\x6e\x30\x5c\x4f\x10\x62\x6b\x30\x31\x59\x57\x65\x57\x30\x7e\x30\x57\x30\x5f\x30\x0a\x00\x00"/*@ L"�}�X�N�p�t���[���o�b�t�@�̍쐬�Ɏ��s���܂���\n" @*/ ) ;
			return -1 ;
		}
		glBindFramebuffer( GL_FRAMEBUFFER, 0 ) ;
	}

	// ����I��
	return 0 ;
}

// �}�X�N�X�N���[�����쐬����֐�
extern	int			Mask_CreateScreenFunction_Timing2_PF( int MaskBufferSizeXOld, int MaskBufferSizeYOld )
{
	RECT UpdateRect ;

	// �`����I�����Ă���
	Graphics_iOS_RenderEnd() ;

	// �}�X�N�p�C���[�W�̓]��
	{
		RECT SrcRect ;
		RECT DestRect ;
		BASEIMAGE MaskBaseImage ;
		BASEIMAGE AlphaBaseImage ;

		SrcRect.left   = 0 ;
		SrcRect.top    = 0 ;
		SrcRect.right  = MASKIOS.MaskTextureSizeX ;
		SrcRect.bottom = MASKIOS.MaskTextureSizeY ;
		DestRect = SrcRect ;

		_MEMSET( &AlphaBaseImage, 0, sizeof( AlphaBaseImage ) ) ;
		MaskBaseImage.ColorData			= *Graphics_iOS_GetDataFormatColorData( GIOS.Device.Caps.MaskAlphaFormat ) ;
		MaskBaseImage.Width				= MASKIOS.MaskTextureSizeX ;
		MaskBaseImage.Height			= MASKIOS.MaskTextureSizeY ;
		MaskBaseImage.Pitch				= MASKD.MaskBufferPitch ;
		MaskBaseImage.GraphData			= MASKD.MaskBuffer ;
		MaskBaseImage.MipMapCount		= 0 ;
		MaskBaseImage.GraphDataCount	= 0 ;

		Graphics_iOS_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
			&SrcRect,
			&DestRect,
			MASKIOS.MaskImageTextureBuffer,
			1,
			MASKIOS.MaskTextureSizeX,
			MASKIOS.MaskTextureSizeY,
			MASKIOS.MaskTextureSizeX,
			MASKIOS.MaskTextureSizeY,
			&MaskBaseImage,
			&AlphaBaseImage,
			GIOS.Device.Caps.MaskAlphaFormat,
			FALSE,
			FALSE,
			0,
			FALSE
		) ;
	}

	// �}�X�N�p�X�N���[���e�N�X�`���ɍ��܂ł̓��e��]��
	UpdateRect.left   = 0 ;
	UpdateRect.top    = 0 ;
	UpdateRect.right  = MaskBufferSizeXOld ;
	UpdateRect.bottom = MaskBufferSizeYOld ;
	Graphics_iOS_StretchRect(
		MASKIOS.MaskScreenOldTextureBuffer, MaskBufferSizeXOld,        MaskBufferSizeYOld,        &UpdateRect,
		MASKIOS.MaskScreenFrameBuffer,      MASKIOS.MaskTextureSizeX, MASKIOS.MaskTextureSizeY, &UpdateRect
	) ;

	// �����_�[�^�[�Q�b�g�ɂ���Ă�����ύX����
	if( GIOS.Device.State.TargetFrameBuffer == MASKIOS.MaskScreenOldFrameBuffer )
	{
		Graphics_iOS_DeviceState_SetRenderTarget( MASKIOS.MaskScreenFrameBuffer, MASKIOS.MaskTextureSizeX, MASKIOS.MaskTextureSizeY ) ;
	}

	// �ȑO�̃}�X�N�X�N���[�������J��
	{
		if( MASKIOS.MaskScreenOldFrameBuffer != 0 )
		{
			glDeleteFramebuffers( 1, &MASKIOS.MaskScreenOldFrameBuffer ) ;
			MASKIOS.MaskScreenOldFrameBuffer = 0 ;
		}

		if( MASKIOS.MaskScreenOldTextureBuffer != 0 )
		{
			glDeleteTextures( 1, &MASKIOS.MaskScreenOldTextureBuffer ) ;
			MASKIOS.MaskScreenOldTextureBuffer = 0 ;
		}

		if( MASKIOS.MaskScreenOldDepthBuffer != 0 )
		{
			glDeleteRenderbuffers( 1, &MASKIOS.MaskScreenOldDepthBuffer ) ;
			MASKIOS.MaskScreenOldDepthBuffer = 0 ;
		}
	}

	// ����I��
	return 0 ;
}

// �}�X�N�X�N���[�����ꎞ�폜����
extern	int			Mask_ReleaseSurface_PF( void )
{
	if( MASKIOS.MaskImageTextureBuffer != 0 )
	{
		glDeleteTextures( 1, &MASKIOS.MaskImageTextureBuffer ) ;
		MASKIOS.MaskImageTextureBuffer = 0 ;
	}

	if( MASKIOS.MaskScreenFrameBuffer != 0 )
	{
		glDeleteFramebuffers( 1, &MASKIOS.MaskScreenFrameBuffer ) ;
		MASKIOS.MaskScreenFrameBuffer = 0 ;
	}

	if( MASKIOS.MaskScreenTextureBuffer != 0 )
	{
		glDeleteTextures( 1, &MASKIOS.MaskScreenTextureBuffer ) ;
		MASKIOS.MaskScreenTextureBuffer = 0 ;
	}

	if( MASKIOS.MaskScreenDepthBuffer != 0 )
	{
		glDeleteRenderbuffers( 1, &MASKIOS.MaskScreenDepthBuffer ) ;
		MASKIOS.MaskScreenDepthBuffer = 0 ;
	}

	return 0 ;
}

// �}�X�N�g�p���[�h��ύX
extern	int			Mask_SetUseMaskScreenFlag_PF( void )
{
	IMAGEDATA     *Image     = NULL ;
	SHADOWMAPDATA *ShadowMap = NULL ;

	// �`���̉摜�f�[�^�A�h���X���擾����
	if( GSYS.DrawSetting.ShadowMapDrawSetupRequest )
	{
		ShadowMap = Graphics_ShadowMap_GetData( GSYS.DrawSetting.ShadowMapDrawHandle ) ;
	}
	else
	{
		Image = Graphics_Image_GetData( GSYS.DrawSetting.TargetScreen[ 0 ] ) ;
	}

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I������
	Graphics_iOS_RenderEnd() ;

	// �`����ύX����

	// �}�X�N�T�[�t�F�X�����݂��Ă��Ċ��L���ȏꍇ�̓}�X�N�T�[�t�F�X��`��Ώۂɂ���
	if( MASKD.MaskValidFlag && MASKIOS.MaskScreenFrameBuffer )
	{
		Graphics_iOS_DeviceState_SetRenderTarget( MASKIOS.MaskScreenFrameBuffer, MASKIOS.MaskTextureSizeX, MASKIOS.MaskTextureSizeY ) ;
	}
	else
	// �V���h�E�}�b�v���L���ȏꍇ�̓V���h�E�}�b�v��`��Ώۂɂ���
	if( ShadowMap )
	{
		Graphics_iOS_DeviceState_SetRenderTarget( ShadowMap->PF->FrameBuffer, ShadowMap->PF->Texture.Width, ShadowMap->PF->Texture.Height ) ;
	}
	else
	// �`��\�摜���L���ȏꍇ�͕`��\�摜��`��Ώۂɂ���
	if( Image )
	{
		if( Image->Hard.Draw[ 0 ].Tex->PF->MSRenderTarget != 0 )
		{
			Graphics_iOS_DeviceState_SetRenderTarget( Image->Hard.Draw[ 0 ].Tex->PF->MSRenderTarget, Image->Hard.Draw[ 0 ].Tex->PF->Texture.Width, Image->Hard.Draw[ 0 ].Tex->PF->Texture.Height ) ;
		}
		else
		{
			Graphics_iOS_DeviceState_SetRenderTarget( Image->Hard.Draw[ 0 ].Tex->PF->FrameBuffer, Image->Hard.Draw[ 0 ].Tex->PF->Texture.Width, Image->Hard.Draw[ 0 ].Tex->PF->Texture.Height ) ;
		}
	}
	else
	// ����ȊO�̏ꍇ�̓T�u�o�b�N�o�b�t�@��`��Ώۂɂ���
	{
		Graphics_iOS_DeviceState_SetRenderTarget( GIOS.Device.Screen.SubBackBufferFrameBuffer, GIOS.Device.Screen.SubBackBufferTextureSizeX, GIOS.Device.Screen.SubBackBufferTextureSizeY ) ;
	}

	// �g�p����y�o�b�t�@�̃Z�b�g�A�b�v
	Graphics_Screen_SetupUseZBuffer() ;

	// �r���[�|�[�g�����ɖ߂�
	GIOS.Device.DrawSetting.CancelSettingEqualCheck = TRUE ;
	Graphics_iOS_DeviceState_SetViewportEasy(
		GSYS.DrawSetting.DrawArea.left,
		GSYS.DrawSetting.DrawArea.top,
		GSYS.DrawSetting.DrawArea.right,
		GSYS.DrawSetting.DrawArea.bottom
	) ;
	GIOS.Device.DrawSetting.CancelSettingEqualCheck = FALSE ;

	// ����I��
	return 0 ;
}

// �}�X�N���g�p�����`��̑O�ɌĂԊ֐�( ���łɃT�u�o�b�t�@���g�p�����`��G���A�@�\���g�p���Ă���ꍇ�̏���������Ă��܂��Ă���� )
extern	int			Mask_DrawBeginFunction_PF( RECT *Rect )
{
	IMAGEDATA     *Image     = NULL ;
	SHADOWMAPDATA *ShadowMap = NULL ;

	// �`���̉摜�f�[�^�A�h���X���擾����
	if( GSYS.DrawSetting.ShadowMapDraw == FALSE )
	{
		ShadowMap = Graphics_ShadowMap_GetData( GSYS.DrawSetting.ShadowMapDrawHandle ) ;
	}
	else
	{
		Image = Graphics_Image_GetData( GSYS.DrawSetting.TargetScreen[ 0 ] ) ;
	}

	// �}�X�N���g�p���Ă���Ƃ��̂ݓ��ʂȏ���������
	if( MASKD.MaskValidFlag && MASKIOS.MaskScreenFrameBuffer )
	{
		// �ŏI�o�͐�̌���
		
		// �`��\�摜���`���̏ꍇ�͂�����A����ȊO�̏ꍇ�̓T�u�o�b�N�o�b�t�@���g�p���Ă���ꍇ�̓T�u�o�b�N�o�b�t�@���A
		// �����ł͂Ȃ��ꍇ�̓o�b�N�o�b�t�@���o�͐�ɂ���
		if( ShadowMap )
		{
			MASKIOS.DestTargetTextureBuffer = ShadowMap->PF->Texture.TextureBuffer ;
			MASKIOS.DestTargetFrameBuffer   = ShadowMap->PF->FrameBuffer ;
			MASKIOS.DestTargetWidth         = ShadowMap->PF->Texture.Width ;
			MASKIOS.DestTargetHeight        = ShadowMap->PF->Texture.Height ;
		}
		else
		if( Image )
		{
			MASKIOS.DestTargetTextureBuffer = Image->Hard.Draw[ 0 ].Tex->PF->Texture.TextureBuffer ;
			if( Image->Hard.Draw[ 0 ].Tex->PF->MSRenderTarget != 0 )
			{
				MASKIOS.DestTargetFrameBuffer = Image->Hard.Draw[ 0 ].Tex->PF->MSRenderTarget ;
			}
			else
			{
				MASKIOS.DestTargetFrameBuffer = Image->Hard.Draw[ 0 ].Tex->PF->FrameBuffer ;
			}
			MASKIOS.DestTargetWidth  = Image->Hard.Draw[ 0 ].Tex->PF->Texture.Width ;
			MASKIOS.DestTargetHeight = Image->Hard.Draw[ 0 ].Tex->PF->Texture.Height ;
		}
		else
		{
			MASKIOS.DestTargetTextureBuffer = GIOS.Device.Screen.SubBackBufferTexture ;
			MASKIOS.DestTargetFrameBuffer   = GIOS.Device.Screen.SubBackBufferFrameBuffer ;
			MASKIOS.DestTargetWidth         = GIOS.Device.Screen.SubBackBufferTextureSizeX ;
			MASKIOS.DestTargetHeight        = GIOS.Device.Screen.SubBackBufferTextureSizeY ;
		}

		// �ŏI�o�͐悩��}�X�N�X�N���[���Ɍ��݂̕`��󋵂��R�s�[����
		Graphics_iOS_StretchRect(
			MASKIOS.DestTargetTextureBuffer, MASKIOS.DestTargetWidth,  MASKIOS.DestTargetHeight, Rect,
			MASKIOS.MaskScreenFrameBuffer,   MASKIOS.MaskTextureSizeX, MASKIOS.MaskTextureSizeY, Rect
		) ; 
	}

	// ����I��
	return 0 ;
}

// �}�X�N���g�p�����`��̌�ɌĂԊ֐�( ���łɃT�u�o�b�t�@���g�p�����`��G���A�@�\���g�p���Ă���ꍇ�̏���������Ă��܂��Ă���� )
extern	int			Mask_DrawAfterFunction_PF( RECT *Rect )
{
	// �}�X�N���g�p���Ă���ꍇ�̂݃}�X�N�摜�ƍ������ē]��
	if( MASKD.MaskValidFlag && MASKIOS.MaskScreenFrameBuffer )
	{
		IMAGEDATA               *MaskScreenImage = NULL ;
		GLuint                  MaskImageTextureBuffer ;
		int						MaskImageTextureWidth ;
		int						MaskImageTextureHeight ;
		GRAPHICS_IOS_SHADER *MaskShader ;
		int                     AlphaBlend ;

		// �}�X�N�p�O���t�B�b�N�n���h�����L���ȏꍇ�̓}�X�N�p�O���t�B�b�N�n���h���̏����擾����
		if( MASKD.MaskScreenGraphHandle != 0 )
		{
			MaskScreenImage = Graphics_Image_GetData( MASKD.MaskScreenGraphHandle ) ;

			// ���ɖ����ɂȂ��Ă�����ݒ�� 0 �ɂ���
			if( MaskScreenImage == NULL )
			{
				MASKD.MaskScreenGraphHandle = 0 ;
			}
		}

		// �g�p����}�X�N�C���[�W�e�N�X�`�����Z�b�g
		if( MaskScreenImage != NULL )
		{
			MaskImageTextureBuffer = MaskScreenImage->Hard.Draw[ 0 ].Tex->PF->Texture.TextureBuffer ;
			MaskImageTextureWidth  = MaskScreenImage->Hard.Draw[ 0 ].Tex->PF->Texture.Width ;
			MaskImageTextureHeight = MaskScreenImage->Hard.Draw[ 0 ].Tex->PF->Texture.Height ;
			MaskShader     = MASKD.MaskReverseEffectFlag ?
				&GIOS.Device.Shader.Base.MaskEffect_UseGraphHandle_ReverseEffect_Shader[ MASKD.MaskScreenGraphHandleUseChannel ] :
				&GIOS.Device.Shader.Base.MaskEffect_UseGraphHandle_Shader[ MASKD.MaskScreenGraphHandleUseChannel ] ;
			AlphaBlend             = TRUE ;
		}
		else
		{
			MaskImageTextureBuffer = MASKIOS.MaskImageTextureBuffer ;
			MaskImageTextureWidth  = MASKIOS.MaskTextureSizeX ;
			MaskImageTextureHeight = MASKIOS.MaskTextureSizeY ;
			MaskShader             = MASKD.MaskReverseEffectFlag ? &GIOS.Device.Shader.Base.MaskEffect_ReverseEffect_Shader : &GIOS.Device.Shader.Base.MaskEffect_Shader ;
			AlphaBlend             = FALSE ;
		}

		Graphics_iOS_StretchRect(
			MASKIOS.MaskScreenTextureBuffer, MASKIOS.MaskTextureSizeX, MASKIOS.MaskTextureSizeY, Rect,
			MASKIOS.DestTargetFrameBuffer,   MASKIOS.DestTargetWidth,  MASKIOS.DestTargetHeight, Rect,
			GL_NEAREST,
			AlphaBlend,
			MaskShader,
			MaskImageTextureBuffer,           MaskImageTextureWidth,     MaskImageTextureHeight,    Rect
		) ;
	}

	return 0 ;
}

// �}�X�N�X�N���[�����w��̐F�œh��Ԃ�
extern	int			Mask_FillMaskScreen_PF( int Flag )
{
//	int i ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I������
	Graphics_iOS_RenderEnd() ;

	// �}�X�N�p�C���[�W�̓]��
	{
		RECT SrcRect ;
		RECT DestRect ;
		BASEIMAGE MaskBaseImage ;
		BASEIMAGE AlphaBaseImage ;

		SrcRect.left   = 0 ;
		SrcRect.top    = 0 ;
		SrcRect.right  = MASKIOS.MaskTextureSizeX ;
		SrcRect.bottom = MASKIOS.MaskTextureSizeY ;
		DestRect = SrcRect ;

		_MEMSET( &AlphaBaseImage, 0, sizeof( AlphaBaseImage ) ) ;
		MaskBaseImage.ColorData			= *Graphics_iOS_GetDataFormatColorData( GIOS.Device.Caps.MaskAlphaFormat ) ;
		MaskBaseImage.Width				= MASKIOS.MaskTextureSizeX ;
		MaskBaseImage.Height			= MASKIOS.MaskTextureSizeY ;
		MaskBaseImage.Pitch				= MASKD.MaskBufferPitch ;
		MaskBaseImage.GraphData			= MASKD.MaskBuffer ;
		MaskBaseImage.MipMapCount		= 0 ;
		MaskBaseImage.GraphDataCount	= 0 ;

		Graphics_iOS_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
			&SrcRect,
			&DestRect,
			MASKIOS.MaskImageTextureBuffer,
			1,
			MASKIOS.MaskTextureSizeX,
			MASKIOS.MaskTextureSizeY,
			MASKIOS.MaskTextureSizeX,
			MASKIOS.MaskTextureSizeY,
			&MaskBaseImage,
			&AlphaBaseImage,
			GIOS.Device.Caps.MaskAlphaFormat,
			FALSE,
			FALSE,
			0,
			FALSE
		) ;
	}

	return 0 ;
}

// �w��̈�̃}�X�N�C���[�W�e�N�X�`�����X�V����
extern	int			Mask_UpdateMaskImageTexture_PF( RECT *Rect )
{
//	int i ;

	// �`��ҋ@���Ă���`�敨��`��
	DRAWSTOCKINFO

	// �`����I������
	Graphics_iOS_RenderEnd() ;

	// �}�X�N�p�C���[�W�̓]��
	{
		BASEIMAGE MaskBaseImage ;
		BASEIMAGE AlphaBaseImage ;

		_MEMSET( &AlphaBaseImage, 0, sizeof( AlphaBaseImage ) ) ;
		MaskBaseImage.ColorData			= *Graphics_iOS_GetDataFormatColorData( GIOS.Device.Caps.MaskAlphaFormat ) ;
		MaskBaseImage.Width				= MASKIOS.MaskTextureSizeX ;
		MaskBaseImage.Height			= MASKIOS.MaskTextureSizeY ;
		MaskBaseImage.Pitch				= MASKD.MaskBufferPitch ;
		MaskBaseImage.GraphData			= MASKD.MaskBuffer ;
		MaskBaseImage.MipMapCount		= 0 ;
		MaskBaseImage.GraphDataCount	= 0 ;

		Graphics_iOS_BltBmpOrBaseImageToGraph3_NoMipMapBlt(
			Rect,
			Rect,
			MASKIOS.MaskImageTextureBuffer,
			1,
			MASKIOS.MaskTextureSizeX,
			MASKIOS.MaskTextureSizeY,
			MASKIOS.MaskTextureSizeX,
			MASKIOS.MaskTextureSizeY,
			&MaskBaseImage,
			&AlphaBaseImage,
			GIOS.Device.Caps.MaskAlphaFormat,
			FALSE,
			FALSE,
			0,
			FALSE
		) ;
	}

	return 0 ;
}






#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_MASK
