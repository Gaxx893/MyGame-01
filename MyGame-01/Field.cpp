#include "Field.h"

namespace
{
	// �O���t�@�C��
	const char* const kFileStage = "Data/Stage/field1.csv";

	//�n�ʂɕ~���l�߂�u���b�N�̐�
	constexpr int kBlockNumX = 100;
	constexpr int kBlockNumZ = 100;
}

Field::Field()
{
	//�X�e�[�W�ԍ�
	m_stageNum = 1;

	m_data.fileName = kFileStage;
	m_data.blockNumX = kBlockNumX;
	m_data.blockNumZ = kBlockNumZ;

	Init(m_data);
}

Field::~Field()
{
	m_pGrassCube.erase(m_pGrassCube.begin(), m_pGrassCube.end());
}
