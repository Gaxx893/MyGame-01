#include <DxLib.h>

#include "SceneTitle.h"
#include "SceneMain.h"

#include "../Util/Pad.h"
#include "../Util/Game.h"
#include "../Util/Range.h"
#include "../Field.h"

namespace
{
	// �O���t�B�b�N�f�[�^
	const char* const kGameNameFileName = "Data/PngData/Title.png";
	const char* const kFrameFileName = "Data/PngData/Frame.png";

	// �ړ���
	constexpr float kMoveRange = 120.0f;
}

SceneTitle::SceneTitle() :
	m_handle(-1),
	m_frameHandle(-1),
	m_pos(0, 0),
	m_sceneNo(1),
	m_pField(nullptr)
{
	// �O���t�B�b�N���̃��[�h
	m_handle = LoadGraph(kGameNameFileName);
	m_frameHandle = LoadGraph(kFrameFileName);
}

void SceneTitle::End()
{
	// �폜
	DeleteGraph(m_handle);
}

SceneBase* SceneTitle::Update()
{
	// �J�[�\���̈ړ��͈�
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
			// �Q�[���I��
			DxLib_End();
			break;
		}
	}

	// �ړ��ł���͈�
	const Range<float> PlayerPositionRange(0.0f, 110.0f);
	// X���W�𐧌�����
	m_pos.y = PlayerPositionRange.Clamp(m_pos.y);

	UpdateFade();
	return this;
}

void SceneTitle::Draw()
{
	// �w�i�̕`��
	DrawGraph(0, 0, m_handle, true);
	DrawGraph(m_pos.x, m_pos.y, m_frameHandle, true);
	SceneBase::DrawFade();
}
