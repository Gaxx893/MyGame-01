#pragma once

#include <DxLib.h>
#include <memory>
#include <vector>

class Model;
class CannonShot
{
public:
	CannonShot(VECTOR pos, VECTOR dir);
	~CannonShot();

	void Init();
	void Update();
	void Draw();

	float GetColRadius();
	VECTOR GetPos();

private:
	std::shared_ptr<Model> m_pModel;

	VECTOR m_pos;
	VECTOR m_dir;
	std::vector<CannonShot> m_shots;
};

