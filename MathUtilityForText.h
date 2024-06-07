#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"
#include <math.h>

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

Vector3& operator+=(Vector3& lhs, const Vector3& rhv);

float EaseInOut(float x1, float x2, float t);
float Lerp(float x1, float x2, float t);
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);