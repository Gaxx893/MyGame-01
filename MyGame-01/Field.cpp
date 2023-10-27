#include "Field.h"

namespace
{
	// 外部ファイル
	const char* const kFileStage = "Data/Stage/field1.csv";

	//地面に敷き詰めるブロックの数
	constexpr int kBlockNumX = 100;
	constexpr int kBlockNumZ = 100;
}

Field::Field()
{
	//ステージ番号
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
