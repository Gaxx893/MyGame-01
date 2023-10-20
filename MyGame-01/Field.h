#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include <array>
#include <queue>

struct ModelParam
{
	int handle = -1;
	bool isFall = false;
	VECTOR pos = { 0.0f, 0.0f, 0.0f };
};

class Model;

// �n�ʃN���X
class Field
{
public:
	Field(VECTOR PlayerattackPos);	// �R���X�g���N�^
	~Field();	// �f�X�g���N�^

	void Update();	// �X�V
	void Draw();	// �`��

private:
	void LoadModelHandle();

	std::array<std::array<int, 8>, 8> m_field;	// 2�����z��̃X�e�[�W

	int stageSize;
	int stageMaxSize;
	std::vector<ModelParam> model;

//	std::vector<std::shared_ptr<Model>> m_pModel;
//	std::array<int, 5> m_modelHandles;	// ���f���̃n���h�����i�[����z��
//	std::vector<std::vector<std::queue<int>>> m_field(8, std::vector<std::queue<int>>(8));
//	std::vector<std::queue<int>> data;

	VECTOR playerAttackPos;	// �v���C���[���U���������W

	enum FieldState
	{
		NONE,	// �Ȃ�
		GREEN,// �ΐF(�f�t�H���g�J���[)
		RED,	// �ԐF
		BLUE,	// �F
		YELLOW,	// ���F
		PURPLE	// ���F
	};
};

