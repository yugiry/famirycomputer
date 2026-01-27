#pragma once
#include "DxLib.h"
#include "Scene_Manager.h"
#include "result.h"
#include "title.h"
#include "function.h"

CResult::CResult(CManager* p) :CScene(p) {
	push = true;
}

int CResult::Update() {

	if (CheckHitKeyAll() && !push)
	{
		manager->Scene_Delete();
		manager->scene = new CTitle(manager);
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