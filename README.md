# DxLibForHTML5

## �T�v

DX���C�u������HTML5�œ������Ă݂���...

- iOS, Android�ł̕`��o�b�N�G���h�� OpenGLES
- iOS �̃T�E���h�Đ��o�b�N�G���h�� OpenAL
- emscripten �ɂ� OpenGLES, OpenAL, libpng, libjpeg, zlib, ogg, vorbis, bullet �Ƃ����� DX���C�u�����Ŏg���Ă���O�����C�u���������ׂĂ�����Ă���

�͂��Aemscripten ���g���ăr���h���Ă݂܂�

## �K�v����

- emscripten 1.39.6^
- cmake
- git (Windows �̂�)
- make (Windows �̂�)

## �r���h

- macOS, Linux

```bash
mkdir Build
cd Build
emcmake cmake ..
emmake make
```

- Windows (���e�X�g)

```bat
mkdir Build
cd Build
emcmake cmake -G "Unix Makefiles" ..
emmake make
```
