#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"

class MapChipField;
class Player {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const Vector3& GetVelocity() const { return velocity_; }

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	void PlayerMove();

	//void MapCollision(CollisionMapInfo& info);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};
	// 加速
	static inline const float kAcceleration = 0.01f;
	// 減速
	static inline const float kAttenuation = 0.005f;
	// 最大値
	static inline const float kLimitRunSpeed = 0.5f;
	// 左右
	enum class LRDirection {
		kRight,
		kLeft,
	};
	LRDirection lrDriection_ = LRDirection::kRight;
	// 旋回開始の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 旋回時間＜秒＞
	static inline const float kTimeTurn = 0.3f;
	// 接地フラグ
	bool onGround_ = true;
	// 重力加速度（下方向）
	static inline const float kGravityAcceleration = 0.05f;
	// 最大落下速度（下方向）
	static inline const float kLimitFallSpeed = 0.5f;
	// ジャンプ初速（上方向）
	static inline const float kJumpAcceleration = 0.5f;
	static inline const float kAttenuationLanding = 0.1f;
	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	// マップとの当たり判定情報
	struct CollisionMapInfo {
		bool onCeiling_ = false;
		bool onLanding_ = false;
		bool onWall = false;
		Vector3 amountMove;
	};
	const WorldTransform& GetWorldTransform() const { return worldTransform_; }


};
