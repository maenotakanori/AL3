#include "CameraController.h"
#include "Player.h"

void CameraController::Initialize() { 
	viewProjection_.Initialize(); 



}

void CameraController::Update() { 
	const Vector3& targetVelocity = target_->GetVelocity();
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
	// 追従対象とオフセットと追従対象の速度からカメラの目標座標を計算
	destPos = targetWorldTransform.translation_ + targetOffset_ + targetVelocity * kVelocityBias;
	// 座標保管によりゆったり追従
	viewProjection_.translation_ = Lerp(viewProjection_.translation_, destPos, kInterpolationRate);

	// 追従対象が画面外に出ないように補正
	viewProjection_.translation_.x = max(viewProjection_.translation_.x, targetWorldTransform.translation_.x + margin.left);
	viewProjection_.translation_.x = min(viewProjection_.translation_.x, targetWorldTransform.translation_.x + margin.right);
	viewProjection_.translation_.y = max(viewProjection_.translation_.y, targetWorldTransform.translation_.y + margin.bottom);
	viewProjection_.translation_.y = min(viewProjection_.translation_.y, targetWorldTransform.translation_.y + margin.top);

	// 移動範囲制限
	viewProjection_.translation_.x = max(viewProjection_.translation_.x, movableArea_.left);
	viewProjection_.translation_.x = min(viewProjection_.translation_.x, movableArea_.right);
	viewProjection_.translation_.y = max(viewProjection_.translation_.y, movableArea_.bottom);
	viewProjection_.translation_.y = min(viewProjection_.translation_.y, movableArea_.top);

	viewProjection_.UpdateMatrix();

}

void CameraController::Reset() { 
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}


