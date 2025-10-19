#include "ResultScene.h"
#include <DxLib.h>
#include "../../Library/Input.h"
#include "../Image.h"
#include "../Screen.h"

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
	DrawGraph(0, 0, Image::bg["Bg"], TRUE);
	DrawGraph(0, 0, Image::bg["Film"], TRUE);

	SetFontSize(70);
	int DrawWidth = GetDrawFormatStringWidth("RESULT", -1);
	DrawFormatString((Screen::WIDTH - DrawWidth) / 2, Screen::HEIGHT / 2 - 35, GetColor(255, 255, 255), "Result");
	SetFontSize(40);
	DrawWidth = GetDrawFormatStringWidth("Push [T]Key To Title", -1);
	DrawFormatString((Screen::WIDTH - DrawWidth) / 2, Screen::HEIGHT - 100, GetColor(255, 255, 255), "Push [T]Key To Title");
	SetFontSize(20);
}