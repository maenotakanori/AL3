#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"

class Player;

class CameraController {
public:
	void Initialize(ViewProjection* viewProjection);

	void Update();

private:
	ViewProjection* viewProjection_ = nullptr;
	Player* target_ = nullptr;
	void SetTarget(Player* target) { target_ = target; }
	void Reset();
	Vector3 targetOffset_ = {0, 0, -15.0f};
	//const Vector3 operator+(const Vector3 v1, const Vector3 v2);

};