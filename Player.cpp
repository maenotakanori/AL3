#include "Player.h"
#include "cassert"
#include "numbers"
#include "MathUtilityForText.h"
#include <algorithm>

void Player::Initialize(Model* model,ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	model_ = model;
	//textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() { 
	worldTransform_.UpdateMatrix(); 
	// 移動入力
	// 左右操作移動
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || 
		Input::GetInstance()->PushKey(DIK_LEFT)) {
		// 左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			// 左移動中の右入力
			if (velocity_.x < 0.0f) {
				// 速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x += kAcceleration;
			if (lrDriection_ != LRDirection::kRight) {
				lrDriection_ = LRDirection::kRight;
			}
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 右移動中の左入力
			if (velocity_.x > 0.0f) {
				// 速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x -= kAcceleration;
			if (lrDriection_ != LRDirection::kLeft) {
				lrDriection_ = LRDirection::kLeft;
			}
		}
		// 加速/減速
		velocity_ += acceleration;
		// 最大速度制限
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
	} else {
		// 非入力時は移動減衰をかける
		velocity_.x *= (1.0f - kAcceleration);
	}
	// 移動
	worldTransform_.translation_ += velocity_;
	// 行列計算
	worldTransform_.UpdateMatrix();

	// 旋回制御
	{ 
		float destinationRotationYTable[] = {
		std::numbers::pi_v<float> / 2.0f, 
		std::numbers::pi_v<float> * 3.0f / 2.0f
		};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDriection_)];
		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = destinationRotationY;
	}

}

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_, textureHandle_); }
