#include <cassert>
#include <DxLib.h>

#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "SceneDebug.h"
#include "../Util/Pad.h"

SceneManager::SceneManager() :
	m_pScene()
{
}
SceneManager::~SceneManager()
{
	// 処理なし
}

void SceneManager::Init()
{
#ifdef NDEBUG
	// 指定したクラスのインスタンスのポインタをセット
	m_pScene.reset(new SceneTitle);
	m_pScene->Init();
#else
	// 指定したクラスのインスタンスのポインタをセット
	m_pScene.reset(new SceneDebug);
	m_pScene->Init();
#endif
}

void SceneManager::End()
{
	// 有効なポイント(nullptrでないか)か確認
	assert(m_pScene);
	// 無効なポインタ(nullptr)の場合、シーンの終了処理を行わない
	if (!m_pScene)	return;

	// シーンの終了処理
	m_pScene->End();
}

void SceneManager::Update()
{
	// 有効なポイント(nullptrでないか)か確認
	assert(m_pScene);
	// 無効なポインタ(nullptr)の場合、シーンの更新処理を行わない
	if (!m_pScene)	return;

	Pad::update();
	// 次のシーンオブジェクトのポインタを取得
	// (/*由衣さんに質問したい*/)
	SceneBase* pScene = m_pScene->Update();
	// 取得したポインタが現在のシーンオブジェクトのポインタと同じじゃなければ
	if (pScene != m_pScene.get())
	{
		// 現在のシーンの終了処理
		m_pScene->End();

		// シーンオブジェクトのポインタをセットし、
		// 次シーンへの切り替えを行う
		// (/*由衣さんに質問したい*/)
		m_pScene.reset(pScene);
		// シーンの初期化
		m_pScene->Init();
	}
}

void SceneManager::Draw()
{
	// 有効なポイント(nullptrでないか)か確認
	assert(m_pScene);
	// 無効なポインタ(nullptr)の場合、シーンの描画処理を行わない
	if (!m_pScene)	return;
	// シーンの描画
	m_pScene->Draw();
}