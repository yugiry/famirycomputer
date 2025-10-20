#pragma once
#include "pipe.h"

CPipe::CPipe(Point p, bool _turn)
{
	pos = p;
	img = LoadGraph("image\\pipe.png");

	turn = _turn;
}

int CPipe::Action(vector<unique_ptr<BaseVector>>& base)
{
	return 0;
}

void CPipe::Draw()
{

}