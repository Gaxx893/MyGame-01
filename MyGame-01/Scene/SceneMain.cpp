#include <vector>

#include "../Model.h"
#include "../FieldBase.h"
#include "../Camera.h"
#include "../StateMachine.h"
#include "../Player.h"
#include "../Util/Pad.h"

#include "SceneMain.h"
#include "SceneTitle.h"

namespace
{
	// 非同期読み込みのテスト　ロードするリソースの数
	constexpr int kTestLoadNum = 216;
}

SceneMain::SceneMain(std::shared_ptr<FieldBase> Field):
	m_pField(Field)
{
	// プレイヤーのインスタンス生成
	m_pPlayer = std::make_shared<Player>();

	// カメラのインスタンス生成
	m_pCamera = std::make_shared<Camera>();

	// リソースの読み込み
	SetUseASyncLoadFlag(true);	// 非同期読み込みを行いたい
	for (int i = 0; i < kTestLoadNum; i++)
	{
		m_testHandle.push_back(LoadGraph("Data/test.bmp"));
	}
	m_testHandle.push_back(LoadGraph("Data/test2.bmp"));
	SetUseASyncLoadFlag(false);	// デフォルトに戻しておく

	int width = 0;
	int height = 0;
	int result = GetGraphSize(m_testHandle.back(), &width, &height);
}

void SceneMain::End()
{
	for (auto& handle : m_testHandle)
	{
		DeleteGraph(handle);
	}
}

// 更新
SceneBase* SceneMain::Update()
{
	// 非同期読み込み中のデータがある場合は何もしない
	for (auto& handle : m_testHandle)
	{
		if (CheckHandleASyncLoad(handle))
		{
			// handleのリソースを読み込み中
			return this;
		}
	}

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
	// 非同期読み込み中のデータがある場合は何パーセント完了しているか表示
	int total = 0;
	int loading = 0;
	for (auto& handle : m_testHandle)
	{
		total++;
		if (CheckHandleASyncLoad(handle))
		{
			loading++;	// 読み込みが終わっていないデータの数を加算
		}
	}

	if (loading > 0)
	{
		// まだ読み込みが終わっていない
		SceneBase::DrawFade();
		float rate = static_cast<float>(loading) / static_cast<float>(total);	// 読み込んでいないデータの割合
		rate = 1.0f - rate;	// 読み込みが終わったデータの数に変換

		// データの数から何%ロード計算したが、
		// データサイズや内容によってロード時間は変わるし
		// たまたまWindowsが裏で重い処理を始めたからロードが重くなる、等
		// ロード時間は確定できないのであくまで目安

		DrawFormatString(8, 8, 0xffffff, "Loading... %.1f%%", rate * 100);

		return;
	}
	
	m_pPlayer->Draw();
	m_pField->Draw();

	// 読み込んだBMPの表示テスト
//	DrawExtendGraph(0, 0, 200, 200, m_testHandle.back(), true);

	// フェード処理
	SceneBase::DrawFade();
}

// 当たり判定確認
void SceneMain::CheckCollide()
{
	
}
