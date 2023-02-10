#include "Collision.h"

using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere& shprere, const Plane& plane, DirectX::XMVECTOR* inter)
{
	//���W�n�̌��_���狅�̒��S���W�ւ̋���
	XMVECTOR distV = XMVector3Dot(shprere.center, plane.normal);
	//���ʂ̌��_���������Z���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
	float dist = distV.m128_f32[0] - plane.distance;
	//�����̐�Βl�����a���傫����Γ������Ă��Ȃ�
	if (fabsf(dist) > shprere.radius) return false;

	//�^����_���v�Z
	if (inter) {
		//���ʏ�̍ŋߐړ_���A�^����_�Ƃ���
		*inter = -dist * plane.normal + shprere.center;
	}

	return true;
}
