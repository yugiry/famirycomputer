#pragma once
#include "DxLib.h"
#include "Scene_Manager.h"
#include "title.h"
#include "function.h"

CTitle::CTitle(CManager* p) :CScene(p) {
	push = true;
}

int CTitle::Update() {

	if (CheckHitKeyAll() && !push)
	{
		return 1;
	}
	push = CheckHitKeyAll();

	return 0;
}

void CTitle::Draw()
{
	SetFontSize(30);
	DrawString(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2, "GAME CLEAR", GetColor(255, 255, 255));
	SetFontSize(10);
}

CTitle::~CTitle()
{

}