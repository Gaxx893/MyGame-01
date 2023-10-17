#pragma once
#include <memory>
#include <vector>
#include "SceneBase.h"

class Player;
class Field;
class Camera;

// ���C��(�Q�[��)��ʃN���X
class SceneMain : public SceneBase
{
public:
	SceneMain();				// �R���X�g���N�^
	virtual ~SceneMain() {};	// �f�X�g���N�^

	virtual SceneBase* Update() override;	// �X�V
	virtual void Draw() override;			// �`��

	void CheckCollide();	// �����蔻��m�F

private:
	std::shared_ptr<Player> m_pPlayer;	// �v���C���[�̃|�C���^
	std::shared_ptr<Field> m_pField;	// �n�ʂ̃|�C���^
	std::shared_ptr<Camera> m_pCamera;	// �J�����̃|�C���^
};

