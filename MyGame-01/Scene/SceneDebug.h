#pragma once
#include "SceneBase.h"

#include "../Util/Vec2.h"
#include <memory>

// �f�o�b�O�p�̃V�[���I���N���X
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
};

