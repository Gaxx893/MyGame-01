#include <DxLib.h>

#include "SceneTitle.h"
#include "SceneMain.h"

#include "../Util/Pad.h"
#include "../Util/Game.h"
#include "../Util/Range.h"
#include "../Field.h"

namespace
{
	// グラフィックデータ
	const char* const kGameNameFileName = "Data/PngData/Title.png";
	const char* const kFrameFileName = "Data/PngData/Frame.png";

	// 移動幅
	constexpr float kMoveRange = 120.0f;
}

SceneTitle::SceneTitle() :
	m_handle(-1),
	m_frameHandle(-1),
	m_pos(0, 0),
	m_sceneNo(1),
	m_pField(nullptr)
{
	// グラフィック情報のロード
	m_handle = LoadGraph(kGameNameFileName);
	m_frameHandle = LoadGraph(kFrameFileName);
}

void SceneTitle::End()
{
	// 削除
	DeleteGraph(m_handle);
}

SceneBase* SceneTitle::Update()
{
	// カーソルの移動範囲
	const Range<int> CURSOR_RANGE(1, 2);

	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		m_sceneNo = CURSOR_RANGE.Clamp(m_sceneNo - 1);
		m_pos.y -= kMoveRange;
	}
	else if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		m_sceneNo = CURSOR_RANGE.Clamp(m_sceneNo + 1);
		m_pos.y += kMoveRange;
	}

	switch (m_sceneNo)
	{
	case 1:
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			m_pField = std::make_shared<Field>();
			return new SceneMain(m_pField);
			break;
		}
	case 2:
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			// ゲーム終了
			DxLib_End();
			break;
		}
	}

	// 移動できる範囲
	const Range<float> PlayerPositionRange(0.0f, 110.0f);
	// X座標を制限する
	m_pos.y = PlayerPositionRange.Clamp(m_pos.y);

	UpdateFade();
	return this;
}

void SceneTitle::Draw()
{
	// 背景の描画
	DrawGraph(0, 0, m_handle, true);
	DrawGraph(m_pos.x, m_pos.y, m_frameHandle, true);
	SceneBase::DrawFade();
}
