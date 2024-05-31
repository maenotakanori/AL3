#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"

class Player {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};
	static inline const float kAcceleration = 0.1f;
	static inline const float kAttenuation = 0.1f;
	static inline const float kLimitRunSpeed = 0.1f;
	// 左右
	enum class LRDirection {
		kRight,
		kLeft,
	};
	LRDirection lrDriection_ = LRDirection::kRight;

};
