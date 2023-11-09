#include "Cannon.h"
#include "Model.h"

namespace
{
	constexpr int kShotInterval = 60 * 4;
}

Cannon::Cannon(int fileName, VECTOR pos, Rot num) :
	m_pos(pos),
	m_dir(VGet(0, 0, 0)),
	m_frameCount(0),
	m_isStartShot(false)
{
	// ƒ‚ƒfƒ‹‚Ì‰Šú‰»
	m_pModel = std::make_shared<Model>(fileName);
	m_pModel->SetUseCollision(false, false);
	m_pModel->SetPos(m_pos);
	
	if (num == UP)
	{
		m_pModel->SetRot(VGet(0.0f, 90.0f / 180.0f * DX_PI_F, 0.0f));
		m_dir.z = m_pos.z - 1;

	}
	else if (num == DOWN)
	{
		m_pModel->SetRot(VGet(0.0f, -90.0f / 180.0f * DX_PI_F, 0.0f));
		m_dir.z = m_pos.z + 1;
	}
	else if (num == LEFT)
	{
		m_pModel->SetRot(VGet(0.0f, 0.0f / 180.0f * DX_PI_F, 0.0f));
		m_dir.x = m_pos.x + 1;
	}
	else if (num == RIGHT)
	{
		m_pModel->SetRot(VGet(0.0f, -180.0f / 180.0f * DX_PI_F, 0.0f));
		m_dir.x = m_pos.x + 1;
	}
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	m_isStartShot = false;
	m_frameCount++;

	if (m_frameCount > kShotInterval)
	{
		m_frameCount = 0;
		m_isStartShot = true;
	}
}

void Cannon::Draw()
{
	m_pModel->Draw();
}