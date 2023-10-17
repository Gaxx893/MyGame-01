#include "Camera.h"
#include "Util/Pad.h"

#include <DxLib.h>
#include <cstdlib>
#include <ctime>

namespace
{
	// カメラとプレイヤーの距離間
	constexpr float kDistance = 800.0f;

	// 移動速度
	constexpr float kSpeed = 10.0f;
}

Camera::Camera()
{
	// カメラ情報の初期化
	m_data.fov = 60.0f * DX_PI_F / 180.0f;
	m_data.targetPos = VGet(525.0f, 0.0f, 525.0f);
	m_data.cameraPos = VGet(525.0f, 1000.0f, -450.0f);
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
	SetCameraNearFar(-1000.0f, 1000.0f);
	// 視野角
	SetupCamera_Perspective(m_data.fov);
	// 左:カメラの位置　右:カメラの注視位置
	SetCameraPositionAndTarget_UpVecY(m_data.cameraPos, m_data.targetPos);
}

void Camera::Update()
{
	// 左:カメラの位置　右:カメラの注視位置
	SetCameraPositionAndTarget_UpVecY(m_data.cameraPos, m_data.targetPos);

#if false
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_cameraPos = VAdd(m_data.cameraPos, VGet(kSpeed, 0, 0));
	}
	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_cameraPos = VAdd(m_data.cameraPos, VGet(-kSpeed, 0, 0));
	}
	else if (Pad::isPress(PAD_INPUT_UP))
	{
		m_cameraPos = VAdd(m_data.cameraPos, VGet(0, 0, kSpeed));
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_cameraPos = VAdd(m_data.cameraPos, VGet(0, 0, -kSpeed));
	}

	DrawFormatString(0, 0, 0xffffff, "x = %f, y = %f, z = %f", m_data.cameraPos.x, m_data.cameraPos.y, m_data.cameraPos.z);

#endif
}