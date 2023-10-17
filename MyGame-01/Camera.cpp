#include "Camera.h"
#include "Util/Pad.h"

#include <DxLib.h>
#include <cstdlib>
#include <ctime>

namespace
{
	// �J�����ƃv���C���[�̋�����
	constexpr float kDistance = 800.0f;

	// �ړ����x
	constexpr float kSpeed = 10.0f;
}

Camera::Camera()
{
	// �J�������̏�����
	m_data.fov = 60.0f * DX_PI_F / 180.0f;
	m_data.targetPos = VGet(525.0f, 0.0f, 525.0f);
	m_data.cameraPos = VGet(525.0f, 1000.0f, -450.0f);
}

void Camera::Init()
{
	//////////// 3D�֘A�̐ݒ� /////////////
	// Z�o�b�t�@���g�p����
	SetUseZBuffer3D(true);
	// Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);
	// �|���S���̗��ʂ�`�悵�Ȃ�
	SetUseBackCulling(true);

	// �J�����̐ݒ�
	// �J�����̕`��͈�
	SetCameraNearFar(-1000.0f, 1000.0f);
	// ����p
	SetupCamera_Perspective(m_data.fov);
	// ��:�J�����̈ʒu�@�E:�J�����̒����ʒu
	SetCameraPositionAndTarget_UpVecY(m_data.cameraPos, m_data.targetPos);
}

void Camera::Update()
{
	// ��:�J�����̈ʒu�@�E:�J�����̒����ʒu
	SetCameraPositionAndTarget_UpVecY(m_data.cameraPos, m_data.targetPos);

#if false
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_cameraPos = VAdd(m_data.cameraPos, VGet(kSpeed, 0, 0));
	}
	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_cameraPos = VAdd(m_data.cameraPos, VGet(-kSpeed, 0, 0));
	}
	else if (Pad::isPress(PAD_INPUT_UP))
	{
		m_cameraPos = VAdd(m_data.cameraPos, VGet(0, 0, kSpeed));
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_cameraPos = VAdd(m_data.cameraPos, VGet(0, 0, -kSpeed));
	}

	DrawFormatString(0, 0, 0xffffff, "x = %f, y = %f, z = %f", m_data.cameraPos.x, m_data.cameraPos.y, m_data.cameraPos.z);

#endif
}