#pragma once
#include <DxLib.h>
#include <memory>

// カメラクラス
class Camera
{
public:
	Camera();		// コンストラクタ
	~Camera() {};	// デストラクタ

	void Init();	// 初期化
	void Update(VECTOR playerPos, float playerAngle);	// 更新
	void Draw() {};	// 描画

private:
	struct CameraParam
	{
		float fov;			// 視野角
		VECTOR targetPos;	// 注視点
		VECTOR cameraPos;	// 座標
		float cameraAngle;	// 向き
	};

	CameraParam m_data;	// カメラ情報
};