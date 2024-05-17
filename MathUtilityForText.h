#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"
#include <math.h>

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);