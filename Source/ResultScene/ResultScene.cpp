#include "ResultScene.h"
#include <DxLib.h>
#include "../../Library/Input.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}


void ResultScene::Draw()
{
	DrawString(0, 0, "RESULT SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}