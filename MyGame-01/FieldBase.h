#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Model;

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

	void FirstModelLoad(); // ���f�����[�h(�ŏ��̈����)

	void LoadFile(const char* fileName);

	void ModelLoad(int Model1);//���f�����[�h(�S���̃��f��)

protected:
	std::vector<std::shared_ptr<Model>> m_pGrassCube;

	//�u���b�N�̔ԍ�(�ԍ��ɂ���ău���b�N�̐F���ς��)
	std::vector<int> m_blockNum;

	//�X�e�[�W�ԍ�
	int m_stageNum;

	loadData m_data; // ���[�h�f�[�^
};
