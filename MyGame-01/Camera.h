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
	void Update();	// �X�V
	void Draw() {};	// �`��

private:
	struct CameraParam
	{
		float fov;			// ����p
		VECTOR targetPos;	// �����_
		VECTOR cameraPos;	// ���W
	};

	CameraParam m_data;	// �J�������
};