#pragma once
#include "objBase.h"

class CScaf :public BaseVector
{
public:
	CScaf(Point);

	int Action(vector<unique_ptr<BaseVector>>&);
	void Draw();
};