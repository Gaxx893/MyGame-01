#pragma once
#include <DxLib.h>
#include <memory>
#include "Util/Vec2.h"
#include "StageData.h"

class Model;
template <class TState> class StateMachine;

// プレイヤークラス
class Player
{
public:
	Player();	// コンストラクタ
	~Player();	// デストラクタ

	void Update();		// アップデート
	void EnterNormal();	// 通常Enter	
	void UpdateNormal();// 通常Update
	void ExitNormal();	// 通常Exit	
	void EnterDeath();	// 通常Enter
	void UpdateDeath();	// 通常Update
	void ExitDeath();	// 通常Exit
	void Draw();		// 描画
	void UpdateIdle();	// 待機
	void UpdateAttack();// 攻撃
	void OnDamage(int damage);	// 被ダメージ
	void DrawUI();

public:
	VECTOR GetPos() { return m_data.pos; }			// 現在座標の取得
	VECTOR GetLastPos() { return m_data.lastPos; }	// 前回座標の取得
	float GetAngle() { return m_data.angle; }		// Y軸回転の向きの取得
	float GetColRadius();							// 半径の取得

	void SetIsOnField(bool OnFieldFlag) { m_data.isOnField = OnFieldFlag; }
	void SetModelPos(VECTOR modelPos) { m_modelPos = modelPos; }

	// ステート
	enum State
	{
		Normal,
		Damage,
		Death
	};

private:
	std::shared_ptr<Model> m_pModel;	// モデルのポインタ

	// プレイヤー情報 
	struct PlayerParam
	{
		VECTOR pos;		// 現在の座標
		VECTOR lastPos;	// 前回の座標
		float angle;	// 向き
		float radius;	// 半径
		bool isOnField;	// 地面に乗っているか
		float velocity;	// 重力加速度
		int animNo;		// アニメーション番号
		bool isJumping;	// ジャンプしているか
		float jumpAcc;	// ジャンプ処理用加速度
	};

	PlayerParam m_data;	
	StateMachine<State> m_stateMachine;

	VECTOR m_modelPos;

	int m_hp;			// HP
	int m_damageFrame;	// 無敵時間
	float m_hpRate;		// 最大HPに対する現在のHPの割合
	float m_barWidth;	// HPバーの長さ
};