#include "StateMachine.h"
#include "Player.h"
#include "Model.h"
#include "Util/Pad.h"

namespace
{
	// グラフィック情報
	const char* const kPlayerFileName = "Data/Model/Character.mv1";

	// アニメーション番号
	constexpr int kIdleAnimeNo = 3;
	constexpr int kAttackAnimeNo = 10;
	constexpr int kRunAnimeNo = 11;

	// プレイヤーのパラメータ
	constexpr float kSpeed = 20.0f;
	constexpr float kColRadius = 50.0f;
	constexpr float kGravity = -2.0f;

	// セルのサイズ
	constexpr float kCellSize = 210.0f;
}

Player::Player():
	m_angle(VGet(0.0f, 0.0f, 0.0f))
{
	// プレイヤー情報の初期化
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

	// プレイヤーモデルの初期化
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	m_pModel->SetAnimation(m_data.animNo, true, true);
	m_pModel->SetPos(m_data.pos);
	m_pModel->SetRot(m_data.angle);

	// ステートマシンの初期化、Entry
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
	// ステートマシーンの更新
	m_stateMachine.Update();
}

//// ステート:通常 ////
// 通常Enter
void Player::EnterNormal()
{
}

// 通常Update
void Player::UpdateNormal()
{
	// 重力処理
//	Gravity();
	// 移動処理(アニメーションの切り替えも兼ねる)
//	Move();
	// 攻撃処理(アニメーションの切り替えも兼ねる)
	Attack();

	// アニメーションアップデート
	m_pModel->Update();
	// 座標更新
	m_pModel->SetPos(m_data.pos);
	// 向き更新
	m_pModel->SetRot(m_data.angle);
}

// 通常Exit
void Player::ExitNormal()
{
}

//// ステート:死亡 ////
// 死亡Enter
void Player::EnterDeath()
{
}

// 死亡Update
void Player::UpdateDeath()
{
	//TODO:落ちていく
}

// 死亡Exit
void Player::ExitDeath()
{
}

// 描画
void Player::Draw()
{
	// 描画
	m_pModel->Draw();
}

// 上下左右移動
void Player::Move()
{
	m_data.lastPos = m_data.pos;

	bool isMoving = false;
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_data.pos = VAdd(m_data.pos, VGet(kSpeed, 0.0f, 0.0f));
		m_data.angle.y = rightVec;// 右向き
		isMoving = true;
	}
	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_data.pos = VAdd(m_data.pos, VGet(-kSpeed, 0.0f, 0.0f));
		m_data.angle.y = leftVec;// 左向き
		isMoving = true;
	}
	else if (Pad::isPress(PAD_INPUT_UP))
	{
		m_data.pos = VAdd(m_data.pos, VGet(0.0f, 0.0f, kSpeed));
		m_data.angle.y = upVec;// 上向き
		isMoving = true;
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_data.pos = VAdd(m_data.pos, VGet(0.0f, 0.0f, -kSpeed));
		m_data.angle.y = downVec;// 下向き
		isMoving = true;
	}

	if (isMoving)
	{
		bool isIdleAnim = m_data.animNo == kRunAnimeNo;
		if (!isIdleAnim)
		{
			// 歩行アニメに変更
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
			// 待機アニメに変更
			m_data.animNo = kIdleAnimeNo;
			m_pModel->ChangeAnimation(m_data.animNo, true, false, 2);
		}
	}
}

// 攻撃
void Player::Attack()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// 攻撃した座標を保存
		m_data.atkPos = m_data.pos;
		m_angle = m_data.angle;

		bool isAttackAnim = m_data.animNo == kAttackAnimeNo;
		if (!isAttackAnim)
		{
			// 攻撃アニメに変更
			m_data.animNo = kAttackAnimeNo;
			m_pModel->ChangeAnimation(m_data.animNo, false, false, 1);
		}
	}
	else
	{
		m_angle = { 0.0f, -1.0f, 0.0f };
	}
}

// 重力
void Player::Gravity()
{
	// プレイヤーが着地している場合
	if (m_data.isOnField)
	{
		m_data.isOnField = false;	// 地面に触れていない
	}
	else
	{
		// 速度に重力を加算
		m_data.velocity += kGravity;
		// Y座標を更新
		m_data.pos.y += m_data.velocity;
	}
}

// 半径取得
float Player::GetColRadius()
{
	return kColRadius;
}
