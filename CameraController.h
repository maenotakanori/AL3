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
	// 短形
	struct Rect {
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};
	// カメラ移動範囲
	Rect movableArea_ = {0, 100, 0, 100};
	void SetMovableArea(Rect area) { movableArea_ = area; }

private:
	ViewProjection viewProjection_;
	Player* target_ = nullptr;
	Vector3 targetOffset_ = {0, 0, -15.0f};
	// カメラの目標座標
	Vector3 destPos;
	static inline const float kInterpolationRate = 0.1f;
	static inline const float kVelocityBias = 30.0f;
	// 追従対象の各方向へのカメラ移動範囲
	static inline const Rect margin = {-9.0f, 9.0f, -5.0f, 5.0f};

};