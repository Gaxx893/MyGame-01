#include <vector>

#include "../Model.h"
#include "../Field.h"
#include "../Camera.h"
#include "../StateMachine.h"
#include "../Player.h"

#include "SceneMain.h"

SceneMain::SceneMain()
{
	// �v���C���[�̃C���X�^���X����
	m_pPlayer = std::make_shared<Player>();

	// �n�ʂ̃C���X�^���X����
	m_pField = std::make_shared<Field>(m_pPlayer->GetAttackPos());
	m_pCamera = std::make_shared<Camera>();
}

// �X�V
SceneBase* SceneMain::Update()
{
	m_pPlayer->Update();
	m_pField->Update();
	m_pCamera->Update();

	CheckCollide();

	// �t�F�[�h����
	SceneBase::UpdateFade();
	return this;
}

// �`��
void SceneMain::Draw()
{
	m_pPlayer->Draw();
	m_pField->Draw();

	// �t�F�[�h����
	SceneBase::DrawFade();
}

// �����蔻��m�F
void SceneMain::CheckCollide()
{
	// �n�ʂƃv���C���[�̓����蔻��
	for (auto& pModel : m_pField->GetModel())
	{
		// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
		// result�ϐ��ɓ����蔻��̏����i�[���Ă���
		MV1_COLL_RESULT_POLY_DIM result;	// ������f�[�^

		result = MV1CollCheck_Capsule(pModel->GetModelHandle(),		// ���f���̃n���h�����擾
			pModel->GetColFrameIndex(),	// �����蔻��Ɏg�p����A�j���[�V�����̓���̃t���[���C���f�b�N�X���擾
			m_pPlayer->GetPos(),		// �v���C���[�̌��݈ʒu���擾
			m_pPlayer->GetLastPos(),	// �v���C���[�̑O��̈ʒu���擾(�����蔻��̐��x����̈�)
			m_pPlayer->GetColRadius());	// �v���C���[�̓����蔻��p�J�v�Z���̔��a���擾

		//�|���S������ł��������Ă����ꍇ,isHit��true�ɂ���
		const bool isHit = result.HitNum > 0;
		if (isHit)
		{
			m_pPlayer->SetIsOnField(true);
		}
	}
}
