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
}

void PlayScene::Draw()
{
	DrawGraph(0, 0, Image::bg["Bg"], TRUE);
	DrawGraph(0, 0, Image::bg["Film"], TRUE);
}
