#include "CannonShot.h"
#include "Model.h"

namespace
{
	// �O���t�B�b�N���
	const char* const kCannonBallFileName = "Data/Model/Cannonball.mv1";

	// �p�����[�^
	constexpr int kShotNum = 6;
	constexpr float kSpeed = 10.0f;
}

CannonShot::CannonShot(VECTOR cannonBallPos) :
	m_pos(cannonBallPos)
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
}
