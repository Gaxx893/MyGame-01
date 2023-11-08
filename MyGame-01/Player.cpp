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
	constexpr int kHitAnimeNo = 2;
	constexpr int kAttackAnimeNo = 10;
	constexpr int kRunAnimeNo = 11;

	// プレイヤーのパラメータ
	constexpr float kSpeed = 20.0f;
	constexpr float kColRadius = 63.0f;
	constexpr float kGravity = -1.0f;
	constexpr float kJumpPower = 16.0f;	// ジャンプ力
	constexpr float kRotSpeed = 0.05f;	// 旋回速度
	constexpr VECTOR kPlayerVec{ 0.0f,0.0f,-20.0f };	// 移動量
	constexpr VECTOR kNockBackVec{ 0.0f, 0.0f, -20.0f };	// ノックバックするベクトル

	// 最大HP
	constexpr int max_hp = 20;
	// HPバー
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
	// プレイヤー情報の初期化
	m_data.pos = VGet(525.0f, 0.0f, 525.0f);
	m_data.angle = -3.14f;
	m_data.animNo = kIdleAnimeNo;
	m_data.isOnField = false;
	m_data.velocity = 0.0f;
	m_data.jumpAcc = 0.0f;

	// プレイヤーモデルの初期化
	m_pModel = std::make_shared<Model>(kPlayerFileName);
	m_pModel->SetPos(m_data.pos);
	m_pModel->SetRot(VGet(0.0f, m_data.angle, 0.0f));

	// ステートマシンの初期化、Entry
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
	// ステートマシーンの更新
	m_stateMachine.Update();
}

//// ステート:通常 ////
// 通常Enter
void Player::EnterNormal()
{
	m_pModel->SetAnimation(m_data.animNo, true, true);
}

// 通常Update
void Player::UpdateNormal()
{
	// 待機状態更新
	UpdateIdle();
	// 攻撃状態更新
	UpdateAttack();

	// アニメーションアップデート
	m_pModel->Update();
	// 座標更新
	m_pModel->SetPos(m_data.pos);
	// 向き更新
	m_pModel->SetRot(VGet(0.0f, m_data.angle, 0.0f));
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

void Player::EnterDamage()
{
	m_data.animNo = kHitAnimeNo;
	m_pModel->ChangeAnimation(m_data.animNo, false, true, 2);
}

void Player::UpdateDamage()
{
	// アニメーションアップデート
	m_pModel->Update();

	if (m_pModel->IsAnimEnd())
	{
		m_stateMachine.SetState(Normal);
	}
}

void Player::ExitDamage()
{
}

// 描画
void Player::Draw()
{
	m_damageFrame--;

	// 描画
	m_pModel->Draw();

	DrawSphere3D(VGet(m_data.pos.x, m_data.pos.y + 185.0f, m_data.pos.z), kColRadius, 8, 0xff0000, 0xff0000, false);
}

void Player::UpdateIdle()
{
	m_data.lastPos = m_data.pos;

	// アニメーションをすすめる
	m_pModel->Update();
	//m_damageFrame--;

	// ジャンプ処理
	bool isJumping = false;

	// プレイヤーの進行方向
	MATRIX playerRotMtx = MGetRotY(m_data.angle);
	VECTOR move = VTransform(kPlayerVec, playerRotMtx);
	if (!isJumping)
	{
		// Aボタンでジャンプ
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
			// 歩行アニメに変更
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
			// 待機アニメに変更
			m_data.animNo = kIdleAnimeNo;
			m_pModel->ChangeAnimation(m_data.animNo, true, false, 2);
		}
	}
}

// 攻撃
void Player::UpdateAttack()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		bool isAttackAnim = m_data.animNo == kAttackAnimeNo;
		if (!isAttackAnim)
		{
			// 攻撃アニメに変更
			m_data.animNo = kAttackAnimeNo;
			m_pModel->ChangeAnimation(m_data.animNo, false, false, 1);
		}
	}
}

void Player::OnDamage(int damage)
{
	if (m_damageFrame > 0)	return;

	const bool isAlive = m_hp > 0;
	// 生きていた場合
	if (isAlive)
	{
		// 体力を減らす
		m_hp -= damage;
	}

	m_damageFrame = 60 * 2;

	m_stateMachine.SetState(Damage);
}

void Player::DrawUI()
{
	// HPバー表示位置のワールド座標をスクリーン座標に変換する
	Vec2 screenPos = { 200, 30 };

	if (m_hp > -2)
	{
		// 最大HPに対する現在のHPの割合を計算する
		m_hpRate = static_cast<float>(m_hp) / static_cast<float>(max_hp);
		// HPバーの長さを計算する
		m_barWidth = hp_bar_width * m_hpRate;
	}

	// HPバーの土台(赤)
	DrawBoxAA(screenPos.x - hp_bar_width / 2, screenPos.y, screenPos.x + hp_bar_width / 2, screenPos.y + hp_bar_height, 0xff0000, true);
	// 現在のHP(緑)
	DrawBoxAA(screenPos.x - hp_bar_width / 2, screenPos.y, screenPos.x - hp_bar_width / 2 + m_barWidth, screenPos.y + hp_bar_height, 0x00ff00, true);
	// 枠線
	DrawBoxAA(screenPos.x - hp_bar_width / 2, screenPos.y, screenPos.x + hp_bar_width / 2, screenPos.y + hp_bar_height, 0xffffff, false);
}

// 半径取得
float Player::GetColRadius()
{
	return kColRadius;
}
