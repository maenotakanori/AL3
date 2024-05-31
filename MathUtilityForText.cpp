#include "MathUtilityForText.h"
#include <cmath>

//Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {
//	// 使用しないとエラーになるのでダミーをコピー
//	Vector3 dm;
//	dm = scale;
//	dm = rot;
//
//	// 平行移動
//	Matrix4x4 result{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, translate.x, translate.y, translate.z, 1.0f};
//
//	return result;
//}

struct Vector3 {
	float x, y, z;
};

struct Matrix4x4 {
	float m[4][4];
};

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result = {};
	float cos = std::cos(radian);
	float sin = std::sin(radian);
	result = {
	    {{1, 0, 0, 0},
	     {0, cos, sin, 0},
	     {
	         0,
	         -sin,
	         cos,
	         0,
	     }, {0, 0, 0, 1}}
    };
	return result;
};

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result = {};
	float cos = std::cos(radian);
	float sin = std::sin(radian);
	result = {
	    {{cos, 0, -sin, 0},
	     {0, 1, 0, 0},
	     {
	         sin,
	         0,
	         cos,
	         0,
	     }, {0, 0, 0, 1}}
    };
	return result;
};

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result = {};
	float cos = std::cos(radian);
	float sin = std::sin(radian);
	result = {
	    {{cos, sin, 0, 0}, {-sin, cos, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}
    };
	return result;
};

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
};

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = {};

	Matrix4x4 rotateX = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateY = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZ = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZ = Multiply(Multiply(rotateX, rotateY), rotateZ);
	Matrix4x4 Sclae = {
	    {{scale.x, 0, 0, 0}, {0, scale.y, 0, 0}, {0, 0, scale.z, 0}, {0, 0, 0, 1}}
    };
	Matrix4x4 Translate{
	    {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {translate.x, translate.y, translate.z, 1}}
    };

	result = Multiply(Multiply(Sclae, rotateXYZ), Translate);

	return result;
};

//02_05 p21

Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {
	lhv.x += rhv.x;
	lhv.y += rhv.y;
	lhv.z += rhv.z;
	return lhv;
}