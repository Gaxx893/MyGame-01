#pragma once
#include <DxLib.h>
#include <memory>
#include "Util/Vec2.h"

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
	void Gravity();		// �d��
	void Move();		// �㉺���E�ړ�
	void Attack();		// �U��

public:
	VECTOR GetPos() { return m_data.pos; }			// ���ݍ��W�̎擾
	VECTOR GetLastPos() { return m_data.lastPos; }	// �O����W�̎擾
	VECTOR GetAttackPos() { return m_data.atkPos; }	// �U���������W�̎擾
	float GetColRadius();							// ���a�̎擾
	int GetPlayerColor() { return m_data.color; }	// �F���̎擾

	void SetIsOnField(bool OnFieldFlag) { m_data.isOnField = OnFieldFlag; }

	// �X�e�[�g
	enum State
	{
		Normal,
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
		VECTOR atkPos;	// �U���������W
		int color;		// �F���

	//	int frameCount;	// ���t���[����
	//	float frameRate;// ���t���[���̊���
	//	VECTOR dir;		// 
	//	VECTOR upDir;	// 
	//	VECTOR nowDir;	// 
	//	VECTOR maxDir;	// 
	//	VECTOR minDir;	// 
	};

	PlayerParam m_data;	
	StateMachine<State> m_stateMachine;
};