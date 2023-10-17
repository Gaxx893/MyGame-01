#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>

class Model;

// 地面クラス
class Field
{
public:
	Field(VECTOR PlayerattackPos);	// コンストラクタ
	~Field();	// デストラクタ

	void Update();	// 更新
	void Draw();	// 描画

	std::vector<std::shared_ptr<Model>> GetModel() { return m_pModel; }

private:
	std::vector<std::shared_ptr<Model>> m_pModel;	// モデルクラスのポインタ

	std::vector<std::vector<int>> m_field;	// 2次元配列のステージ

	VECTOR playerAttackPos;	// プレイヤーが攻撃した座標

	enum FieldState
	{
		NONE,	// なし
		DEFAULT,// 緑色(デフォルトカラー)
		RED,	// 赤色
		BLUE,	// 青色
		YELLOW,	// 黄色
		PURPLE	// 紫色
	};
};

