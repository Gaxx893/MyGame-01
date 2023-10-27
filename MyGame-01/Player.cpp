#include "StateMachine.h"
#include "Player.h"
#include "Model.h"
#include "Util/Pad.h"

namespace
{
	// �O���t�B�b�N���
	const char* const kPlayerFileName = "Data/Model/Character.mv1";

	// �A�j���[�V�����ԍ�
	constexpr int kIdleAnimeNo = 3;
	constexpr int kAttackAnimeNo = 10;
	constexpr int kRunAnimeNo = 11;

	// �v���C���[�̃p�����[�^
	constexpr float kSpeed = 20.0f;
	constexpr float kColRadius = 50.0f;
	constexpr float kGravity = -2.0f;

	// �Z���̃T�C�Y
	constexpr float kCellSize = 210.0f;
}

Player::Player():
	m_angle(VGet(0.0f, 0.0f, 0.0f))
{
	// �v���C���[���̏�����
	m_data.pos = VGet(525.0f, 0.0f, 525.0f);
	m_data.angle = { 0.0f, -1.0f, 0.0f };
	m_data.animNo = kIdleAnimeNo;
	m_data.isOnField = false;
	m_data.velocity = 0.0f;
	m_data.atkPos = VGet(0.0f, 0.0f, 0.0f);
	m_data.color = 0xffffff;
	//m_data.frameCount = 0;
	//m_data.frameRate = 0.0f;
	//m_data.dir = VGet(0, 0, 1);
	//m_data.upDir = VGet(0, 1, 0);
	//m_data.nowDir = VGet(0, 0, 1);
	//m_data.maxDir = VGet(0, 0, 1);
	//m_data.minDir = VGet(0, 0, 1);

	// �v���C���[���f���̏�����
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	m_pModel->SetAnimation(m_data.animNo, true, true);
	m_pModel->SetPos(m_data.pos);
	m_pModel->SetRot(m_data.angle);

	// �X�e�[�g�}�V���̏������AEntry
	auto dummy = []() {};
	auto update = [this]() { UpdateNormal(); };
	m_stateMachine.AddState(Normal, dummy, update, dummy);
	m_stateMachine.AddState(Death, dummy, [this]() {UpdateDeath(); }, dummy);
	m_stateMachine.SetState(Normal);
}

Player::~Player()
{
}

void Player::Update()
{
	// �X�e�[�g�}�V�[���̍X�V
	m_stateMachine.Update();
}

//// �X�e�[�g:�ʏ� ////
// �ʏ�Enter
void Player::EnterNormal()
{
}

// �ʏ�Update
void Player::UpdateNormal()
{
	// �d�͏���
//	Gravity();
	// �ړ�����(�A�j���[�V�����̐؂�ւ������˂�)
//	Move();
	// �U������(�A�j���[�V�����̐؂�ւ������˂�)
	Attack();

	// �A�j���[�V�����A�b�v�f�[�g
	m_pModel->Update();
	// ���W�X�V
	m_pModel->SetPos(m_data.pos);
	// �����X�V
	m_pModel->SetRot(m_data.angle);
}

// �ʏ�Exit
void Player::ExitNormal()
{
}

//// �X�e�[�g:���S ////
// ���SEnter
void Player::EnterDeath()
{
}

// ���SUpdate
void Player::UpdateDeath()
{
	//TODO:�����Ă���
}

// ���SExit
void Player::ExitDeath()
{
}

// �`��
void Player::Draw()
{
	// �`��
	m_pModel->Draw();
}

// �㉺���E�ړ�
void Player::Move()
{
	m_data.lastPos = m_data.pos;

	bool isMoving = false;
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_data.pos = VAdd(m_data.pos, VGet(kSpeed, 0.0f, 0.0f));
		m_data.angle.y = rightVec;// �E����
		isMoving = true;
	}
	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_data.pos = VAdd(m_data.pos, VGet(-kSpeed, 0.0f, 0.0f));
		m_data.angle.y = leftVec;// ������
		isMoving = true;
	}
	else if (Pad::isPress(PAD_INPUT_UP))
	{
		m_data.pos = VAdd(m_data.pos, VGet(0.0f, 0.0f, kSpeed));
		m_data.angle.y = upVec;// �����
		isMoving = true;
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_data.pos = VAdd(m_data.pos, VGet(0.0f, 0.0f, -kSpeed));
		m_data.angle.y = downVec;// ������
		isMoving = true;
	}

	if (isMoving)
	{
		bool isIdleAnim = m_data.animNo == kRunAnimeNo;
		if (!isIdleAnim)
		{
			// ���s�A�j���ɕύX
			m_data.animNo = kRunAnimeNo;
			m_pModel->ChangeAnimation(m_data.animNo, true, false, 2);
		}
	}
	else 
	{
		bool isAttackAnim = m_data.animNo == kAttackAnimeNo;
		bool isIdleAnim = m_data.animNo == kIdleAnimeNo;
		if (!isAttackAnim && !isIdleAnim)
		{
			// �ҋ@�A�j���ɕύX
			m_data.animNo = kIdleAnimeNo;
			m_pModel->ChangeAnimation(m_data.animNo, true, false, 2);
		}
	}
}

// �U��
void Player::Attack()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// �U���������W��ۑ�
		m_data.atkPos = m_data.pos;
		m_angle = m_data.angle;

		bool isAttackAnim = m_data.animNo == kAttackAnimeNo;
		if (!isAttackAnim)
		{
			// �U���A�j���ɕύX
			m_data.animNo = kAttackAnimeNo;
			m_pModel->ChangeAnimation(m_data.animNo, false, false, 1);
		}
	}
	else
	{
		m_angle = { 0.0f, -1.0f, 0.0f };
	}
}

// �d��
void Player::Gravity()
{
	// �v���C���[�����n���Ă���ꍇ
	if (m_data.isOnField)
	{
		m_data.isOnField = false;	// �n�ʂɐG��Ă��Ȃ�
	}
	else
	{
		// ���x�ɏd�͂����Z
		m_data.velocity += kGravity;
		// Y���W���X�V
		m_data.pos.y += m_data.velocity;
	}
}

// ���a�擾
float Player::GetColRadius()
{
	return kColRadius;
}
