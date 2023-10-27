#pragma once
#include <memory>
#include <DxLib.h>

#include "../Util/Vec2.h"

#include "SceneBase.h"

class FieldBase;

// �^�C�g����ʃN���X
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
	int m_handle;		// �w�i�ƃ^�C�g��
	int m_frameHandle;	// �I�����̊O�g

	Vec2 m_pos;
	int m_sceneNo;	// �I��ԍ�

	std::shared_ptr<FieldBase> m_pField;
};