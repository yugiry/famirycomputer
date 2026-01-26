#pragma once
#include "DxLib.h"
#include "Scene_Manager.h"
#include "result.h"
#include "function.h"

CResult::CResult(CManager* p) :CScene(p) {
	push = true;
}

int CResult::Update() {

	if (CheckHitKeyAll() && !push)
	{
		return 1;
	}
	push = CheckHitKeyAll();

	return 0;
}

void CResult::Draw()
{
	SetFontSize(30);
	DrawString(WINDOW_WIDTH / 2 -80, WINDOW_HEIGHT / 2, "GAME CLEAR", GetColor(255, 255, 255));
	SetFontSize(10);
}

CResult::~CResult()
{

}