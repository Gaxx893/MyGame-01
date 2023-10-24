#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "StageData.h"

class Model;

// 地面クラス
class Field
{
public:
	Field();	// コンストラクタ
	~Field();	// デストラクタ

	void Update();	// 更新
	void Draw();	// 描画
	void SelectFallCube(VECTOR PlayerAttackPos, float PlayerDir);

	std::vector<std::shared_ptr<Model>> GetGreenModel() { return m_pGreenModel; }
	std::vector<std::shared_ptr<Model>> GetRedModel() { return m_pRedModel; }
	std::vector<std::shared_ptr<Model>> GetBlueModel() { return m_pBlueModel; }
	std::vector<std::shared_ptr<Model>> GetYellowModel() { return m_pYellowModel; }
	std::vector<std::shared_ptr<Model>> GetPurpleModel() { return m_pPurpleModel; }

private:
	void SelectCubeLine(const int beginIndex, const int endIndex, const int currentIndex);

	std::vector<std::shared_ptr<Model>> m_pGreenModel;	// 緑ブロックのポインタ
	std::vector<std::shared_ptr<Model>> m_pRedModel;	// 赤ブロックのポインタ
	std::vector<std::shared_ptr<Model>> m_pBlueModel;	// 青ブロックのポインタ
	std::vector<std::shared_ptr<Model>> m_pYellowModel;// 黄ブロックのポインタ
	std::vector<std::shared_ptr<Model>> m_pPurpleModel;// 紫ブロックのポインタ

	std::vector<std::vector<int>> m_field;	// 2次元配列のステージ
	VECTOR m_modelPos;

	VECTOR m_playerAttackPos;	// プレイヤーが攻撃した座標

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

