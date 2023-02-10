#include "GameScene.h"
#include "Model.h"
#include <cassert>
#include <sstream>
#include <iomanip>

#include "Collision.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete objSkydome;
	delete objGround;
	delete objSphere;
	delete objFloor;
	delete modelSkydome;
	delete modelGround;
	delete modelSphere;
	delete modelFloor;
	delete camera;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

    // カメラ生成
	camera = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight, input);

	// カメラ注視点をセット
	camera->SetTarget({0, 1, 0});
	camera->SetDistance(3.0f);

    // 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	objSkydome = Object3d::Create();
	objGround = Object3d::Create();
	objSphere = Object3d::Create();
	objSphere2 = Object3d::Create();
	objFloor = Object3d::Create();

	// テクスチャ2番に読み込み
	Sprite::LoadTexture(2, L"Resources/texture.png");

	modelSkydome = Model::CreateFromOBJ("skydome");
	modelGround = Model::CreateFromOBJ("ground");
	modelSphere = Model::CreateFromOBJ("sphere1");
	modelSphere2 = Model::CreateFromOBJ("sphere2");
	modelFloor = Model::CreateFromOBJ("floor");

	objSkydome->SetModel(modelSkydome);
	objGround->SetModel(modelGround);
	objSphere->SetModel(modelSphere);
	objSphere2->SetModel(modelSphere2);
	objFloor->SetModel(modelFloor);
}

void GameScene::Update()
{
	camera->Update();

	objSkydome->Update();
	objGround->Update();
	objSphere->Update();
	objSphere2->Update();
	objFloor->Update();

	debugText.Print("AD: move camera LeftRight", 50, 50, 1.0f);
	debugText.Print("WS: move camera UpDown", 50, 70, 1.0f);
	debugText.Print("ARROW: move camera FrontBack", 50, 90, 1.0f);

	//球と平面の当たり判定
	bool hit = Collision::CheckSphere2Plane(sphere, plane);
	if (hit) {
		debugText.Print("HIT", 50, 200, 1.0f);
	}

	//球移動
	{
		XMVECTOR moveY = XMVectorSet(0, 0.05f, 0, 0);
		if (input->PushKey(DIK_S)) { 
			sphere.center += moveY; 

		}
		else if (input->PushKey(DIK_W)) { sphere.center -= moveY; }

		XMVECTOR moveX = XMVectorSet(0.05f, 0, 0, 0);
		if (input->PushKey(DIK_A)) { sphere.center += moveX; }
		else if (input->PushKey(DIK_D)) { sphere.center -= moveX; }

		objSphere->SetPosition(XMFLOAT3(sphere.center.m128_f32[0], sphere.center.m128_f32[1], sphere.center.m128_f32[2]));
		objSphere2->SetPosition(XMFLOAT3(sphere.center.m128_f32[0], sphere.center.m128_f32[1], sphere.center.m128_f32[2]));
	}
	//stringstreamで変数の値を埋め込んで整形する
	std::ostringstream spherestr;
	spherestr << "Sphere:("
		<< std::fixed << std::setprecision(2)	//小数点以下2桁まで
		<< sphere.center.m128_f32[0] << ","	//x
		<< sphere.center.m128_f32[1] << ","	//y
		<< sphere.center.m128_f32[2] << ")";//z

	debugText.Print(spherestr.str(), 50, 180, 1.0f);
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	objSkydome->Draw();
	objGround->Draw();
	bool hit = Collision::CheckSphere2Plane(sphere, plane);
	if (hit) {
		objSphere2->Draw();
	}
	else {
		objSphere->Draw();
	}
	//objFloor->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画
	//sprite1->Draw();
	//sprite2->Draw();

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
