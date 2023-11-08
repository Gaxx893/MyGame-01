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
	constexpr int kHitAnimeNo = 2;
	constexpr int kAttackAnimeNo = 10;
	constexpr int kRunAnimeNo = 11;

	// �v���C���[�̃p�����[�^
	constexpr float kSpeed = 20.0f;
	constexpr float kColRadius = 63.0f;
	constexpr float kGravity = -1.0f;
	constexpr float kJumpPower = 16.0f;	// �W�����v��
	constexpr float kRotSpeed = 0.05f;	// ���񑬓x
	constexpr VECTOR kPlayerVec{ 0.0f,0.0f,-20.0f };	// �ړ���
	constexpr VECTOR kNockBackVec{ 0.0f, 0.0f, -20.0f };	// �m�b�N�o�b�N����x�N�g��

	// �ő�HP
	constexpr int max_hp = 20;
	// HP�o�[
	constexpr int hp_bar_width = 128;
	constexpr int hp_bar_height = 20;
}

Player::Player() :
	m_modelPos(VGet(0.0f, 0.0f, 0.0f)),
	m_hp(max_hp),
	m_damageFrame(0),
	m_hpRate(0.0f),
	m_barWidth(0.0f)
{
	// �v���C���[���̏�����
	m_data.pos = VGet(525.0f, 0.0f, 525.0f);
	m_data.angle = -3.14f;
	m_data.animNo = kIdleAnimeNo;
	m_data.isOnField = false;
	m_data.velocity = 0.0f;
	m_data.jumpAcc = 0.0f;

	// �v���C���[���f���̏�����
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	m_pModel->SetPos(m_data.pos);
	m_pModel->SetRot(VGet(0.0f, m_data.angle, 0.0f));

	// �X�e�[�g�}�V���̏������AEntry
	auto dummy = []() {};
	m_stateMachine.AddState(Normal, [this]() { EnterNormal(); }, [this]() { UpdateNormal(); }, dummy);
	m_stateMachine.AddState(Damage, [this]() { EnterDamage(); }, [this]() { UpdateDamage(); }, dummy);
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
	m_pModel->SetAnimation(m_data.animNo, true, true);
}

// �ʏ�Update
void Player::UpdateNormal()
{
	// �ҋ@��ԍX�V
	UpdateIdle();
	// �U����ԍX�V
	UpdateAttack();

	// �A�j���[�V�����A�b�v�f�[�g
	m_pModel->Update();
	// ���W�X�V
	m_pModel->SetPos(m_data.pos);
	// �����X�V
	m_pModel->SetRot(VGet(0.0f, m_data.angle, 0.0f));
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

void Player::EnterDamage()
{
	m_data.animNo = kHitAnimeNo;
	m_pModel->ChangeAnimation(m_data.animNo, false, true, 2);
}

void Player::UpdateDamage()
{
	// �A�j���[�V�����A�b�v�f�[�g
	m_pModel->Update();

	if (m_pModel->IsAnimEnd())
	{
		m_stateMachine.SetState(Normal);
	}
}

void Player::ExitDamage()
{
}

// �`��
void Player::Draw()
{
	m_damageFrame--;

	// �`��
	m_pModel->Draw();

	DrawSphere3D(VGet(m_data.pos.x, m_data.pos.y + 185.0f, m_data.pos.z), kColRadius, 8, 0xff0000, 0xff0000, false);
}

void Player::UpdateIdle()
{
	m_data.lastPos = m_data.pos;

	// �A�j���[�V�����������߂�
	m_pModel->Update();
	//m_damageFrame--;

	// �W�����v����
	bool isJumping = false;

	// �v���C���[�̐i�s����
	MATRIX playerRotMtx = MGetRotY(m_data.angle);
	VECTOR move = VTransform(kPlayerVec, playerRotMtx);
	if (!isJumping)
	{
		// A�{�^���ŃW�����v
		if (Pad::isPress(PAD_INPUT_2))
		{
			m_data.jumpAcc = kJumpPower;
			m_data.isOnField = false;
			isJumping = true;
		}
	}

	m_data.jumpAcc += kGravity;
	m_data.pos.y += m_data.jumpAcc;
	if (m_data.isOnField)
	{
		m_data.pos.y = m_modelPos.y + 100.0f;
		m_data.jumpAcc = 0.0f;
		isJumping = false;
		m_data.isOnField = false;
	}

	DrawFormatString(0, 30, 0xffffff, "modelPos= %f", m_modelPos.z);
	DrawFormatString(0, 0, 0xffffff, "pos= %f", m_data.pos.x);

	bool isMoving = false;
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_data.angle += kRotSpeed;
		isMoving = true;
	}
	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_data.angle -= kRotSpeed;
		isMoving = true;
	}
	else if (Pad::isPress(PAD_INPUT_UP))
	{
		m_data.pos = VAdd(m_data.pos, move);
		isMoving = true;
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_data.pos = VSub(m_data.pos, move);
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
		if (!isAttackAnim/* && !isIdleAnim*/)
		{
			// �ҋ@�A�j���ɕύX
			m_data.animNo = kIdleAnimeNo;
			m_pModel->ChangeAnimation(m_data.animNo, true, false, 2);
		}
	}
}

// �U��
void Player::UpdateAttack()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		bool isAttackAnim = m_data.animNo == kAttackAnimeNo;
		if (!isAttackAnim)
		{
			// �U���A�j���ɕύX
			m_data.animNo = kAttackAnimeNo;
			m_pModel->ChangeAnimation(m_data.animNo, false, false, 1);
		}
	}
}

void Player::OnDamage(int damage)
{
	if (m_damageFrame > 0)	return;

	const bool isAlive = m_hp > 0;
	// �����Ă����ꍇ
	if (isAlive)
	{
		// �̗͂����炷
		m_hp -= damage;
	}

	m_damageFrame = 60 * 2;

	m_stateMachine.SetState(Damage);
}

void Player::DrawUI()
{
	// HP�o�[�\���ʒu�̃��[���h���W���X�N���[�����W�ɕϊ�����
	Vec2 screenPos = { 200, 30 };

	if (m_hp > -2)
	{
		// �ő�HP�ɑ΂��錻�݂�HP�̊������v�Z����
		m_hpRate = static_cast<float>(m_hp) / static_cast<float>(max_hp);
		// HP�o�[�̒������v�Z����
		m_barWidth = hp_bar_width * m_hpRate;
	}

	// HP�o�[�̓y��(��)
	DrawBoxAA(screenPos.x - hp_bar_width / 2, screenPos.y, screenPos.x + hp_bar_width / 2, screenPos.y + hp_bar_height, 0xff0000, true);
	// ���݂�HP(��)
	DrawBoxAA(screenPos.x - hp_bar_width / 2, screenPos.y, screenPos.x - hp_bar_width / 2 + m_barWidth, screenPos.y + hp_bar_height, 0x00ff00, true);
	// �g��
	DrawBoxAA(screenPos.x - hp_bar_width / 2, screenPos.y, screenPos.x + hp_bar_width / 2, screenPos.y + hp_bar_height, 0xffffff, false);
}

// ���a�擾
float Player::GetColRadius()
{
	return kColRadius;
}
