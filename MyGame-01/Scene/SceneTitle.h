#pragma once
#include <memory>
#include <DxLib.h>

#include "../Util/Vec2.h"

#include "SceneBase.h"

class FieldBase;

// タイトル画面クラス
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle() {}

	virtual void Init() override {}
	virtual void End() override;

	virtual SceneBase* Update() override;
	virtual void Draw() override;

private:
	int m_handle;		// 背景とタイトル
	int m_frameHandle;	// 選択時の外枠

	Vec2 m_pos;
	int m_sceneNo;	// 選択番号

	std::shared_ptr<FieldBase> m_pField;
};