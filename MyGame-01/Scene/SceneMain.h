#pragma once
#include <memory>
#include <vector>
#include "SceneBase.h"

class Player;
class Field;
class Camera;

// メイン(ゲーム)画面クラス
class SceneMain : public SceneBase
{
public:
	SceneMain();				// コンストラクタ
	virtual ~SceneMain() {};	// デストラクタ

	virtual SceneBase* Update() override;	// 更新
	virtual void Draw() override;			// 描画

	void CheckCollide();	// 当たり判定確認

private:
	std::shared_ptr<Player> m_pPlayer;	// プレイヤーのポインタ
	std::shared_ptr<Field> m_pField;	// 地面のポインタ
	std::shared_ptr<Camera> m_pCamera;	// カメラのポインタ
};

