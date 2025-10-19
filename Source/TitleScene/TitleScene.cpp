#include "TitleScene.h"
#include <DxLib.h>
#include "../../Library/Input.h"
#include "../Image.h"
#include "../Screen.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (Input::IsKeyDown(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawGraph(0, 0, Image::bg["Bg"], TRUE);
	DrawGraph(0, 0, Image::bg["Film"], TRUE);

	SetFontSize(70);
	int DrawWidth = GetDrawFormatStringWidth("TITLE", -1);
	DrawFormatString((Screen::WIDTH - DrawWidth) / 2, Screen::HEIGHT / 2 - 35, GetColor(255, 255, 255), "TITLE");
	SetFontSize(40);
	DrawWidth = GetDrawFormatStringWidth("Push [P]Key To Play", -1);
	DrawFormatString((Screen::WIDTH - DrawWidth) / 2, Screen::HEIGHT - 100, GetColor(255, 255, 255), "Push [P]Key To Play");
	SetFontSize(20);
}
