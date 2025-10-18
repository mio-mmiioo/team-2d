#include "App.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Time.h"
#include <DxLib.h>
#include "Input.h"
#include "../Source/Sound.h"
#include "../Source/Image.h"

void AppInit()
{
	ObjectManager::Init();
	SceneManager::Init();
	Time::Init();
	Sound::Init();
	Image::Init();
}

void AppUpdate()
{
	Input::KeyStateUpdate();
	SceneManager::Update();
	ObjectManager::Update();
}

void AppDraw()
{
	Time::Refresh();
	SceneManager::Draw();
	ObjectManager::Draw();
}

void AppRelease()
{
	ObjectManager::Release();
	SceneManager::Release();
}

bool AppIsExit()
{
	return SceneManager::IsExit();
}