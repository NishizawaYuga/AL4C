#pragma once
#include "CollisionPrimitive.h"

/// <summary>
/// �����蔻��w���p�[�N���X
/// </suumary>
class Collision
{
public:
	/// <summary>
	/// ���ƕ��ʂ̓����蔻��
	/// </suumary>
	/// <param name="sphere">��</param>
	/// <param name="sphere">����</param>
	/// <praam naem="inter>��_</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Plane(const Sphere& shprere, const Plane& plane, DirectX::XMVECTOR* inter = nullptr);
};
