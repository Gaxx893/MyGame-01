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

//	void FirstModelLoad(); // モデルロード(最初の一個だけ)

	void LoadFile(const char* fileName);

	void ModelLoad(int Model1, int Model2);//モデルロード(全部のモデル)

	std::vector<std::shared_ptr<Model>> GetGrassCube() { return m_pGrassCube; }	// 草ブロックモデル
//	std::vector<std::shared_ptr<Model>> GetCannon() { return m_pCannon; }		// 砲台モデル
	std::vector<std::shared_ptr<Cannon>> GetCannon() { return m_pCannon; }		// 砲台モデル

protected:
	std::vector<std::shared_ptr<Model>> m_pGrassCube;
//	std::vector<std::shared_ptr<Model>> m_pCannon;
	std::vector<std::shared_ptr<Cannon>> m_pCannon;
	std::vector<CannonShot*> m_pCannonShot;	// 砲弾の生ポインタ

	//ブロックの番号(番号によってブロックの色が変わる)
	std::vector<int> m_blockNum;

	//ステージ番号
	int m_stageNum;

	loadData m_data; // ロードデータ
};

