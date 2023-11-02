#pragma once
#include <Dxlib.h>
#include <memory>

class Model;
class Cannon
{
public:
	Cannon(int fileName, VECTOR pos);
	~Cannon();

	void Update();
	void Draw();

	VECTOR GetPos() { return m_pos; }
private:
	std::shared_ptr<Model> m_pModel;	// ���f���̃|�C���^

	VECTOR m_pos;

};

