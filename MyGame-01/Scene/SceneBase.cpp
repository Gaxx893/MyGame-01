#include "SceneBase.h"
#include <DxLib.h>
#include "../Util/Game.h"

namespace
{
	// �t�F�[�h���x
	constexpr int kFadeSpeed = 8;

	// �k�����x
	constexpr float kShrinkSpeed = 0.5f;
}

SceneBase::SceneBase() :
	m_fadeSpeed(-1)
{
	// �����ݒ�̓t�F�[�h�A�E�g���
	m_fadeColor = GetColor(0, 0, 0);
	m_fadeBrightness = 255;
	m_fadeSpeed = -kFadeSpeed;
}

void SceneBase::UpdateFade()
{

	m_fadeBrightness += m_fadeSpeed;
	if (m_fadeBrightness >= 255)
	{
		m_fadeBrightness = 255;
		if (m_fadeSpeed > 0)
		{
			m_fadeSpeed = 0;
		}
	}
	if (m_fadeBrightness <= 0)
	{
		m_fadeBrightness = 0;
		if (m_fadeSpeed < 0)
		{
			m_fadeSpeed = 0;
		}
	}
}

void SceneBase::DrawFade() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeBrightness);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool SceneBase::IsFadingIn() const
{
	if (m_fadeSpeed < 0)	return true;
	return false;
}

bool SceneBase::IsFadingOut() const
{
	if (m_fadeSpeed > 0)	return true;
	return false;
}