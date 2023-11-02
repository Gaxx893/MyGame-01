#include "SceneDebug.h"
#include "SceneTitle.h"
#include "SceneMain.h"

#include "../Util/Pad.h"
#include "../Util/Range.h"
#include "../Field.h"

namespace
{
	// 円の半径
	constexpr float kColRadius = 13.0f;
	// 移動幅
	constexpr float kRange = 30.0f;

	// 移動幅の制限
	constexpr float kStart = 110.0f;
	constexpr float kEnd = 170.0f;
}

SceneDebug::SceneDebug() :
	m_pos(165.0f, 110.0f),
	m_sceneNo(1),
	m_pField(nullptr)
{
}

SceneBase* SceneDebug::Update()
{
	// カーソルの移動範囲
	const Range<int> CURSOR_RANGE(1, 3);

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_sceneNo = CURSOR_RANGE.Clamp(m_sceneNo - 1);
		m_pos.y -= kRange;
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_sceneNo = CURSOR_RANGE.Clamp(m_sceneNo + 1);
		m_pos.y += kRange;
	}

	// 移動できる範囲
	const Range<float> PlayerPositionRange(kStart, kEnd);
	// X座標を制限する
	m_pos.y = PlayerPositionRange.Clamp(m_pos.y);

	switch (m_sceneNo)
	{
	case 1:
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			return new SceneTitle();
			break;
		}
	case 2:
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			// ゲーム終了
			m_pField = std::make_shared<Field>();
			return new SceneMain(m_pField);
			break;
		}
	case 3:
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			// ゲーム終了
			DxLib_End();
			break;
		}
	}

	return this;
}

void SceneDebug::Draw()
{
	// 円を描画
	DrawCircle(m_pos.x, m_pos.y, kColRadius, 0xffffff, FALSE);
	// 各シーンの名前表示
	DrawString(200, 100, "SceneTitle", 0xffffff);
	DrawString(200, 130, "SceneMain", 0xffffff);
	DrawString(200, 160, "終了", 0xffffff);
}