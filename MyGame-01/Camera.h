#pragma once
#include <DxLib.h>
#include <memory>

// �J�����N���X
class Camera
{
public:
	Camera();		// �R���X�g���N�^
	~Camera() {};	// �f�X�g���N�^

	void Init();	// ������
	void Update(VECTOR playerPos, float playerAngle);	// �X�V
	void Draw() {};	// �`��

private:
	struct CameraParam
	{
		float fov;			// ����p
		VECTOR targetPos;	// �����_
		VECTOR cameraPos;	// ���W
		float cameraAngle;	// ����
	};

	CameraParam m_data;	// �J�������
};