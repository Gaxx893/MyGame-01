#pragma once

#include <DxLib.h>
#include <memory>
#include <vector>

class Model;
class CannonShot
{
public:
	CannonShot(VECTOR cannonBallPos);
	~CannonShot();

	void Init();
	void Update();
	void Draw();

private:
	std::shared_ptr<Model> m_pModel;

	VECTOR m_pos;
	std::vector<CannonShot> m_shots;
};

