#pragma once
/// <summary>
/// �����蔻��v���~�e�B�u
/// </summary>
 
#include <DirectXMath.h>

/// <summary>
/// ��
/// </suumary>
struct Sphere
{
	float x = 0;
	float y = 0;
	float z = 0;
	//���S���W
	DirectX::XMVECTOR center = { x,y,z,1 };
	//���a
	float radius = 1.0f;
};

/// <summary>
/// ����
/// </suumary>
struct Plane
{
	//�@���x�N�g��
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	//���_����̋���
	float distance = 0.0f;
};