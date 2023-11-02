#include "CannonShot.h"
#include "Model.h"

namespace
{
	// グラフィック情報
	const char* const kCannonBallFileName = "Data/Model/Cannonball.mv1";

	// パラメータ
	constexpr int kShotNum = 6;
	constexpr float kSpeed = 10.0f;
	constexpr float kColRadius = 56.0f;
}

CannonShot::CannonShot(VECTOR cannonBallPos) :
	m_pos(VGet(cannonBallPos.x, cannonBallPos.y + 100.0f, cannonBallPos.z))
{
	m_pModel = std::make_shared<Model>(kCannonBallFileName);
	m_pModel->SetPos(m_pos);
}

CannonShot::~CannonShot()
{
}

void CannonShot::Init()
{
}

void CannonShot::Update()
{
	m_pos.x -= kSpeed;

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
