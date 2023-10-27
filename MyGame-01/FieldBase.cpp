#include <cassert>
#include <iostream>

#include "FieldBase.h"
#include "Model.h"

namespace
{
	//ファイル名
	const char* const kGrassBlock = "Data/Model/GreenCube.mv1";

	// フィールドの横・奥行きのサイズ
	constexpr int kBlockNumX = 100;
	constexpr int kBlockNumZ = 100;

	// 地面に敷き詰めるブロックの数 
	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//ブロックの一辺の長さ
	constexpr float kBlockSideLength = 200.0f;

	//地面の一辺の長さ
	constexpr float kFieldSideLengthX = kBlockSideLength * kBlockNumX;
	constexpr float kFieldSideLengthZ = kBlockSideLength * kBlockNumZ;

}

FieldBase::FieldBase() :
	m_stageNum(-1)
{
	m_data.blockNumX = 0;
	m_data.blockNumZ = 0;
	m_data.fileName = "";
}

FieldBase::~FieldBase()
{
	// 処理なし
}

void FieldBase::Init(loadData data)
{
	FirstModelLoad(); // 最初に複製するためにモデルを用意する

	LoadFile(data.fileName);

	//最初にロードしたモデルと合わせてモデルを100個生成
	int orgModel1 = MV1LoadModel(kGrassBlock);

	ModelLoad(orgModel1);
}

void FieldBase::Update()
{
	for (auto& model : m_pGrassCube)
	{
		model->Update();
	}
}

void FieldBase::Draw()
{
	for (auto& model : m_pGrassCube)
	{
		model->Draw();
	}
}

//3Dモデルをロード
void FieldBase::FirstModelLoad()
{
	float x = 100.0f * static_cast<float>(0 % m_data.blockNumX) - m_data.blockNumX / 2;
	float z = 100.0f * static_cast<float>(m_data.blockNumZ - (0 / m_data.blockNumX)) - m_data.blockNumX / 2;

	m_pGrassCube.push_back(std::make_shared<Model>(kGrassBlock));
	m_pGrassCube.back()->SetPos(VGet(x, 0.0f, z));// 地面がy = 0.0fで描画されるようにする
	m_pGrassCube.back()->SetUseCollision(true, true);
}

void FieldBase::LoadFile(const char* fileName)
{
	// csvファイルを読み込んで数字の配列にしたい
	FILE* fp;

	if (fopen_s(&fp, fileName, "rt") != 0)
	{
		std::cout << "ファイル読み込み失敗";
		return;	// 異常終了
	}

	int chr;

	// chr = fgetc(fp)	ファイルから1文字読み込んでintにしてchrに入れる
	//					chrに53('5'の文字コード)が入る
	//					その後ファイル位置指定子を進める
	//					(次にfgetcしたときは今回読み込んだ文字の次が読み込まれる)

	// chr != FOF		53とEOFの比較が行われる
	//					EOF -> End Of File		ファイルの終端

	int wNum = -1;	// 未確定
	// 横の要素数数える用
	int tempW = 0;

	int tempNum = 0;
	while (true)
	{
		chr = fgetc(fp);	// 1文字読み込み
		// 区切り文字が見つかった
		if (chr == ',' ||
			chr == '\n' ||
			chr == EOF)
		{
			// dataTblにデータを入れる
			m_blockNum.push_back(tempNum);
			tempNum = 0;

			// ファイルの終端に来たら終了
			if (chr == EOF)
			{
				break;
			}
			else if (chr == ',')
			{
				tempW++;	// 要素数数える
			}
			else   // chr == '\n'
			{
				tempW++;	// 要素数数える
				if (wNum < 0)
				{
					wNum = tempW;	// 要素数確定
				}
				/*else
				{
					assert(wNum == tempW);
				}*/
				tempW = 0;
			}
			// まだ終わってないので続けて読み込み
			continue;
		}

		// データは数字のみのはず
		assert(chr >= '0' && chr <= '9');

		// 数字なのは確定
		// 文字列を数値に変換したい

		// 268を読み込む
		// 1文字目は'2'	これを数値に変換していれる
		// 2文字目は'6'	tempNumは2 20 + 6  tempNum = 26
		// 3文字目は'8' tempNumは26 260+ 8 tempNum = 268
		tempNum = (tempNum * 10) + chr - '0';

		// データの区切りが見つかった時点でそこまでがデータのひとまとまり

	}
	// ファイルを閉じる
	fclose(fp);
}

void FieldBase::ModelLoad(int Model1)
{
	//地面に並べる
	for (int i = 0; i < m_blockNum.size(); i++)
	{
		float x = 200.0f * static_cast<float>(i % m_data.blockNumX) - m_data.blockNumX / 2;
		float z = 200.0f * static_cast<float>(m_data.blockNumZ - (i / m_data.blockNumX)) - m_data.blockNumX / 2;

		if (m_blockNum[i] == 17)
		{
			// 草地面
			m_pGrassCube.push_back(std::make_shared<Model>(Model1));
			m_pGrassCube.back()->SetUseCollision(true, true);
			m_pGrassCube.back()->SetPos(VGet(x, -kBlockSideLength / 2.0f, z));//上面がy=0.0fになるように配置
			continue;
		}
	}
}