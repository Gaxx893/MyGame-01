#include <cassert>
#include <iostream>

#include "FieldBase.h"
#include "Model.h"

namespace
{
	//�t�@�C����
	const char* const kGrassBlock = "Data/Model/GreenCube.mv1";

	// �t�B�[���h�̉��E���s���̃T�C�Y
	constexpr int kBlockNumX = 100;
	constexpr int kBlockNumZ = 100;

	// �n�ʂɕ~���l�߂�u���b�N�̐� 
	constexpr int kBlockNum = kBlockNumX * kBlockNumZ;

	//�u���b�N�̈�ӂ̒���
	constexpr float kBlockSideLength = 200.0f;

	//�n�ʂ̈�ӂ̒���
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
	// �����Ȃ�
}

void FieldBase::Init(loadData data)
{
	FirstModelLoad(); // �ŏ��ɕ������邽�߂Ƀ��f����p�ӂ���

	LoadFile(data.fileName);

	//�ŏ��Ƀ��[�h�������f���ƍ��킹�ă��f����100����
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

//3D���f�������[�h
void FieldBase::FirstModelLoad()
{
	float x = 100.0f * static_cast<float>(0 % m_data.blockNumX) - m_data.blockNumX / 2;
	float z = 100.0f * static_cast<float>(m_data.blockNumZ - (0 / m_data.blockNumX)) - m_data.blockNumX / 2;

	m_pGrassCube.push_back(std::make_shared<Model>(kGrassBlock));
	m_pGrassCube.back()->SetPos(VGet(x, 0.0f, z));// �n�ʂ�y = 0.0f�ŕ`�悳���悤�ɂ���
	m_pGrassCube.back()->SetUseCollision(true, true);
}

void FieldBase::LoadFile(const char* fileName)
{
	// csv�t�@�C����ǂݍ���Ő����̔z��ɂ�����
	FILE* fp;

	if (fopen_s(&fp, fileName, "rt") != 0)
	{
		std::cout << "�t�@�C���ǂݍ��ݎ��s";
		return;	// �ُ�I��
	}

	int chr;

	// chr = fgetc(fp)	�t�@�C������1�����ǂݍ����int�ɂ���chr�ɓ����
	//					chr��53('5'�̕����R�[�h)������
	//					���̌�t�@�C���ʒu�w��q��i�߂�
	//					(����fgetc�����Ƃ��͍���ǂݍ��񂾕����̎����ǂݍ��܂��)

	// chr != FOF		53��EOF�̔�r���s����
	//					EOF -> End Of File		�t�@�C���̏I�[

	int wNum = -1;	// ���m��
	// ���̗v�f��������p
	int tempW = 0;

	int tempNum = 0;
	while (true)
	{
		chr = fgetc(fp);	// 1�����ǂݍ���
		// ��؂蕶������������
		if (chr == ',' ||
			chr == '\n' ||
			chr == EOF)
		{
			// dataTbl�Ƀf�[�^������
			m_blockNum.push_back(tempNum);
			tempNum = 0;

			// �t�@�C���̏I�[�ɗ�����I��
			if (chr == EOF)
			{
				break;
			}
			else if (chr == ',')
			{
				tempW++;	// �v�f��������
			}
			else   // chr == '\n'
			{
				tempW++;	// �v�f��������
				if (wNum < 0)
				{
					wNum = tempW;	// �v�f���m��
				}
				/*else
				{
					assert(wNum == tempW);
				}*/
				tempW = 0;
			}
			// �܂��I����ĂȂ��̂ő����ēǂݍ���
			continue;
		}

		// �f�[�^�͐����݂̂̂͂�
		assert(chr >= '0' && chr <= '9');

		// �����Ȃ̂͊m��
		// ������𐔒l�ɕϊ�������

		// 268��ǂݍ���
		// 1�����ڂ�'2'	����𐔒l�ɕϊ����Ă����
		// 2�����ڂ�'6'	tempNum��2 20 + 6  tempNum = 26
		// 3�����ڂ�'8' tempNum��26 260+ 8 tempNum = 268
		tempNum = (tempNum * 10) + chr - '0';

		// �f�[�^�̋�؂肪�����������_�ł����܂ł��f�[�^�̂ЂƂ܂Ƃ܂�

	}
	// �t�@�C�������
	fclose(fp);
}

void FieldBase::ModelLoad(int Model1)
{
	//�n�ʂɕ��ׂ�
	for (int i = 0; i < m_blockNum.size(); i++)
	{
		float x = 200.0f * static_cast<float>(i % m_data.blockNumX) - m_data.blockNumX / 2;
		float z = 200.0f * static_cast<float>(m_data.blockNumZ - (i / m_data.blockNumX)) - m_data.blockNumX / 2;

		if (m_blockNum[i] == 17)
		{
			// ���n��
			m_pGrassCube.push_back(std::make_shared<Model>(Model1));
			m_pGrassCube.back()->SetUseCollision(true, true);
			m_pGrassCube.back()->SetPos(VGet(x, -kBlockSideLength / 2.0f, z));//��ʂ�y=0.0f�ɂȂ�悤�ɔz�u
			continue;
		}
	}
}