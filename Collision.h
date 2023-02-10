#pragma once
#include "CollisionPrimitive.h"

/// <summary>
/// 当たり判定ヘルパークラス
/// </suumary>
class Collision
{
public:
	/// <summary>
	/// 球と平面の当たり判定
	/// </suumary>
	/// <param name="sphere">球</param>
	/// <param name="sphere">平面</param>
	/// <praam naem="inter>交点</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckSphere2Plane(const Sphere& shprere, const Plane& plane, DirectX::XMVECTOR* inter = nullptr);
};
