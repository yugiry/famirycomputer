//DX Library Copyright (C) 2001-2024 Takumi Yamada.
//Dxlib_lib_5.0 2025 Kcom�e���v���[�g Shinya Wakisaka.
#pragma once
#define _USE_MATH_DEFINES
#include "DxLib.h"
#include <list>
#include <vector>
#include <memory>
#include <time.h>

using namespace std;

//���W�A���ϊ��}�N��
#define RADIAN(_deg) ((float)M_PI*(_deg)/180.0f)

//��{�E�B���h�E�T�C�Y
constexpr auto WINDOW_WIDTH = 512;	//����
constexpr auto WINDOW_HEIGHT = 448;	//�c��

constexpr auto MAP_WIDTH = 32;
constexpr auto MAP_HEIGHT = 28;

constexpr auto BLOCK_WIDTH = 16;
constexpr auto BLOCK_HEIGHT = 16;

//2D�p
 struct Point {
	float x, y;
};
 struct Vector {
	float x, y;
};

//3D�p
struct Point3 {
	float x, y, z;
};
struct Vector3 {
	float x, y, z;
};
 struct ObjSize {
	float h, w, d;
};

 enum ID
 {
	 PLAYER,
	 GROUND,
	 SCAF,
	 ID_END
 };

 enum BLOCK
 {
	 BGROUND,
	 BSCAF,
	 BLOCK_END
 };

//�J�������N���X(main.h)
//class CCameraInfo {
//private:
//	static Point3 pos;//�J�����̈ʒu
//public:
//	static Point3 GetPos() { return pos; }//�J�����̈ʒu���擾
//	static void SetPos(Point3 p) { pos = p; }//�J�����̈ʒu���ۑ�
//};