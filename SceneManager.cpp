#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio)
{
	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	title = new Title();
	title->Init(dxCommon, input, audio);
	tutorial = new Tutorial();
	tutorial->Init(dxCommon, input, audio);
	game = new GameScene();

	scene = titleScene;
}

void SceneManager::Update()
{
	if (input->PressKeyTrigger(DIK_SPACE) && scene == titleScene)
	{
		scene = tutorialScene;
	}
	else if (input->PressKeyTrigger(DIK_SPACE) && scene == tutorialScene)
	{
		game->Init(dxCommon, input, audio);
		scene = gameScene;
	}

	if (scene == titleScene) {
		title->Update();
	}
	else if (scene == tutorialScene) {
		tutorial->Update();
	}
	else if (scene == gameScene){
		game->Update();
	}
}

void SceneManager::Draw()
{
	if (scene == titleScene) {
		title->Draw();
	}
	else if (scene == tutorialScene) {
		tutorial->Draw();
	}
	else if (scene == gameScene)
	{
		game->Draw();
	}
}
