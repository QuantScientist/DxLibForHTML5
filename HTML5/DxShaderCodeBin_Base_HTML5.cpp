// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		固定機能パイプラインの代わり用シェーダーバイナリ
// 
// 				Ver 3.21f
// 
// -------------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

// インクルード----------------------------------------------------------------
#include "../DxLib.h"
#include "../DxStatic.h"

// データ定義------------------------------------------------------------------

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// シェーダーファイルを圧縮したもの
BYTE DxShaderCodeBin_Base_HTML5[] = 
{
	0xc7,0xda,0x03,0x00,0x63,0x11,0x00,0x00,0xfd,0x85,0x02,0x97,0x02,0xa9,0x02,0xb5,
	0x04,0x2b,0x05,0xa1,0x05,0xa1,0x05,0x14,0x01,0x1b,0x03,0x42,0x01,0x49,0x03,0x39,
	0x01,0x40,0x03,0x29,0x01,0x30,0x03,0x2c,0x01,0x33,0x03,0x51,0x01,0x58,0x03,0x41,
	0x01,0x48,0x03,0xa1,0x01,0xa8,0x03,0xb6,0x01,0xbd,0x03,0xdd,0x01,0xe4,0x03,0xf2,
	0x01,0xf9,0x03,0xcf,0x01,0xd6,0x03,0xe4,0x01,0xeb,0x03,0x0b,0x02,0x12,0x04,0x20,
	0x02,0x27,0x04,0xc7,0x01,0xce,0x03,0xdc,0x01,0xe3,0x03,0x03,0x02,0x0a,0x04,0x18,
	0x02,0x1f,0x04,0xfd,0x00,0x2b,0xcb,0x01,0xd2,0xfd,0x08,0x2b,0x07,0x02,0x0e,0x04,
	0xb9,0x01,0xc0,0x03,0xce,0x01,0xd5,0x03,0xf5,0x01,0xfc,0x03,0x0a,0x02,0x11,0x04,
	0xdf,0x01,0xe6,0x03,0xf4,0x01,0xfb,0x03,0x1b,0x02,0x22,0x04,0x30,0x02,0x37,0x04,
	0xfd,0x00,0x1b,0xe3,0x01,0xea,0xfd,0x08,0x1b,0x1f,0x02,0x26,0x04,0x95,0x02,0x9c,
	0x04,0xaa,0x02,0xb1,0x04,0xd1,0x02,0xd8,0x04,0xe6,0x02,0xed,0x04,0xc3,0x02,0xca,
	0x04,0xd8,0x02,0xdf,0x04,0xff,0x02,0x06,0x05,0x14,0x03,0x1b,0x05,0xbb,0x02,0xc2,
	0x04,0xd0,0x02,0xd7,0x04,0xf7,0x02,0xfe,0x04,0x0c,0x03,0x13,0x05,0xfd,0x00,0x2b,
	0xbf,0x02,0xc6,0xfd,0x08,0x2b,0xfb,0x02,0x02,0x05,0xc5,0x03,0xcc,0x05,0xda,0x03,
	0xe1,0x05,0x01,0x04,0x08,0x06,0x16,0x04,0x1d,0x06,0xeb,0x03,0xf2,0x05,0x00,0x04,
	0x07,0x06,0x27,0x04,0x2e,0x06,0x3c,0x04,0x43,0x06,0xfd,0x00,0x1b,0xef,0x03,0xf6,
	0x05,0xfd,0x00,0x1b,0x2b,0x04,0x32,0x06,0xb8,0x02,0xbf,0x04,0xcd,0x02,0xd4,0x04,
	0xf4,0x02,0xfb,0x04,0x09,0x03,0x10,0x05,0xfd,0x20,0x47,0x22,0x03,0x29,0x05,0x37,
	0x03,0x3e,0x05,0xde,0x02,0xe5,0x04,0xf3,0x02,0xfa,0x04,0x1a,0x03,0x21,0x05,0x2f,
	0x03,0x36,0x05,0xfd,0x00,0x2b,0xe2,0x02,0xe9,0xfd,0x08,0x2b,0x1e,0x03,0x25,0x05,
	0xec,0x03,0xf3,0xfd,0x08,0x6b,0x28,0x04,0x2f,0x06,0x3d,0x04,0x44,0x06,0x12,0x04,
	0x19,0xfd,0x08,0x6b,0x4e,0x04,0x55,0x06,0x63,0x04,0x6a,0x06,0xfd,0x20,0x87,0xfd,
	0x00,0x1b,0x52,0x04,0x59,0x06,0x81,0x02,0x88,0x04,0x96,0x02,0x9d,0x04,0xbd,0x02,
	0xc4,0x04,0xd2,0x02,0xd9,0x04,0xaf,0x02,0xb6,0x04,0xc4,0x02,0xcb,0x04,0xeb,0x02,
	0xf2,0x04,0x00,0x03,0x07,0x05,0xa7,0x02,0xae,0x04,0xbc,0x02,0xc3,0x04,0xe3,0x02,
	0xea,0x04,0xf8,0x02,0xff,0xfd,0x08,0x2b,0xab,0x02,0xb2,0xfd,0x08,0x2b,0xe7,0x02,
	0xee,0x04,0xb1,0x03,0xb8,0x05,0xc6,0x03,0xcd,0x05,0xed,0x03,0xf4,0x05,0x02,0x04,
	0x09,0x06,0xd7,0x03,0xde,0xfd,0x08,0x83,0x13,0x04,0x1a,0xfd,0x08,0x83,0xfd,0x00,
	0x1b,0xdb,0x03,0xe2,0xfd,0x08,0x1b,0x17,0x04,0x1e,0x06,0x5b,0x01,0x58,0x01,0x5a,
	0x01,0xbc,0xfd,0x18,0x01,0xb6,0xfd,0x18,0x01,0x01,0x01,0x57,0x01,0x6b,0x03,0x9b,
	0x00,0xab,0x00,0x6d,0x00,0xfd,0x00,0x00,0x61,0x74,0x74,0x72,0x69,0x62,0x75,0x74,
	0x65,0x20,0x68,0x69,0x67,0x68,0x70,0x20,0x76,0x65,0x63,0x34,0x20,0x61,0x50,0x6f,
	0x73,0x46,0x34,0x20,0x3b,0x0a,0xfd,0x30,0x1d,0x6c,0x6f,0x77,0xfd,0x20,0x1c,0x44,
	0x69,0x66,0x20,0x3b,0x20,0x20,0x20,0x0a,0x75,0x6e,0x69,0x66,0x6f,0x72,0x6d,0x20,
	0xfd,0x40,0x3a,0x75,0x41,0x6e,0x74,0x69,0x56,0x50,0x4d,0x61,0x74,0x5b,0x20,0x34,
	0x20,0x5d,0x20,0x3b,0x0a,0x76,0x61,0x72,0x79,0x69,0x6e,0x67,0x20,0xfd,0x38,0x42,
	0x76,0xfd,0x08,0x42,0xfd,0x30,0x19,0x6d,0x65,0x64,0x69,0x75,0x6d,0xfd,0x08,0x1c,
	0x32,0x20,0x76,0x54,0x65,0x78,0x55,0x56,0x30,0xfd,0xd8,0x1f,0x31,0xfd,0x00,0x1f,
	0x6f,0x69,0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,0x20,0xfd,0x08,0x0a,0x29,0x0a,0x7b,
	0x0a,0xfd,0x40,0x8b,0x6c,0x50,0x6f,0x73,0x20,0x3b,0xfd,0x50,0x12,0x41,0x56,0xfd,
	0x18,0x14,0xfd,0x00,0x01,0xfd,0x08,0x87,0x3d,0xfd,0x18,0xd1,0x0a,0xfd,0x20,0x79,
	0x2e,0x78,0x20,0x3d,0x20,0x30,0x2e,0xfd,0x00,0x81,0xfd,0x28,0x12,0x79,0xfd,0x60,
	0x12,0x31,0xfd,0x70,0x25,0x31,0xfd,0x40,0x25,0xfd,0x08,0x7b,0x3d,0xfd,0x31,0x49,
	0x01,0xfd,0x08,0x10,0x2e,0x77,0x20,0x3d,0x20,0x31,0x2e,0x30,0x20,0x2f,0xfd,0x20,
	0x0e,0xfd,0x20,0x18,0x78,0x20,0x2a,0x3d,0xfd,0x60,0x13,0x79,0xfd,0x78,0x13,0x7a,
	0xfd,0x50,0x13,0x0a,0xfd,0x18,0xd0,0xfd,0x08,0x8c,0x64,0x6f,0x74,0x28,0xfd,0x08,
	0x1b,0x2c,0xfd,0x49,0x85,0x01,0x30,0x20,0x5d,0x20,0x29,0xfd,0x08,0x40,0xfd,0x10,
	0x2a,0xfd,0x00,0xa4,0xfd,0x98,0x2a,0x31,0xfd,0x58,0x2a,0x7a,0xfd,0xb0,0x2a,0x32,
	0xfd,0x58,0x2a,0xfd,0x00,0xd9,0xfd,0x98,0x2a,0x33,0xfd,0x20,0x2a,0x67,0x6c,0x5f,
	0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x20,0x3d,0xfd,0x31,0x8a,0x01,0x7d,0xfd,
	0x39,0x66,0x02,0xfd,0x75,0x01,0x84,0x02,0xfd,0x30,0x1d,0xfd,0x49,0x25,0x02,0x61,
	0xfd,0x21,0x45,0x02,0xfd,0xb5,0x06,0xa7,0x02,0xfd,0x00,0x11,0xfd,0x28,0x83,0xfd,
	0x7d,0x0d,0x96,0x02,0xfd,0xc8,0x22,0x31,0xfd,0x6d,0x07,0xb9,0x02,0xfd,0x28,0x14,
	0xfd,0x00,0x78,0xfd,0xed,0x09,0xa8,0x02,0x33,0xfd,0x09,0x3a,0x01,0xfd,0xb1,0x67,
	0x02,0xfd,0x41,0xab,0x02,0xfd,0x81,0x05,0x02,0xfd,0x21,0x42,0x02,0xfd,0xa0,0x1f,
	0xfd,0x39,0x45,0x02,0xfd,0xd8,0x21,0xfd,0xb9,0xc9,0x02,0x4c,0x57,0xfd,0x28,0xe0,
	0xfd,0xa8,0x23,0x56,0x69,0x65,0x77,0xfd,0xf0,0x25,0x50,0x72,0x6f,0x6a,0xfd,0x31,
	0x11,0x03,0xfd,0x40,0x25,0xfd,0x48,0xd3,0x75,0x54,0x65,0x78,0xfd,0x08,0x26,0x36,
	0x20,0xfd,0x08,0x27,0xfd,0xe9,0xe0,0x02,0x20,0x20,0x20,0x6c,0x4c,0x6f,0x63,0x61,
	0xfd,0x79,0xe8,0x02,0xfd,0x00,0x1a,0x57,0x6f,0x72,0x6c,0x64,0xfd,0x90,0x1a,0xfd,
	0x00,0xb7,0xfd,0x18,0x19,0xfd,0x48,0x82,0xfd,0x00,0x1b,0xfd,0x09,0x17,0x01,0x54,
	0x65,0x6d,0x70,0xfd,0x19,0x83,0x02,0xfd,0x20,0x61,0x2e,0x78,0x79,0x7a,0x20,0x20,
	0xfd,0x19,0xf6,0x02,0xfd,0x00,0x1b,0xfd,0x30,0x19,0x77,0xfd,0x00,0x38,0xfd,0x19,
	0xfd,0x02,0xfd,0x10,0x34,0xfd,0x20,0x7b,0x2e,0x78,0xfd,0x18,0x1a,0xfd,0x11,0x3e,
	0x02,0xfd,0x20,0x31,0x2c,0xfd,0x29,0x5e,0x01,0xfd,0x31,0xc0,0x02,0xfd,0x28,0x32,
	0x79,0xfd,0xd8,0x32,0xfd,0x31,0xc8,0x02,0xfd,0x28,0x32,0xfd,0x00,0x98,0xfd,0xc0,
	0x32,0xfd,0x31,0xd0,0x02,0xfd,0x28,0x32,0xfd,0x38,0xb3,0xfd,0x10,0xb2,0xfd,0x19,
	0x13,0x01,0xfd,0x18,0xb1,0xfd,0x28,0x4c,0xfd,0x20,0x30,0x2c,0xfd,0x39,0xed,0x01,
	0xfd,0x30,0xb4,0xfd,0x20,0x34,0xfd,0x10,0xb3,0xfd,0xc8,0x34,0xfd,0x30,0xb6,0xfd,
	0x20,0x34,0xfd,0x10,0xb5,0xfd,0xc8,0x34,0xfd,0x30,0xb8,0xfd,0x20,0x34,0xfd,0x10,
	0xb7,0xfd,0x38,0xb8,0xfd,0x39,0x78,0x03,0xfd,0x39,0x29,0x04,0xfd,0x18,0x2e,0x2c,
	0xfd,0x39,0x7d,0x02,0xfd,0x28,0xb5,0xfd,0x40,0x31,0xfd,0x31,0x30,0x04,0xfd,0x78,
	0x31,0xfd,0x28,0xb2,0xfd,0x40,0x31,0xfd,0x31,0x37,0x04,0xfd,0x78,0x31,0xfd,0x28,
	0xaf,0xfd,0x40,0x31,0xfd,0x31,0x3e,0x04,0xfd,0x78,0x31,0xfd,0x29,0x40,0x04,0xfd,
	0x19,0x8f,0x05,0xfd,0x08,0xdb,0xfd,0x21,0x92,0x05,0xfd,0x31,0x8c,0x02,0xfd,0x08,
	0x76,0xfd,0x19,0x5f,0x02,0xfd,0x38,0x15,0xfd,0x21,0x73,0x05,0xfd,0x55,0x02,0x20,
	0x0b,0xfd,0xed,0x01,0xb4,0x04,0xfd,0xf9,0x60,0x07,0xfd,0x2d,0x21,0xd7,0x04,0xfd,
	0x38,0x15,0x78,0xfd,0x00,0xd5,0xfd,0x69,0x9c,0x0a,0xfd,0x11,0xf2,0x04,0xfd,0x10,
	0x88,0xfd,0x28,0x2b,0x2c,0xfd,0x31,0x76,0x03,0xfd,0x29,0x1f,0x01,0xfd,0x41,0x0e,
	0x05,0xfd,0xb0,0x2e,0xfd,0x29,0x1c,0x01,0xfd,0x2d,0x04,0x2a,0x05,0xfd,0xf9,0x8b,
	0x0c,0xfd,0xf5,0x24,0x4d,0x05,0xfd,0x90,0x78,0xfd,0x09,0x4e,0x10,0xfd,0x41,0x68,
	0x05,0xfd,0x2c,0x01,0x78,0xfd,0x11,0x84,0x05,0xfd,0xf0,0x78,0xfd,0xfe,0x2c,0xa0,
	0x05,0x70,0x72,0x65,0x63,0x69,0x73,0xfd,0x01,0x38,0x15,0xfd,0x21,0xc5,0x03,0x66,
	0x6c,0x6f,0x61,0x74,0x3b,0xfd,0x29,0x60,0x04,0xfd,0x09,0x3a,0x17,0xfd,0x08,0x13,
	0x20,0x75,0x41,0x54,0x65,0x73,0x74,0x52,0x65,0xfd,0x41,0x40,0x17,0xfd,0x71,0x59,
	0x17,0xfd,0x01,0x66,0x04,0x41,0x6c,0x70,0x68,0x61,0xfd,0x00,0x2c,0x28,0xfd,0x40,
	0x3f,0x69,0x6e,0xfd,0x08,0x17,0xfd,0x11,0x84,0x04,0x69,0x66,0x28,0xfd,0x28,0x10,
	0x3c,0x3d,0xfd,0x38,0x5b,0x29,0x0a,0x20,0x7b,0x0a,0x20,0x20,0x64,0x69,0x73,0x63,
	0x61,0x72,0x64,0xfd,0x00,0xd3,0x7d,0x0a,0x7d,0xfd,0x91,0xc8,0x04,0xfd,0x30,0x7c,
	0x6c,0x43,0x6f,0x6c,0x6f,0x72,0xfd,0x00,0x2c,0xfd,0x18,0x09,0x3d,0xfd,0x20,0x8f,
	0xfd,0x48,0x8b,0xfd,0x08,0x1b,0x2e,0x61,0x20,0x29,0xfd,0x11,0x5e,0x02,0x46,0x72,
	0x61,0x67,0xfd,0x20,0x2e,0xfd,0x28,0x41,0xfd,0xb5,0x01,0x13,0x01,0xfd,0x20,0x1e,
	0x69,0x6e,0x74,0xfd,0x01,0x83,0x02,0xfd,0x10,0x1a,0x43,0x6d,0x70,0x4d,0x6f,0x64,
	0x65,0xfd,0x05,0x02,0x32,0x01,0xfd,0x11,0x34,0x01,0xfd,0x50,0x56,0x3d,0x3d,0x20,
	0x32,0xfd,0x21,0x32,0x01,0xfd,0x41,0x52,0x01,0x3e,0xfd,0x59,0x52,0x01,0xfd,0x08,
	0x20,0xfd,0x41,0x54,0x01,0x20,0x7d,0xfd,0x01,0x58,0x01,0x20,0x65,0x6c,0x73,0x65,
	0xfd,0xa8,0x59,0x33,0xfd,0x80,0x59,0x21,0xfd,0x04,0x02,0x59,0x34,0xfd,0x88,0xb3,
	0xfd,0x21,0x33,0x01,0xfd,0xc4,0x01,0x59,0x35,0xfd,0x80,0x59,0xfd,0x61,0x60,0x02,
	0xfd,0x8c,0x01,0x59,0x36,0xfd,0x80,0x59,0x3d,0xfd,0x04,0x02,0x59,0x37,0xfd,0x88,
	0xb3,0xfd,0x15,0x01,0x0d,0x01,0xfd,0x15,0x05,0x1a,0x03,0xfd,0x35,0x05,0x2e,0x04,
	0xfd,0x28,0x10,0xfd,0x21,0x13,0x01,0x20,0x2d,0xfd,0x09,0x1e,0x06,0x29,0x20,0x2a,
	0xfd,0x31,0x24,0x01,0x2b,0xfd,0x21,0x31,0x06,0xfd,0xbd,0x18,0x5c,0x04,0xfd,0xa5,
	0x04,0x48,0x03,0xfd,0xdd,0x04,0x8a,0x04,0x2e,0x72,0x67,0x62,0xfd,0x19,0x91,0x0a,
	0x2d,0xfd,0x08,0x99,0xfd,0x08,0x10,0xfd,0x30,0x1e,0x61,0xfd,0x09,0xdd,0x0a,0xfd,
	0x08,0x18,0x61,0xfd,0x85,0x18,0x81,0x04,0xfd,0xb5,0x04,0x3f,0x03,0xfd,0x65,0x05,
	0x03,0x09,0xfd,0x09,0x38,0x01,0x2a,0x3d,0x20,0x34,0xfd,0x1d,0x19,0xea,0x08,0xfd,
	0xad,0x03,0x2f,0x03,0xfd,0xa5,0x05,0x58,0x04,0xfd,0xb5,0x18,0xc4,0x08,0xfd,0x4d,
	0x04,0x32,0x03,0xfd,0x5d,0x06,0x30,0x0d,0xfd,0x25,0x19,0x83,0x04,0xfd,0x75,0x05,
	0x57,0x03,0xfd,0xf5,0x05,0x07,0x09,0xfd,0xd5,0x19,0x78,0x0d,0xfd,0x75,0x03,0x47,
	0x03,0x73,0x61,0x6d,0x70,0x6c,0x65,0x72,0x32,0x44,0x20,0x20,0x75,0x53,0x72,0x63,
	0x54,0x65,0x78,0xfd,0x39,0x45,0x03,0xfd,0x6d,0x01,0xa5,0x04,0xfd,0x18,0x18,0xfd,
	0xa1,0x92,0x36,0xfd,0x95,0x03,0xc4,0x04,0x54,0x65,0x78,0xfd,0x31,0x7f,0x01,0xfd,
	0x81,0x93,0x01,0xfd,0x28,0x20,0x3d,0x20,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x32,
	0x44,0x28,0xfd,0x21,0x0e,0x01,0x2c,0xfd,0x28,0xc0,0xfd,0x11,0xe7,0x20,0xfd,0x20,
	0x29,0xfd,0x30,0x35,0x2a,0xfd,0xd1,0x8d,0x1c,0xfd,0x19,0x08,0x22,0xfd,0x45,0x03,
	0xa0,0x01,0xfd,0xad,0x01,0x05,0x05,0xfd,0x15,0x02,0xbf,0x01,0xfd,0x9d,0x11,0x24,
	0x05,0xfd,0x75,0x07,0xa7,0x03,0xfd,0xad,0x08,0x48,0x05,0xfd,0x29,0x95,0x01,0xfd,
	0xe9,0x86,0x0b,0xfd,0x7d,0x1c,0x5d,0x05,0xfd,0xcd,0x04,0xbc,0x03,0xfd,0xcd,0x07,
	0x72,0x05,0xfd,0x20,0x2c,0x2e,0xfd,0x00,0x2e,0xfd,0x11,0x3a,0x2d,0xfd,0x30,0x13,
	0x67,0xfd,0x78,0x13,0xfd,0x19,0x3e,0x11,0xfd,0x45,0x1d,0xf7,0x0a,0xfd,0xe5,0x06,
	0xe3,0x03,0xfd,0x8d,0x0a,0xc0,0x05,0xfd,0xed,0x1c,0x6f,0x0b,0xfd,0x8d,0x07,0xf8,
	0x03,0xfd,0xdd,0x08,0x1e,0x11,0xfd,0xcd,0x01,0x98,0x2e,0xfd,0xad,0x1c,0x37,0x11,
	0xfd,0x65,0x05,0xd5,0x03,0xfd,0x55,0x09,0xc3,0x16,0xfd,0xc5,0x1e,0xb9,0x05,0xfd,
	0x0d,0x06,0xea,0x03,0xfd,0xbd,0x0a,0x5e,0x11,0xfd,0x85,0x1d,0xf5,0x05,0xfd,0x55,
	0x08,0x11,0x04,0xfd,0x35,0x0b,0x7b,0x17,0xfd,0xa5,0x20,0x31,0x06,0xfd,0x45,0x0e,
	0x63,0x0c,0xfd,0x39,0x9c,0x34,0xfd,0x48,0x15,0xfd,0x95,0x1d,0x6d,0x23,0xfd,0xe5,
	0x05,0xcd,0x03,0xfd,0xdd,0x09,0x94,0x05,0xfd,0x3d,0x1d,0x41,0x23,0xfd,0x8d,0x06,
	0xe2,0x03,0xfd,0xad,0x09,0x9a,0x11,0xfd,0xa5,0x1e,0x8f,0x0b,0xfd,0xc5,0x07,0x09,
	0x04,0xfd,0xbd,0x0b,0x0c,0x06,0xfd,0xcd,0x1e,0x49,0x2f,0xfd,0xc5,0x0e,0x43,0x0c,
	0xfd,0xf9,0xb5,0x01,0xfd,0xf9,0x8c,0x47,0xfd,0xb5,0x1c,0x9c,0x29,0xfd,0x95,0x04,
	0xbc,0x03,0xfd,0x85,0x09,0x3d,0x2f,0xfd,0xd5,0x1d,0x87,0x05,0xfd,0x3d,0x05,0xd1,
	0x03,0xfd,0xc5,0x0a,0xee,0x28,0xfd,0xb5,0x1c,0xc3,0x05,0xfd,0x8d,0x07,0xf8,0x03,
	0xfd,0x65,0x0b,0xd9,0x2e,0xfd,0xb5,0x1f,0xff,0x05,0xfd,0x25,0x0d,0xff,0x0b,0xfd,
	0x35,0x01,0xca,0x07,0xfd,0xad,0x1d,0xa1,0x57,0xfd,0xad,0x04,0xbf,0x03,0xfd,0xc5,
	0x09,0x15,0x17,0xfd,0x1d,0x1e,0x2f,0x5d,0xfd,0xcd,0x0c,0xa2,0x05,0xfd,0x15,0x03,
	0x22,0x13,0xfd,0x8d,0x1f,0x89,0x57,0xfd,0x8d,0x0f,0xf0,0x05,0xfd,0x75,0x1d,0xcf,
	0x0b,0xfd,0x4d,0x08,0x10,0x04,0xfd,0x15,0x0a,0x3a,0x40,0xfd,0x1d,0x1d,0xef,0x05,
	0xfd,0xa5,0x06,0xe5,0x03,0xfd,0x85,0x0a,0xff,0x45,0xfd,0x4d,0x1f,0xd9,0x05,0xfd,
	0x1d,0x0f,0xbf,0x17,0xfd,0x65,0x1f,0xef,0x0b,0xfd,0x85,0x08,0x21,0x04,0xfd,0x65,
	0x0c,0x5f,0x46,0xfd,0x2d,0x21,0x51,0x06,0xfd,0x3d,0x0d,0xa3,0x0c,0xfd,0x85,0x01,
	0x1f,0x08,0xfd,0x3d,0x1e,0xa7,0x46,0xfd,0x1d,0x0e,0x22,0x35,0xfd,0x15,0x01,0x70,
	0x07,0xfd,0xe5,0x1e,0xd7,0x46,0xfd,0x35,0x10,0xef,0x46,0xfd,0x35,0x20,0x07,0x41,
	0xfd,0x35,0x10,0x1a,0x06,0xfd,0x1d,0x1e,0x23,0x0c,0xfd,0x3d,0x08,0x25,0x04,0xfd,
	0x40,0x1c,0x42,0x6c,0x65,0x6e,0x64,0xfd,0x79,0x44,0x04,0xfd,0x11,0xed,0xc7,0x46,
	0x61,0x63,0x74,0x6f,0x72,0xfd,0x20,0x77,0xfd,0xa5,0x02,0x84,0x06,0xfd,0xb0,0x1e,
	0xfd,0x29,0x09,0xdb,0xfd,0x7d,0x04,0xa3,0x06,0xfd,0x28,0x13,0xfd,0x21,0x42,0x01,
	0xfd,0x28,0x1a,0xfd,0x50,0x10,0xfd,0x21,0x0b,0xc7,0xfd,0x41,0xa2,0x02,0xfd,0x20,
	0x21,0xfd,0xa1,0xa4,0x02,0xfd,0x18,0x34,0xfd,0x68,0x38,0xfd,0x29,0xcd,0x01,0xfd,
	0x20,0x38,0x31,0xfd,0x59,0x01,0x0f,0x28,0x20,0x28,0xfd,0x58,0x7e,0xfd,0x39,0x89,
	0x1a,0xfd,0x09,0x77,0x78,0xfd,0x41,0xd3,0x01,0xfd,0x09,0x7d,0x78,0xfd,0x50,0x1e,
	0xfd,0xad,0x03,0x2b,0x67,0xfd,0x9d,0x02,0x94,0x02,0xfd,0xa5,0x02,0xfa,0x06,0xfd,
	0x15,0x02,0xb3,0x02,0xfd,0xa5,0x12,0x19,0x07,0xfd,0x15,0x0d,0x9b,0x04,0xfd,0x4d,
	0x0e,0x30,0x07,0xfd,0x15,0x04,0x3a,0x68,0xfd,0x3d,0x21,0x45,0x07,0xfd,0xcd,0x06,
	0xb0,0x04,0xfd,0xc5,0x0b,0x5a,0x07,0xfd,0x05,0x02,0x69,0x11,0xfd,0x85,0x24,0xc7,
	0x0e,0xfd,0x8d,0x0a,0xd7,0x04,0xfd,0x2d,0x10,0xa8,0x07,0xfd,0xe5,0x22,0x3f,0x0f,
	0xfd,0x35,0x0b,0xec,0x04,0xfd,0x7d,0x0e,0xd6,0x16,0xfd,0xad,0x04,0xc2,0x96,0xfd,
	0x6d,0x21,0xef,0x16,0xfd,0x65,0x07,0xc9,0x04,0xfd,0xf5,0x0e,0x63,0x1e,0xfd,0x65,
	0x26,0xa1,0x07,0xfd,0x0d,0x08,0xde,0x04,0xfd,0x5d,0x10,0x16,0x17,0xfd,0x7d,0x23,
	0xdd,0x07,0xfd,0xfe,0x0b,0x05,0x05,0xfd,0xd5,0x10,0x1b,0x1f,0xfd,0x45,0x28,0x19,
	0x08,0xfd,0x3d,0x14,0x33,0x10,0xfd,0x05,0x01,0x02,0x58,0xfd,0xd5,0x24,0xdd,0x2e,
	0xfd,0x8d,0x09,0xc1,0x04,0xfd,0x7d,0x0f,0x7c,0x07,0xfd,0x35,0x23,0xb1,0x2e,0xfd,
	0x35,0x0a,0xd6,0x04,0xfd,0xa5,0x0d,0x52,0x17,0xfd,0x45,0x26,0x5f,0x0f,0xfd,0x6d,
	0x0b,0xfd,0x04,0xfd,0x5d,0x11,0xf4,0x07,0xfd,0xc5,0x24,0x89,0x3e,0xfd,0x65,0x16,
	0x13,0x10,0xfd,0xa5,0x02,0xa9,0x02,0xfd,0x95,0x06,0x61,0x5f,0xfd,0xbd,0x1e,0xf4,
	0x36,0xfd,0xfe,0x14,0x12,0x64,0xfd,0xbd,0x04,0x21,0xae,0xfd,0x15,0x22,0x64,0x3e,
	0xfd,0x7d,0x12,0x84,0x07,0xfd,0x85,0x04,0x2b,0x31,0xfd,0xad,0x22,0xab,0x07,0xfd,
	0x35,0x0b,0xec,0x04,0xfd,0x05,0x11,0x19,0x3e,0xfd,0x55,0x27,0xe7,0x07,0xfd,0x85,
	0x0f,0xcf,0x0f,0xfd,0x30,0x1a,0x50,0x72,0x65,0x6d,0x75,0xfd,0x28,0x4a,0xfd,0x78,
	0x1a,0xfd,0x68,0x3b,0xfd,0x80,0x16,0xfd,0x0d,0x01,0x36,0x03,0xfd,0x50,0x6a,0xfd,
	0x81,0x6f,0x03,0xfd,0x21,0x34,0x03,0x20,0xfd,0x51,0x36,0x03,0xfd,0x91,0xa8,0x03,
	0xfd,0x80,0x87,0x2f,0xfd,0x80,0x15,0x2e,0x61,0xfd,0x60,0x43,0xfd,0x0a,0x20,0x27,
	0x01,0xfd,0x98,0x43,0xfd,0x08,0x2d,0xfd,0x91,0xe1,0x03,0xfd,0x80,0xc0,0xfd,0x20,
	0x71,0xfd,0x90,0x3e,0xfd,0x18,0x68,0xfd,0x80,0x3e,0xfd,0x10,0x28,0xfd,0xdd,0x02,
	0xbc,0x0b,0xfd,0x29,0xad,0x03,0xfd,0xbd,0x1e,0xc6,0x08,0xfd,0xc5,0x15,0xcb,0x05,
	0xfd,0x35,0x17,0x90,0x09,0xfd,0xc1,0x65,0x0d,0xfd,0x0d,0x2e,0xa5,0x09,0xfd,0x65,
	0x07,0xe0,0x05,0xfd,0x75,0x14,0xba,0x09,0xfd,0xbd,0x04,0x44,0x1f,0xfd,0x4d,0x2b,
	0xe1,0x09,0xfd,0x5d,0x0b,0x07,0x06,0xfd,0x15,0x19,0x08,0x0a,0xfd,0x2d,0x2c,0xff,
	0x13,0xfd,0x05,0x0c,0x1c,0x06,0xfd,0xc5,0x14,0x32,0x0a,0xfd,0x85,0x03,0x1d,0x4a,
	0xfd,0xd5,0x2b,0x07,0x0a,0xfd,0x5d,0x0a,0xf1,0x05,0xfd,0x65,0x18,0xdc,0x09,0xfd,
	0x7d,0x2c,0xf9,0x13,0xfd,0x05,0x0b,0x06,0x06,0xfd,0x55,0x16,0x16,0x1e,0xfd,0xc5,
	0x2f,0x1f,0x14,0xfd,0x3d,0x0c,0x2d,0x06,0xfd,0x45,0x1a,0x54,0x0a,0xfd,0x0d,0x2e,
	0x91,0x28,0xfd,0xe5,0x1f,0xd3,0x14,0xfd,0x15,0x03,0xfc,0x5b,0xfd,0xb5,0x2e,0x54,
	0x50,0xfd,0x2d,0x07,0xe0,0x05,0xfd,0x15,0x18,0x69,0x50,0xfd,0xb5,0x2e,0xcf,0x09,
	0xfd,0x0d,0x08,0xf5,0x05,0xfd,0x4d,0x19,0x93,0x50,0xfd,0xf5,0x2b,0x0b,0x0a,0xfd,
	0x05,0x0c,0x1c,0x06,0xfd,0xf5,0x19,0xbd,0x50,0xfd,0x95,0x30,0x47,0x0a,0xfd,0x55,
	0x10,0x8f,0x14,0xfd,0xbd,0x03,0xfe,0x8a,0xfd,0xc9,0x79,0xf6,0x2a,0x3d,0x20,0x63,
	0x6c,0x61,0x6d,0x70,0xfd,0x69,0xfd,0x02,0xfd,0x09,0xe0,0x02,0xfd,0x59,0xf1,0x02,
	0xfd,0x69,0x04,0x03,0x62,0x2c,0x20,0x30,0x2e,0x30,0x2c,0xfd,0x19,0x20,0xb9,0xfd,
	0x95,0x22,0xbd,0x8f,0xfd,0x85,0x09,0xbe,0x04,0xfd,0xed,0x0c,0x76,0x07,0xfd,0x79,
	0x1a,0x0a,0xfd,0xed,0x25,0x8b,0x07,0xfd,0x45,0x09,0xd3,0x04,0xfd,0xe5,0x0d,0x84,
	0x8f,0xfd,0x9d,0x25,0x53,0x0f,0xfd,0xa5,0x0b,0xfa,0x04,0xfd,0xcd,0x0e,0xee,0x07,
	0xfd,0x5d,0x25,0xcb,0x0f,0xfd,0x4d,0x0c,0x0f,0x05,0xfd,0x65,0x0f,0x1f,0x1f,0xfd,
	0xed,0x23,0x70,0xed,0xfd,0xf5,0x0a,0xec,0x04,0xfd,0x0d,0x10,0x7b,0x1f,0xfd,0xd5,
	0x24,0xe7,0x07,0xfd,0xb5,0x0a,0x01,0x05,0xfd,0x45,0x11,0xd7,0x1f,0xfd,0xcd,0x25,
	0x84,0xed,0xfd,0xd5,0x16,0x47,0x10,0xfd,0x0d,0x06,0x23,0x1b,0xfd,0xb5,0x26,0x5f,
	0x08,0xfd,0xe5,0x16,0xbf,0x10,0xfd,0xee,0x01,0x0a,0x4e,0x01,0xfd,0x05,0x25,0x7d,
	0x28,0xfd,0xa5,0x0a,0xe4,0x04,0xfd,0x1d,0x0e,0xc2,0x07,0xfd,0xad,0x25,0x55,0x30,
	0xfd,0x4d,0x0b,0xf9,0x04,0xfd,0x15,0x0f,0x9e,0xee,0xfd,0x7d,0x27,0x6d,0x40,0xfd,
	0x25,0x17,0x27,0x10,0xfd,0x66,0x04,0x31,0x66,0x01,0xfd,0xfe,0x28,0x4f,0x08,0xfd,
	0xf5,0x18,0xdf,0x40,0xfd,0xf5,0x22,0xd2,0xef,0xfd,0x2d,0x0a,0xd3,0x04,0xfd,0x3d,
	0x10,0xad,0x40,0xfd,0xdd,0x23,0xb5,0x07,0xfd,0xed,0x09,0xe8,0x04,0xfd,0x75,0x11,
	0x7b,0x40,0xfd,0xd5,0x24,0xe6,0xef,0xfd,0x0d,0x16,0xe3,0x0f,0xfd,0x3d,0x06,0x0b,
	0x3b,0xfd,0xbd,0x25,0x2d,0x08,0xfd,0x35,0x12,0x5b,0x10,0xfd,0x95,0x04,0xf2,0x83,
	0xfd,0xa1,0x59,0x03,0xfd,0xed,0x01,0xf2,0x83,0xfd,0x68,0x44,0xfd,0xd1,0xf3,0x83,
	0xfd,0xb1,0x06,0x04,0xfd,0x15,0x01,0xf4,0x83,0xfd,0x48,0x3f,0xfd,0xc9,0xf5,0x83,
	0xfd,0x1d,0x04,0x0d,0x1c,0xfd,0xb5,0x23,0xe5,0x89,0xfd,0x4d,0x12,0xf2,0x05,0xfd,
	0xbd,0x15,0xde,0x09,0xfd,0x75,0x03,0xda,0x0d,0xfd,0x95,0x2c,0xf3,0x09,0xfd,0x15,
	0x0a,0x07,0x06,0xfd,0x95,0x14,0x08,0x0a,0xfd,0xd5,0x05,0x4d,0x20,0xfd,0x6d,0x2b,
	0x2f,0x0a,0xfd,0x75,0x0c,0x2e,0x06,0xfd,0x9d,0x17,0x56,0x0a,0xfd,0xfe,0x2e,0x9b,
	0x14,0xfd,0x1d,0x0d,0x43,0x06,0xfd,0xe5,0x14,0x80,0x0a,0xfd,0x65,0x04,0xe4,0x54,
	0xfd,0x2d,0x2c,0x55,0x0a,0xfd,0x75,0x0b,0x18,0x06,0xfd,0xed,0x16,0x2a,0x0a,0xfd,
	0x4d,0x2f,0x95,0x14,0xfd,0x1d,0x0c,0x2d,0x06,0xfd,0x75,0x16,0x00,0x1f,0xfd,0xfe,
	0x30,0xbb,0x14,0xfd,0x55,0x0d,0x54,0x06,0xfd,0xcd,0x18,0xa2,0x0a,0xfd,0xdd,0x30,
	0xc9,0x29,0xfd,0x1d,0x21,0x6f,0x15,0xfd,0x2d,0x04,0xd9,0x5e,0xfd,0xed,0x2f,0xc4,
	0x52,0xfd,0x25,0x14,0xdd,0xe6,0xfd,0x55,0x0c,0xd1,0x4c,0xfd,0x3d,0x2d,0x1d,0x0a,
	0xfd,0xbd,0x0a,0x1c,0x06,0xfd,0x85,0x1a,0x03,0x53,0xfd,0x15,0x2c,0x59,0x0a,0xfd,
	0x1d,0x0d,0x43,0x06,0xfd,0x2d,0x1b,0x2d,0x53,0xfd,0x1d,0x2f,0x95,0x0a,0xfd,0x05,
	0x13,0x2b,0x15,0xfd,0x75,0x03,0x35,0x7f,0xfd,0x3d,0x01,0x93,0x0d,0xfd,0x79,0xdf,
	0x03,0xfd,0x35,0x22,0xbd,0x83,0xfd,0x15,0x08,0x87,0x04,0xfd,0xfe,0x0c,0x08,0x07,
	0xfd,0xa1,0x06,0x0a,0xfd,0x0d,0x24,0x1d,0x07,0xfd,0x7d,0x07,0x9c,0x04,0xfd,0xd5,
	0x0b,0x32,0x07,0xfd,0x05,0x03,0x0b,0x1c,0xfd,0xe5,0x22,0x59,0x07,0xfd,0xdd,0x09,
	0xc3,0x04,0xfd,0xdd,0x0e,0x80,0x07,0xfd,0xa5,0x23,0xef,0x0e,0xfd,0x85,0x0a,0xd8,
	0x04,0xfd,0xad,0x0d,0x67,0x1d,0xfd,0xa5,0x23,0x84,0xe1,0xfd,0x85,0x09,0xb5,0x04,
	0xfd,0x55,0x0e,0xc3,0x1d,0xfd,0xe5,0x24,0x79,0x07,0xfd,0xed,0x08,0xca,0x04,0xfd,
	0x8d,0x0f,0x1f,0x1e,0xfd,0xbd,0x23,0xb5,0x07,0xfd,0x4d,0x0b,0xf1,0x04,0xfd,0x35,
	0x10,0x7b,0x1e,0xfd,0xc5,0x26,0xf1,0x07,0xfd,0x2d,0x15,0xe3,0x0f,0xfd,0x05,0x02,
	0x6e,0x73,0xfd,0x35,0x23,0x57,0x26,0xfd,0xdd,0x08,0xad,0x04,0xfd,0x2d,0x0e,0x54,
	0x07,0xfd,0xf5,0x23,0xc1,0x2d,0xfd,0x85,0x09,0xc2,0x04,0xfd,0xb5,0x0d,0xda,0x16,
	0xfd,0xa5,0x25,0x0f,0x0f,0xfd,0xbd,0x0a,0xe9,0x04,0xfd,0x0d,0x10,0xcc,0x07,0xfd,
	0x85,0x25,0x49,0x3d,0xfd,0xc5,0x15,0xc3,0x0f,0xfd,0xed,0x01,0x4d,0x29,0xfd,0xad,
	0x22,0xaa,0xde,0xfd,0xbd,0x08,0x9c,0x04,0xfd,0x85,0x0e,0x3d,0x3d,0xfd,0xed,0x23,
	0x47,0x07,0xfd,0x25,0x08,0xb1,0x04,0xfd,0xbd,0x0f,0x0b,0x3d,0xfd,0xc5,0x22,0x83,
	0x07,0xfd,0x85,0x0a,0xd8,0x04,0xfd,0x65,0x10,0xd9,0x3c,0xfd,0xcd,0x25,0xbf,0x07,
	0xfd,0x6d,0x10,0x7f,0x0f,0xfd,0x5d,0x07,0x39,0x7d,0xfd,0xae,0x04,0xf2,0x78,0x01,
	0xfd,0x45,0x02,0x80,0x0b,0xfd,0x7d,0x26,0xf1,0x82,0xfd,0xad,0x0d,0xb7,0x05,0xfd,
	0xad,0x15,0x68,0x09,0xfd,0xad,0x01,0x29,0x0d,0xfd,0x85,0x2c,0x7d,0x09,0xfd,0x4d,
	0x08,0xcc,0x05,0xfd,0x85,0x14,0x92,0x09,0xfd,0x0d,0x04,0xb8,0x1e,0xfd,0x5d,0x2b,
	0xb9,0x09,0xfd,0xad,0x0a,0xf3,0x05,0xfd,0x8d,0x17,0xe0,0x09,0xfd,0x25,0x2d,0xaf,
	0x13,0xfd,0x55,0x0b,0x08,0x06,0xfd,0xd5,0x14,0x0a,0x0a,0xfd,0x9d,0x02,0xab,0x50,
	0xfd,0x1d,0x2c,0xdf,0x09,0xfd,0xad,0x09,0xdd,0x05,0xfd,0xdd,0x16,0xb4,0x09,0xfd,
	0x75,0x2d,0xa9,0x13,0xfd,0x55,0x0a,0xf2,0x05,0xfd,0x65,0x16,0x9e,0x1d,0xfd,0x25,
	0x2f,0xcf,0x13,0xfd,0x8d,0x0b,0x19,0x06,0xfd,0xbd,0x18,0x2c,0x0a,0xfd,0x05,0x2f,
	0xf1,0x27,0xfd,0x45,0x1f,0x83,0x14,0xfd,0x65,0x02,0x80,0x5a,0xfd,0x15,0x2e,0x14,
	0x4f,0xfd,0xed,0x16,0x25,0xdc,0xfd,0xb5,0x07,0x5c,0x49,0xfd,0x2d,0x2d,0xa7,0x09,
	0xfd,0xf5,0x08,0xe1,0x05,0xfd,0xad,0x18,0x53,0x4f,0xfd,0x05,0x2c,0xe3,0x09,0xfd,
	0x55,0x0b,0x08,0x06,0xfd,0x55,0x19,0x7d,0x4f,0xfd,0x0d,0x2f,0x1f,0x0a,0xfd,0x4d,
	0x04,0x1d,0x06,0xfd,0x7a,0x25,0xa8,0x03,0x32,0xfd,0x12,0xe1,0xb8,0x03,0x32,0xfd,
	0x4a,0x4f,0xba,0x03,0xfd,0x66,0x02,0x04,0xa8,0x03,0xfd,0x86,0x02,0xf1,0xb9,0x03,
	0xfd,0x2a,0x77,0xb9,0x03,0xfd,0x1a,0xa3,0xb9,0x03,0x32,0x2e,0xfd,0x01,0xaa,0x06,
	0xfd,0x10,0x14,0xfd,0x0a,0xda,0xa3,0x03,0xfd,0x10,0x14,0x79,0xfd,0x28,0x14,0x7a,
	0xfd,0x52,0x84,0xbc,0x03,0xfd,0x42,0x8f,0xa4,0x03,0xfd,0x6a,0xd9,0xb8,0x03,0xfd,
	0x18,0x63,0xfd,0x2e,0x01,0x2d,0xba,0x03,0xfd,0x9d,0x02,0x78,0x07,0xfd,0xfe,0x01,
	0x00,0x07,0xfd,0xb1,0xc1,0x04,0xfd,0xd9,0xf6,0x79,0xfd,0xd1,0x54,0x04,0xfd,0x19,
	0x1b,0x04,0xfd,0x01,0x59,0x05,0xfd,0x48,0x36,0x2e,0x72,0x20,0x3e,0xfd,0x01,0x65,
	0x01,0x30,0x31,0xfd,0x89,0x74,0x0b,0xfd,0x61,0x9b,0x02,0xfd,0xe2,0xaf,0xe2,0x02,
	0xfd,0x45,0x08,0x57,0x01,0x3c,0x20,0x30,0x2e,0x39,0x39,0x39,0xfd,0x91,0x57,0x01,
	0xfd,0x0d,0x07,0x59,0x01,0xfd,0x91,0x43,0x07,0x44,0xfd,0x01,0xf5,0x07,0xfd,0x6d,
	0x01,0xd5,0x7c,0xfd,0x0d,0x01,0x86,0x01,0xfd,0x45,0x01,0x2d,0x07,0xfd,0x19,0x66,
	0x07,0xfd,0x28,0x8d,0xfd,0x19,0xb6,0x2d,0xfd,0x49,0xc5,0x2d,0xfd,0x48,0x1f,0xfd,
	0x12,0xd7,0x8d,0x03,0xfd,0x11,0xd6,0x2d,0xfd,0x79,0x0d,0x06,0xfd,0x59,0xcf,0x01,
	0xfd,0x40,0xe5,0xfd,0xc5,0x0c,0xbb,0x01,0xfd,0x08,0xae,0xfd,0x9d,0x0d,0xbb,0x01,
	0x67,0xfd,0xbd,0x0d,0xbb,0x01,0xfd,0x08,0x28,0xfd,0xbd,0x0a,0xbb,0x01,0xfd,0x6a,
	0x89,0xf9,0x01,0xfd,0x9d,0x01,0xbb,0x01,0xfd,0x55,0x0b,0xe9,0x06,0xfd,0x95,0x02,
	0xb5,0x01,0xfd,0xe5,0x0a,0xe3,0x06,0xfd,0x95,0x02,0xb5,0x01,0xfd,0xe5,0x0a,0xdd,
	0x06,0xfd,0x95,0x02,0xb5,0x01,0xfd,0xf1,0xd7,0x06,0xfd,0xd5,0x01,0xd4,0x11,0xfd,
	0xf1,0xaf,0x11,0xfd,0xdd,0x04,0x8f,0x11,0xfd,0xed,0x01,0x00,0x01,0xfd,0xe1,0xd3,
	0x12,0xfd,0xa5,0x07,0xd1,0x12,0xfd,0x05,0x03,0x2c,0x14,0xfd,0xc8,0x22,0x32,0xfd,
	0xf0,0x22,0x33,0xfd,0xf0,0x22,0x34,0xfd,0xf0,0x22,0x35,0xfd,0xf0,0x22,0x36,0xfd,
	0xf0,0x22,0x37,0xfd,0x15,0x02,0xfe,0x14,0xfd,0xb8,0x1f,0xfd,0x01,0x77,0x01,0xfd,
	0xc0,0x1f,0x33,0xfd,0xd8,0x1f,0x34,0xfd,0xd8,0x1f,0x35,0xfd,0xd8,0x1f,0x36,0xfd,
	0xd8,0x1f,0x37,0xfd,0xa5,0x05,0xec,0x02,0xfd,0x29,0x5f,0x01,0xfd,0x20,0x14,0xfd,
	0x01,0x69,0x01,0xfd,0x29,0x54,0x01,0xfd,0x20,0x14,0xfd,0x01,0x5e,0x01,0xfd,0x29,
	0x49,0x01,0xfd,0x20,0x14,0xfd,0x01,0x53,0x01,0xfd,0x29,0x3e,0x01,0xfd,0x20,0x14,
	0xfd,0x01,0x48,0x01,0xfd,0x29,0x33,0x01,0xfd,0x20,0x14,0xfd,0x01,0x3d,0x01,0xfd,
	0x29,0x28,0x01,0xfd,0x20,0x14,0xfd,0x01,0x32,0x01,0xfd,0xa5,0x01,0x78,0x07,0xfd,
	0x06,0x01,0x96,0xfa,0x02,0xfd,0x61,0x89,0x01,0xfd,0x6d,0x01,0x25,0x14,0xfd,0xd1,
	0x05,0x04,0xfd,0x3d,0x04,0xed,0x01,0xfd,0x26,0x01,0x8d,0x9f,0x03,0xfd,0x08,0x97,
	0x75,0x43,0x6c,0x65,0x61,0xfd,0x29,0xbe,0x1e,0xfd,0x05,0x01,0x29,0x01,0xfd,0x50,
	0x31,0x7d,0x0a,
} ;

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE

