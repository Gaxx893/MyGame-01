#pragma once
#include "SceneBase.h"

#include "../Util/Vec2.h"
#include <memory>

class FieldBase;

// デバッグ用のシーン選択クラス
class SceneDebug : public SceneBase
{
public:
	SceneDebug();
	virtual ~SceneDebug() {};

	virtual SceneBase* Update() override;
	virtual void Draw() override;

private:
	Vec2 m_pos;
	int m_sceneNo;

	std::shared_ptr<FieldBase> m_pField;
};

