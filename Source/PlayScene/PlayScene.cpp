#include "PlayScene.h"
#include <DxLib.h>
#include "Stage/BaseStage.h"
#include "../../Library/Input.h"
#include "../Image.h"

PlayScene::PlayScene()
{
	new BaseStage();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_R)) {
		SceneManager::ChangeScene("RESULT");
	}
}

void PlayScene::Draw()
{
	DrawGraph(0, 0, Image::bg["Bg"], TRUE);
	DrawGraph(0, 0, Image::bg["Film"], TRUE);

	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
}
