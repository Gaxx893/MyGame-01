#include "Camera.h"
#include "Util/Pad.h"

#include <DxLib.h>
#include <cstdlib>
#include <ctime>

namespace
{
	// �J�����̏����ʒu
	constexpr VECTOR kCameraPos{ 0.0f, 720.0f, 520.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 400.0f, -120.0f };

	// �ړ����x
	constexpr float kSpeed = 10.0f;
}

Camera::Camera()
{
	// �J�������̏�����
	m_data.fov = 60.0f * DX_PI_F / 180.0f;
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
	SetCameraNearFar(50.0f, 6000.0f);
	// ����p
	SetupCamera_Perspective(m_data.fov);
	// ��:�J�����̈ʒu�@�E:�J�����̒����ʒu
	SetCameraPositionAndTarget_UpVecY(kCameraPos, kCameraTarget);
}

void Camera::Update(VECTOR playerPos, float playerAngle)
{
	
	m_data.cameraAngle = playerAngle;
	m_data.cameraAngle = (m_data.cameraAngle * 0.8f) + (playerAngle * 0.2f);
	MATRIX cameraRotMtx = MGetRotY(m_data.cameraAngle);

	// �W�����v���͒P���Ƀv���C���[�ɕ��]����̂ł͂Ȃ�
	//�v���C���[�̗����Ă����ʒu������悤�ɂ���
	VECTOR cameraTrans = playerPos;
	cameraTrans.y = playerPos.y * 0.0f;
	//cameraTrans.y = m_pos.y * 0.2f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	// �v���C���[�̉�]�ɍ��킹�ăJ�����ʒu�A�����_����]������
	// �v���C���[�̉�]���ƕ��s�ړ���������
	MATRIX cameraMtx = MMult(cameraRotMtx, playerTransMtx);

	VECTOR cameraPos = VTransform(kCameraPos, cameraMtx);
	VECTOR cameraTarget = VTransform(kCameraTarget, cameraMtx);

	// �J�����̐ݒ�
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// �J�����̎���p��ݒ�i���W�A���j
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// �J�����̈ʒu�A�ǂ������Ă��邩��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);

#if false
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_data.cameraPos = VAdd(m_data.cameraPos, VGet(kSpeed, 0, 0));
	}
	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_data.cameraPos = VAdd(m_data.cameraPos, VGet(-kSpeed, 0, 0));
	}
	else if (Pad::isPress(PAD_INPUT_UP))
	{
		m_data.cameraPos = VAdd(m_data.cameraPos, VGet(0, 0, kSpeed));
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_data.cameraPos = VAdd(m_data.cameraPos, VGet(0, 0, -kSpeed));
	}

	DrawFormatString(0, 0, 0xffffff, "x = %f, y = %f, z = %f", m_data.cameraPos.x, m_data.cameraPos.y, m_data.cameraPos.z);

#endif
}