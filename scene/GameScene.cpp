#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete modelBlock_;
	delete debugCamera_;
	delete modelSkydome_;
	delete mapChipField_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("uvChecker.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	player_ = new Player();
	player_->Initialize(model_, textureHandle_, &viewProjection_);

	modelBlock_ = Model::CreateFromOBJ("cube");

	//// 要素数
	//const uint32_t kNumBlockVirtical = 10;
	//const uint32_t kNumBlockHorizontal = 20;
	//// ブロック1個分の横幅
	//const float kBlockWidth = 2.0f;
	//const float kBlockHeight = 2.0f;
	//// 要素数を変更する
	//// 列数を設定（縦方向のブロック数）
	//worldTransformBlocks_.resize(kNumBlockVirtical);
	//for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
	//	// 1列の要素数を設定（横方向のブロック数）
	//	worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	//}

	//// キューブの生成
	//for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
	//	for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
	//		if ((i + j) % 2 == 0)
	//			continue;
	//		worldTransformBlocks_[i][j] = new WorldTransform();
	//		worldTransformBlocks_[i][j]->Initialize();
	//		worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
	//		worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
	//	}
	//}

	debugCamera_ = new DebugCamera(1280, 720);

	modelSkydome_ = Model::CreateFromOBJ("SkyDome", true);

	// 02_03 p32

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");

	GenerateBlocks();

}

void GameScene::Update() {
	// player_->Update();
	//// ブロックの更新
	// for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
	//	for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
	//		if (!worldTransformBlock)
	//			continue;
	//		// 平行移動
	//		Matrix4x4 result{
	//		    1.0f, 0.0f, 0.0f,
	//			0.0f, 0.0f, 1.0f,
	//			0.0f, 0.0f, 0.0f,
	//			0.0f, 1.0f, 0.0f,
	//			worldTransformBlock->translation_.x,
	//			worldTransformBlock->translation_.y,
	//			worldTransformBlock->translation_.z,
	//		    1.0f};
	//		// 平行移動だけ代入
	//		worldTransformBlock->matWorld_ = result;
	//		// 定数バッファに転送する
	//		worldTransformBlock->TransferMatrix();
	//	}
	// }

	// debugCamera_->Update();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif
	// 　カメラの処理
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// 　ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// 　ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

	//// 自キャラの更新
	// player_->Update();
	//// ブロックの更新
	// for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
	//	for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
	//		if (!worldTransformBlock)
	//			continue;
	//		Matrix4x4 matWorld = MakeAffineMatrix(worldTransformBlock->scale_,
	//			worldTransformBlock->rotation_, worldTransformBlock->translation_);
	//		worldTransformBlock->matWorld_ = matWorld;
	//		// 定数バッファに転送する
	//		worldTransformBlock->TransferMatrix();
	//	}
	// }
	//  自キャラの更新
	player_->Update();
	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			// アフィン変換と転送
			worldTransformBlock->UpdateMatrix();
		}
	}



}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// ↓preとpostの間
	player_->Draw();

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, viewProjection_);
		}
	}

	modelSkydome_->Draw(worldTransform_, viewProjection_);


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GenerateBlocks() {
	// ブロックの個数(追加)
	//static inline const uint32_t kNumBlockVirtical = 20;
	//static inline const uint32_t kNumBlockHorizontal = 100;
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	// 要素数を変更する
	// 列数を設定（縦方向のブロック数）
	worldTransformBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; i++) {
		// 1列の要素数を設定（横方向のブロック数）
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}
	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}
