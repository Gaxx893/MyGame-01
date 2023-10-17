#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>

class Model;

// �n�ʃN���X
class Field
{
public:
	Field(VECTOR PlayerattackPos);	// �R���X�g���N�^
	~Field();	// �f�X�g���N�^

	void Update();	// �X�V
	void Draw();	// �`��

	std::vector<std::shared_ptr<Model>> GetModel() { return m_pModel; }

private:
	std::vector<std::shared_ptr<Model>> m_pModel;	// ���f���N���X�̃|�C���^

	std::vector<std::vector<int>> m_field;	// 2�����z��̃X�e�[�W

	VECTOR playerAttackPos;	// �v���C���[���U���������W

	enum FieldState
	{
		NONE,	// �Ȃ�
		DEFAULT,// �ΐF(�f�t�H���g�J���[)
		RED,	// �ԐF
		BLUE,	// �F
		YELLOW,	// ���F
		PURPLE	// ���F
	};
};

