#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "StageData.h"

class Model;

// �n�ʃN���X
class Field
{
public:
	Field();	// �R���X�g���N�^
	~Field();	// �f�X�g���N�^

	void Update();	// �X�V
	void Draw();	// �`��
	void SelectFallCube(VECTOR PlayerAttackPos, float PlayerDir);

	std::vector<std::shared_ptr<Model>> GetGreenModel() { return m_pGreenModel; }
	std::vector<std::shared_ptr<Model>> GetRedModel() { return m_pRedModel; }
	std::vector<std::shared_ptr<Model>> GetBlueModel() { return m_pBlueModel; }
	std::vector<std::shared_ptr<Model>> GetYellowModel() { return m_pYellowModel; }
	std::vector<std::shared_ptr<Model>> GetPurpleModel() { return m_pPurpleModel; }

private:
	void SelectCubeLine(const int beginIndex, const int endIndex, const int currentIndex);

	std::vector<std::shared_ptr<Model>> m_pGreenModel;	// �΃u���b�N�̃|�C���^
	std::vector<std::shared_ptr<Model>> m_pRedModel;	// �ԃu���b�N�̃|�C���^
	std::vector<std::shared_ptr<Model>> m_pBlueModel;	// �u���b�N�̃|�C���^
	std::vector<std::shared_ptr<Model>> m_pYellowModel;// ���u���b�N�̃|�C���^
	std::vector<std::shared_ptr<Model>> m_pPurpleModel;// ���u���b�N�̃|�C���^

	std::vector<std::vector<int>> m_field;	// 2�����z��̃X�e�[�W
	VECTOR m_modelPos;

	VECTOR m_playerAttackPos;	// �v���C���[���U���������W

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

