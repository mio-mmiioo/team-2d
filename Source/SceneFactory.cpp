#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "../Library/BootScene.h"
#include "TitleScene/TitleScene.h"
#include "PlayScene/PlayScene.h"

SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name)
{
	if (name == "TITLE")
	{
		return new TitleScene();
	}
	if (name == "PLAY")
	{
		return new PlayScene();
	}
	MessageBox(NULL, ("���̃V�[���͂���܂���\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
