#pragma once
#include "DxLib.h"
#include "Scene_Manager.h"
#include "result.h"
#include "function.h"

CResult::CResult(CManager* p) :CScene(p) {

}

int CResult::Update() {

	if (CheckHitKeyAll())
	{
		return 1;
	}

	return 0;
}

void CResult::Draw()
{

}

CResult::~CResult()
{

}