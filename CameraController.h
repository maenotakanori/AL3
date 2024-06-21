#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
#include "ViewProjection.h"

class Player;

class CameraController {
public:
	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }
	void Reset();
	const ViewProjection& GetviewProjection() const { return viewProjection_; }

private:
	ViewProjection viewProjection_;
	Player* target_ = nullptr;
	Vector3 targetOffset_ = {0, 0, -15.0f};
	
};