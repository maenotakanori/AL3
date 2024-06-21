#include "MathUtilityForText.h"
#include <cmath>
#include <numbers>

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

Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {
	lhv.x += rhv.x;
	lhv.y += rhv.y;
	lhv.z += rhv.z;
	return lhv;
}

float EaseInOut(float x1, float x2, float t) { 
	float easedT = -(std::cosf(std::numbers::pi_v<float> * t) - 1.0f) / 2.0f;
	return Lerp(x1, x2, easedT);
}

float Lerp(float x1, float x2, float t) { return (1.0f - t) * x1 + t * x2; }

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) { 
	return Vector3(Lerp(v1.x, v2.x, t), Lerp(v1.y, v2.y, t), Lerp(v1.z, v2.z, t)); 
}

const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	return temp += v2;
}
