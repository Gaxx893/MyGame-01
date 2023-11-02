#include "Cannon.h"
#include "Model.h"

Cannon::Cannon(int fileName, VECTOR pos) :
	m_pos(pos)
{
	// ƒ‚ƒfƒ‹‚Ì‰Šú‰»
	m_pModel = std::make_shared<Model>(fileName);
	m_pModel->SetUseCollision(false, false);
	m_pModel->SetPos(m_pos);
	m_pModel->SetRot(VGet(0.0f, DX_PI_F, 0.0f));
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	
}

void Cannon::Draw()
{
	m_pModel->Draw();
}
