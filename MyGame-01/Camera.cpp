#include "Camera.h"
#include "Util/Pad.h"

#include <DxLib.h>
#include <cstdlib>
#include <ctime>

namespace
{
	// カメラの初期位置
	constexpr VECTOR kCameraPos{ 0.0f, 720.0f, 520.0f };
	constexpr VECTOR kCameraTarget{ 0.0f, 400.0f, -120.0f };

	// 移動速度
	constexpr float kSpeed = 10.0f;
}

Camera::Camera()
{
	// カメラ情報の初期化
	m_data.fov = 60.0f * DX_PI_F / 180.0f;
}

void Camera::Init()
{
	//////////// 3D関連の設定 /////////////
	// Zバッファを使用する
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);
	// ポリゴンの裏面を描画しない
	SetUseBackCulling(true);

	// カメラの設定
	// カメラの描画範囲
	SetCameraNearFar(50.0f, 6000.0f);
	// 視野角
	SetupCamera_Perspective(m_data.fov);
	// 左:カメラの位置　右:カメラの注視位置
	SetCameraPositionAndTarget_UpVecY(kCameraPos, kCameraTarget);
}

void Camera::Update(VECTOR playerPos, float playerAngle)
{
	
	m_data.cameraAngle = playerAngle;
	m_data.cameraAngle = (m_data.cameraAngle * 0.8f) + (playerAngle * 0.2f);
	MATRIX cameraRotMtx = MGetRotY(m_data.cameraAngle);

	// ジャンプ時は単純にプレイヤーに服従するのではなく
	//プレイヤーの立っていた位置を見るようにする
	VECTOR cameraTrans = playerPos;
	cameraTrans.y = playerPos.y * 0.0f;
	//cameraTrans.y = m_pos.y * 0.2f;
	MATRIX playerTransMtx = MGetTranslate(cameraTrans);

	// プレイヤーの回転に合わせてカメラ位置、注視点を回転させる
	// プレイヤーの回転情報と平行移動情報を合成
	MATRIX cameraMtx = MMult(cameraRotMtx, playerTransMtx);

	VECTOR cameraPos = VTransform(kCameraPos, cameraMtx);
	VECTOR cameraTarget = VTransform(kCameraTarget, cameraMtx);

	// カメラの設定
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// カメラの視野角を設定（ラジアン）
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこを見ているかを設定する
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);

#if false
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_data.cameraPos = VAdd(m_data.cameraPos, VGet(kSpeed, 0, 0));
	}
	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_data.cameraPos = VAdd(m_data.cameraPos, VGet(-kSpeed, 0, 0));
	}
	else if (Pad::isPress(PAD_INPUT_UP))
	{
		m_data.cameraPos = VAdd(m_data.cameraPos, VGet(0, 0, kSpeed));
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_data.cameraPos = VAdd(m_data.cameraPos, VGet(0, 0, -kSpeed));
	}

	DrawFormatString(0, 0, 0xffffff, "x = %f, y = %f, z = %f", m_data.cameraPos.x, m_data.cameraPos.y, m_data.cameraPos.z);

#endif
}