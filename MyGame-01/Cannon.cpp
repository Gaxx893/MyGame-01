#include "Cannon.h"
#include "Model.h"

Cannon::Cannon(int fileName, VECTOR pos, Rot num) :
	m_pos(pos),
	m_dir(VGet(0, 0, 0))
{
	// ƒ‚ƒfƒ‹‚Ì‰Šú‰»
	m_pModel = std::make_shared<Model>(fileName);
	m_pModel->SetUseCollision(false, false);
	m_pModel->SetPos(m_pos);
	

	if (num == UP)
	{
		m_pModel->SetRot(VGet(0.0f, 90.0f / 180.0f * DX_PI_F, 0.0f));
		m_dir.z++;

	}
	else if (num == DOWN)
	{
		m_pModel->SetRot(VGet(0.0f, -90.0f / 180.0f * DX_PI_F, 0.0f));
		m_dir.z--;
	}
	else if (num == LEFT)
	{
		m_pModel->SetRot(VGet(0.0f, 0.0f / 180.0f * DX_PI_F, 0.0f));
		m_dir.x++;
	}
	else if (num == RIGHT)
	{
		m_pModel->SetRot(VGet(0.0f, -180.0f / 180.0f * DX_PI_F, 0.0f));
		m_dir.x--;
	}
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	m_pos = VAdd(m_pos, m_dir);

	m_pModel->SetPos(m_pos);
}

void Cannon::Draw()
{
	m_pModel->Draw();
}