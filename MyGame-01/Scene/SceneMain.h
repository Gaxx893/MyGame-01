#pragma once
#include <memory>
#include <vector>
#include "SceneBase.h"

class Player;
class FieldBase;
class Camera;
class Cannon;
class CannonShot;

// メイン(ゲーム)画面クラス
class SceneMain : public SceneBase
{
public:
	SceneMain(std::shared_ptr<FieldBase> Field);				// コンストラクタ
	virtual ~SceneMain() {};	// デストラクタ

	virtual void End() override;
	virtual SceneBase* Update() override;	// 更新
	virtual void Draw() override;			// 描画

	void CheckCollide();	// 当たり判定確認

private:
	std::shared_ptr<Player> m_pPlayer;			// プレイヤーのポインタ
	std::shared_ptr<FieldBase> m_pField;		// 地面のポインタ
	std::shared_ptr<Camera> m_pCamera;			// カメラのポインタ
	std::vector<std::shared_ptr<Cannon>> m_pCannon;		// 砲弾のポインタ
	std::vector<CannonShot*> m_pCannonShot;	// 砲弾の生ポインタ

	// test
	std::vector<int> m_testHandle;
	int m_frameCount;
};

