#include "CannonShot.h"
#include "Model.h"
#include <DxLib.h>

namespace
{
	// グラフィック情報
	const char* const kCannonBallFileName = "Data/Model/Cannonball.mv1";

	// パラメータ
	constexpr int kShotNum = 6;
	constexpr float kSpeed = 10.0f;
	constexpr float kColRadius = 56.0f;
}

CannonShot::CannonShot(VECTOR pos, VECTOR dir) :
	m_pos(VGet(pos.x, pos.y + 100.0f, pos.z)),
	m_vec(VGet(0,0,0))
{
	m_pModel = std::make_shared<Model>(kCannonBallFileName);
	m_pModel->SetPos(m_pos);

	VECTOR vec = VSub(dir,m_pos);
	float angle = atan2f(vec.x, vec.z);
	m_vec.x = cosf(angle) * 10;
	m_vec.z = sinf(angle) * 10;

	m_dir = atan2f(m_vec.x, m_vec.z);
}

CannonShot::~CannonShot()
{
}

void CannonShot::Init()
{
}

void CannonShot::Update()
{
	m_vec.x = cosf(m_dir) * 10;
	m_vec.z = sinf(m_dir) * 10;

	m_pos = VAdd(m_pos, m_vec);
//	m_dir = atan2f(m_vec.x, m_vec.z);

	m_pModel->SetPos(m_pos);
}

void CannonShot::Draw()
{
	m_pModel->Draw();

	DrawSphere3D(m_pos, kColRadius, 8, 0xff0000, 0xff0000, false);
}

float CannonShot::GetColRadius()
{
	return kColRadius;
}

VECTOR CannonShot::GetPos()
{
	return m_pos;
}
