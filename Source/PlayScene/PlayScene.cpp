#include "PlayScene.h"
#include <DxLib.h>
#include "Stage/Stage.h"
#include "../../Library/Input.h"

PlayScene::PlayScene()
{
	new Stage(1);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
