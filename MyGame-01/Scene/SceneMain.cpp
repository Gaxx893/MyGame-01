#include <vector>

#include "../Model.h"
#include "../Field.h"
#include "../Camera.h"
#include "../StateMachine.h"
#include "../Player.h"

#include "SceneMain.h"

SceneMain::SceneMain()
{
	// プレイヤーのインスタンス生成
	m_pPlayer = std::make_shared<Player>();

	// 地面のインスタンス生成
	m_pField = std::make_shared<Field>(m_pPlayer->GetAttackPos());
	m_pCamera = std::make_shared<Camera>();
}

// 更新
SceneBase* SceneMain::Update()
{
	m_pPlayer->Update();
	m_pField->Update();
	m_pCamera->Update();

	CheckCollide();

	// フェード処理
	SceneBase::UpdateFade();
	return this;
}

// 描画
void SceneMain::Draw()
{
	m_pPlayer->Draw();
	m_pField->Draw();

	// フェード処理
	SceneBase::DrawFade();
}

// 当たり判定確認
void SceneMain::CheckCollide()
{
	// 地面とプレイヤーの当たり判定
	for (auto& pModel : m_pField->GetModel())
	{
		// DxLibの関数を利用して当たり判定をとる
		// result変数に当たり判定の情報を格納している
		MV1_COLL_RESULT_POLY_DIM result;	// 当たりデータ

		result = MV1CollCheck_Capsule(pModel->GetModelHandle(),		// モデルのハンドルを取得
			pModel->GetColFrameIndex(),	// 当たり判定に使用するアニメーションの特定のフレームインデックスを取得
			m_pPlayer->GetPos(),		// プレイヤーの現在位置を取得
			m_pPlayer->GetLastPos(),	// プレイヤーの前回の位置を取得(当たり判定の精度向上の為)
			m_pPlayer->GetColRadius());	// プレイヤーの当たり判定用カプセルの半径を取得

		//ポリゴンが一つでもあたっていた場合,isHitをtrueにする
		const bool isHit = result.HitNum > 0;
		if (isHit)
		{
			m_pPlayer->SetIsOnField(true);
		}
	}
}
