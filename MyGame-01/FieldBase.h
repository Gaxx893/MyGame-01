#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

#include "Cannon.h"
#include "RotData.h"

class Model;
class Cannon;
class CannonShot;

class FieldBase
{
protected:
	//���[�h����ۂ̃f�[�^�\����
	struct loadData
	{
		const char* fileName;//�t�@�C����
		int blockNumX;//X���̃u���b�N�̐�
		int blockNumZ;//Y���̃u���b�N�̐�
	};

public:
	FieldBase();
	virtual ~FieldBase();

	void Init(loadData data);
	void Update();
	void Draw();

//	void FirstModelLoad(); // ���f�����[�h(�ŏ��̈����)

	void LoadFile(const char* fileName);

	void ModelLoad(int Model1, int Model2);//���f�����[�h(�S���̃��f��)

	std::vector<std::shared_ptr<Model>> GetGrassCube() { return m_pGrassCube; }	// ���u���b�N���f��
//	std::vector<std::shared_ptr<Model>> GetCannon() { return m_pCannon; }		// �C�䃂�f��
	std::vector<std::shared_ptr<Cannon>> GetCannon() { return m_pCannon; }		// �C�䃂�f��

protected:
	std::vector<std::shared_ptr<Model>> m_pGrassCube;
//	std::vector<std::shared_ptr<Model>> m_pCannon;
	std::vector<std::shared_ptr<Cannon>> m_pCannon;
	std::vector<CannonShot*> m_pCannonShot;	// �C�e�̐��|�C���^

	//�u���b�N�̔ԍ�(�ԍ��ɂ���ău���b�N�̐F���ς��)
	std::vector<int> m_blockNum;

	//�X�e�[�W�ԍ�
	int m_stageNum;

	loadData m_data; // ���[�h�f�[�^
};

