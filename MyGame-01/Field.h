#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>

class Model;

// 地面クラス
class Field
{
public:
	Field();	// コンストラクタ
	~Field();	// デストラクタ

	void Update();	// 更新
	void Draw();	// 描画

	std::vector<std::shared_ptr<Model>> GetModel() { return m_pModel; }

private:
	std::vector<std::shared_ptr<Model>> m_pModel;	// モデルクラスのポインタ

	std::vector<std::vector<int>> m_field;	// 2次元配列のステージ
};

