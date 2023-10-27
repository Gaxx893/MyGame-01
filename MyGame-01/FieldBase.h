#pragma once
#include <vector>
#include <memory>
#include<DxLib.h>

class Model;

class FieldBase
{
protected:
	//ロードする際のデータ構造体
	struct loadData
	{
		const char* fileName;//ファイル名
		int blockNumX;//X軸のブロックの数
		int blockNumZ;//Y軸のブロックの数
	};

public:
	FieldBase();
	virtual ~FieldBase();

	void Init(loadData data);
	void Update();
	void Draw();

	void FirstModelLoad(); // モデルロード(最初の一個だけ)

	void LoadFile(const char* fileName);

	void ModelLoad(int Model1);//モデルロード(全部のモデル)

protected:
	std::vector<std::shared_ptr<Model>> m_pGrassCube;

	//ブロックの番号(番号によってブロックの色が変わる)
	std::vector<int> m_blockNum;

	//ステージ番号
	int m_stageNum;

	loadData m_data; // ロードデータ
};

