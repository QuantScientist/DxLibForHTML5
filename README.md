# DxLibForHTML5

## �T�v

DX���C�u������HTML5�œ������Ă݂���...

- iOS, Android�ł̕`��o�b�N�G���h�� OpenGLES
- iOS �̃T�E���h�Đ��o�b�N�G���h�� OpenAL
- emscripten �ɂ� OpenGLES, OpenAL, libpng, libjpeg, zlib, ogg, vorbis, bullet �Ƃ����� DX���C�u�����Ŏg���Ă���O�����C�u���������ׂĂ�����Ă���

�͂��Aemscripten ���g���ăr���h���Ă݂܂�

## �R���p�C���ς݃o�C�i���̃_�E�����[�h

- [�ŐV�ł̃_�E�����[�h](https://github.com/nokotan/DxLibForHTML5/releases/latest) (Windows, Linux, macOS����)

## �K�v����

- emscripten 1.39.6^
- cmake
- git
- make (nmake, ninja�ł���)

## �r���h

- macOS, Linux

```bash
git clone --recursive https://github.com/nokotan/DxLibForHTML5.git
cd DxLibForHTML5
mkdir Build
cd Build
emcmake cmake ..
emmake make
```

- Windows

nmake ���g���ꍇ

```bat
git clone --recursive https://github.com/nokotan/DxLibForHTML5.git
cd DxLibForHTML5
mkdir Build
cd Build
emcmake cmake -G "MinGW Makefiles" ..
nmake
```

ninja ���g���ꍇ

```bat
git clone --recursive https://github.com/nokotan/DxLibForHTML5.git
cd DxLibForHTML5
mkdir Build
cd Build
emcmake cmake -G "ninja" ..
ninja
```
