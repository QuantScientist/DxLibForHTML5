// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		Android�p�t�H���g�֌W�v���O�����w�b�_�t�@�C��
// 
// 				Ver 3.21d
// 
// -------------------------------------------------------------------------------

#ifndef DX_FONTANDROID_H
#define DX_FONTANDROID_H

#include "../DxCompileConfig.h"

#ifndef DX_NON_FONT

// �C���N���[�h ------------------------------------------------------------------
#include "../DxFile.h"
#include <ft2build.h>

#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H
#include FT_GLYPH_H
#include FT_TRUETYPE_IDS_H

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// �}�N����` --------------------------------------------------------------------

#define FSYSANDR			FontSystemAndroid

// �\���̒�` --------------------------------------------------------------------

/* Cached glyph information */
typedef struct cached_glyph {
    int stored;
    FT_UInt index;
    FT_Bitmap bitmap;
    FT_Bitmap pixmap;
    int minx;
    int maxx;
    int miny;
    int maxy;
    int yoffset;
    int advance;
    uint16_t cached;
} c_glyph;

// Android�p �t�H���g�L���b�V���̊��ˑ��Ǘ��f�[�^
struct FONTMANAGE_PF
{
   /* Freetype2 maintains all sorts of useful info itself */
    FT_Face face;

    /* We'll cache these ourselves */
    int width;
    int height;
    int ascent;
    int descent;
    int lineskip;

    /* The font style */
    int italic;
    int style;
    int outline;

    /* Whether kerning is desired */
    int kerning;

    /* Extra width in glyph bounds for text styles */
    int glyph_overhang;
    float glyph_italics;

    /* Information in the font for underlining */
    int underline_offset;
    int underline_height;

    /* We are responsible for closing the font stream */
    int src;
    int freesrc;
    FT_Open_Args args;

    /* For non-scalable formats, we must remember which font index size */
    int font_size_family;

    /* really just flags passed into FT_Load_Glyph */
    int hinting;
} ;

// Android�p �t�H���g�V�X�e���p�\����
struct FONTSYSTEM_ANDR
{
	int 					initialized;
	FT_Library 				library;
} ;

// �������ϐ��錾 --------------------------------------------------------------

extern FONTSYSTEM_ANDR FontSystemAndroid ;

// �֐��v���g�^�C�v�錾-----------------------------------------------------------

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

#endif // DX_NON_FONT

#endif // DX_FONTANDROID_H
