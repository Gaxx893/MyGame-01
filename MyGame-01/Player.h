#pragma once
#include <DxLib.h>
#include <memory>
#include "Util/Vec2.h"

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
	void Gravity();		// 重力
	void Move();		// 上下左右移動
	void Attack();		// 攻撃

public:
	VECTOR GetPos() { return m_data.pos; }			// 現在座標の取得
	VECTOR GetLastPos() { return m_data.lastPos; }	// 前回座標の取得
	VECTOR GetAttackPos() { return m_data.atkPos; }	// 攻撃した座標の取得
	float GetColRadius();							// 半径の取得
	int GetPlayerColor() { return m_data.color; }	// 色情報の取得

	void SetIsOnField(bool OnFieldFlag) { m_data.isOnField = OnFieldFlag; }

	// ステート
	enum State
	{
		Normal,
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
		VECTOR atkPos;	// 攻撃した座標
		int color;		// 色情報

	//	int frameCount;	// 現フレーム数
	//	float frameRate;// 現フレームの割合
	//	VECTOR dir;		// 
	//	VECTOR upDir;	// 
	//	VECTOR nowDir;	// 
	//	VECTOR maxDir;	// 
	//	VECTOR minDir;	// 
	};

	PlayerParam m_data;	
	StateMachine<State> m_stateMachine;
};