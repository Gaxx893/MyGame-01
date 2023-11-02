#include "SceneDebug.h"
#include "SceneTitle.h"
#include "SceneMain.h"

#include "../Util/Pad.h"
#include "../Util/Range.h"
#include "../Field.h"

namespace
{
	// �~�̔��a
	constexpr float kColRadius = 13.0f;
	// �ړ���
	constexpr float kRange = 30.0f;

	// �ړ����̐���
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
	// �J�[�\���̈ړ��͈�
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

	// �ړ��ł���͈�
	const Range<float> PlayerPositionRange(kStart, kEnd);
	// X���W�𐧌�����
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
			// �Q�[���I��
			m_pField = std::make_shared<Field>();
			return new SceneMain(m_pField);
			break;
		}
	case 3:
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			// �Q�[���I��
			DxLib_End();
			break;
		}
	}

	return this;
}

void SceneDebug::Draw()
{
	// �~��`��
	DrawCircle(m_pos.x, m_pos.y, kColRadius, 0xffffff, FALSE);
	// �e�V�[���̖��O�\��
	DrawString(200, 100, "SceneTitle", 0xffffff);
	DrawString(200, 130, "SceneMain", 0xffffff);
	DrawString(200, 160, "�I��", 0xffffff);
}