#pragma once
#include <Dxlib.h>
#include <memory>
#include "RotData.h"

class Model;
class Cannon
{
public:
	Cannon(int fileName, VECTOR pos, Rot num);
	~Cannon();

	void Update();
	void Draw();

	VECTOR GetPos() { return m_pos; }
	VECTOR GetDir() { return m_dir; }
private:
	std::shared_ptr<Model> m_pModel;	// モデルのポインタ

	VECTOR m_pos;
	VECTOR m_dir;
};

