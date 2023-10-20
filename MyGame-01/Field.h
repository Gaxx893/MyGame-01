#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include <array>
#include <queue>

struct ModelParam
{
	int handle = -1;
	bool isFall = false;
	VECTOR pos = { 0.0f, 0.0f, 0.0f };
};

class Model;

// 地面クラス
class Field
{
public:
	Field(VECTOR PlayerattackPos);	// コンストラクタ
	~Field();	// デストラクタ

	void Update();	// 更新
	void Draw();	// 描画

private:
	void LoadModelHandle();

	std::array<std::array<int, 8>, 8> m_field;	// 2次元配列のステージ

	int stageSize;
	int stageMaxSize;
	std::vector<ModelParam> model;

//	std::vector<std::shared_ptr<Model>> m_pModel;
//	std::array<int, 5> m_modelHandles;	// モデルのハンドルを格納する配列
//	std::vector<std::vector<std::queue<int>>> m_field(8, std::vector<std::queue<int>>(8));
//	std::vector<std::queue<int>> data;

	VECTOR playerAttackPos;	// プレイヤーが攻撃した座標

	enum FieldState
	{
		NONE,	// なし
		GREEN,// 緑色(デフォルトカラー)
		RED,	// 赤色
		BLUE,	// 青色
		YELLOW,	// 黄色
		PURPLE	// 紫色
	};
};

