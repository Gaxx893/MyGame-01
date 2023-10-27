#pragma once
#include <memory>
#include <vector>
#include "SceneBase.h"

class Player;
class FieldBase;
class Camera;

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
	std::shared_ptr<Player> m_pPlayer;		// プレイヤーのポインタ
	std::shared_ptr<FieldBase> m_pField;	// 地面のポインタ
	std::shared_ptr<Camera> m_pCamera;		// カメラのポインタ

	// test
	std::vector<int> m_testHandle;
};

