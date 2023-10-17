#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>

class Model;

// �n�ʃN���X
class Field
{
public:
	Field();	// �R���X�g���N�^
	~Field();	// �f�X�g���N�^

	void Update();	// �X�V
	void Draw();	// �`��

	std::vector<std::shared_ptr<Model>> GetModel() { return m_pModel; }

private:
	std::vector<std::shared_ptr<Model>> m_pModel;	// ���f���N���X�̃|�C���^

	std::vector<std::vector<int>> m_field;	// 2�����z��̃X�e�[�W
};

