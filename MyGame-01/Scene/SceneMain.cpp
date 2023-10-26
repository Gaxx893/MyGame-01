#include <vector>

#include "../Model.h"
#include "../Field.h"
#include "../Camera.h"
#include "../StateMachine.h"
#include "../Player.h"
#include "../Util/Pad.h"

#include "SceneMain.h"
#include "SceneTitle.h"

namespace
{
	// �񓯊��ǂݍ��݂̃e�X�g�@���[�h���郊�\�[�X�̐�
	constexpr int kTestLoadNum = 216;
}

SceneMain::SceneMain()
{
	// �v���C���[�̃C���X�^���X����
	m_pPlayer = std::make_shared<Player>();

	// �n�ʂ̃C���X�^���X����
	m_pField = std::make_shared<Field>();
	m_pCamera = std::make_shared<Camera>();

	// ���\�[�X�̓ǂݍ���
	SetUseASyncLoadFlag(true);	// �񓯊��ǂݍ��݂��s������
	for (int i = 0; i < kTestLoadNum; i++)
	{
		m_testHandle.push_back(LoadGraph("Data/test.bmp"));
	}
	m_testHandle.push_back(LoadGraph("Data/test2.bmp"));
	SetUseASyncLoadFlag(false);	// �f�t�H���g�ɖ߂��Ă���

	int width = 0;
	int height = 0;
	int result = GetGraphSize(m_testHandle.back(), &width, &height);
	/*printfDx("result = %d", result);
	printfDx("width = %d", width);
	printfDx("height = %d", height);*/
}

void SceneMain::End()
{
	for (auto& handle : m_testHandle)
	{
		DeleteGraph(handle);
	}
}

// �X�V
SceneBase* SceneMain::Update()
{
	// �񓯊��ǂݍ��ݒ��̃f�[�^������ꍇ�͉������Ȃ�
	for (auto& handle : m_testHandle)
	{
		if (CheckHandleASyncLoad(handle))
		{
			// handle�̃��\�[�X��ǂݍ��ݒ�
			return this;
		}
	}

	m_pField->SelectFallCube(m_pPlayer->GetAttackPos(), m_pPlayer->GetAngle());

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
	// �񓯊��ǂݍ��ݒ��̃f�[�^������ꍇ�͉��p�[�Z���g�������Ă��邩�\��
	int total = 0;
	int loading = 0;
	for (auto& handle : m_testHandle)
	{
		total++;
		if (CheckHandleASyncLoad(handle))
		{
			loading++;	// �ǂݍ��݂��I����Ă��Ȃ��f�[�^�̐������Z
		}
	}

	if (loading > 0)
	{
		// �܂��ǂݍ��݂��I����Ă��Ȃ�
		SceneBase::DrawFade();
		float rate = static_cast<float>(loading) / static_cast<float>(total);	// �ǂݍ���ł��Ȃ��f�[�^�̊���
		rate = 1.0f - rate;	// �ǂݍ��݂��I������f�[�^�̐��ɕϊ�

		// �f�[�^�̐����牽%���[�h�v�Z�������A
		// �f�[�^�T�C�Y����e�ɂ���ă��[�h���Ԃ͕ς�邵
		// ���܂���Windows�����ŏd���������n�߂����烍�[�h���d���Ȃ�A��
		// ���[�h���Ԃ͊m��ł��Ȃ��̂ł����܂Ŗڈ�

		DrawFormatString(8, 8, 0xffffff, "Loading... %.1f%%", rate * 100);

		return;
	}
	
	m_pPlayer->Draw();
	m_pField->Draw();

	// �ǂݍ���BMP�̕\���e�X�g
//	DrawExtendGraph(0, 0, 200, 200, m_testHandle.back(), true);

	// �t�F�[�h����
	SceneBase::DrawFade();
}

// �����蔻��m�F
void SceneMain::CheckCollide()
{
	// �n�ʂƃv���C���[�̓����蔻��
	for (auto& pModel : m_pField->GetGreenModel())
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
