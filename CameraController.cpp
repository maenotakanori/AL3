#include "CameraController.h"
#include "Player.h"

void CameraController::Initialize(ViewProjection* viewProjection) { 
	viewProjection_ = viewProjection; 
}

void CameraController::Update() {

}

void CameraController::Reset() { 
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
	//02_06 p11

}

const Vector3 CameraController::operator+(const Vector3 v1, const Vector3 v2) { 
	Vector3 temp(v1);
	return temp += v2; 
}
