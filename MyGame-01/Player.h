#pragma once
#include <DxLib.h>
#include <memory>
#include "Util/Vec2.h"
#include "StageData.h"

class Model;
template <class TState> class StateMachine;

// �v���C���[�N���X
class Player
{
public:
	Player();	// �R���X�g���N�^
	~Player();	// �f�X�g���N�^

	void Update();		// �A�b�v�f�[�g
	void EnterNormal();	// �ʏ�Enter	
	void UpdateNormal();// �ʏ�Update
	void ExitNormal();	// �ʏ�Exit	
	void EnterDeath();	// �ʏ�Enter
	void UpdateDeath();	// �ʏ�Update
	void ExitDeath();	// �ʏ�Exit
	void Draw();		// �`��
	void UpdateIdle();	// �ҋ@
	void UpdateAttack();// �U��
	void OnDamage(int damage);	// ��_���[�W
	void DrawUI();

public:
	VECTOR GetPos() { return m_data.pos; }			// ���ݍ��W�̎擾
	VECTOR GetLastPos() { return m_data.lastPos; }	// �O����W�̎擾
	float GetAngle() { return m_data.angle; }		// Y����]�̌����̎擾
	float GetColRadius();							// ���a�̎擾

	void SetIsOnField(bool OnFieldFlag) { m_data.isOnField = OnFieldFlag; }
	void SetModelPos(VECTOR modelPos) { m_modelPos = modelPos; }

	// �X�e�[�g
	enum State
	{
		Normal,
		Damage,
		Death
	};

private:
	std::shared_ptr<Model> m_pModel;	// ���f���̃|�C���^

	// �v���C���[��� 
	struct PlayerParam
	{
		VECTOR pos;		// ���݂̍��W
		VECTOR lastPos;	// �O��̍��W
		float angle;	// ����
		float radius;	// ���a
		bool isOnField;	// �n�ʂɏ���Ă��邩
		float velocity;	// �d�͉����x
		int animNo;		// �A�j���[�V�����ԍ�
		bool isJumping;	// �W�����v���Ă��邩
		float jumpAcc;	// �W�����v�����p�����x
	};

	PlayerParam m_data;	
	StateMachine<State> m_stateMachine;

	VECTOR m_modelPos;

	int m_hp;			// HP
	int m_damageFrame;	// ���G����
	float m_hpRate;		// �ő�HP�ɑ΂��錻�݂�HP�̊���
	float m_barWidth;	// HP�o�[�̒���
};