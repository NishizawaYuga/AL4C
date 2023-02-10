#pragma once
/// <summary>
/// 当たり判定プリミティブ
/// </summary>
 
#include <DirectXMath.h>

/// <summary>
/// 球
/// </suumary>
struct Sphere
{
	float x = 0;
	float y = 0;
	float z = 0;
	//中心座標
	DirectX::XMVECTOR center = { x,y,z,1 };
	//半径
	float radius = 1.0f;
};

/// <summary>
/// 平面
/// </suumary>
struct Plane
{
	//法線ベクトル
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	//原点からの距離
	float distance = 0.0f;
};