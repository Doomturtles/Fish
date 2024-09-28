#include "MyGame.h"
#include "Level.h"
#include "../engine/custom/Media.h"
MyGame::MyGame() : AbstractGame(){
	TTF_Font* font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->useFont(font);
	gfx->setVerticalSync(true);
	level = new Level(gfx, mySystem, *new Point2(350, 350));
	gfx->InitializeMedia();

	float rockSize = 150;
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(200, 0), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(400, 0), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(600, 0), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(0, 150), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(0, 300), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(0, 450), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(200, 600), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(400, 600), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(600, 600), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(800, 150), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(800, 300), 1));
	mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(800, 450), 1));
	level->CreateEnemy();
	mySystem->RegisterNewObject(level->CreatePondBoundary(*new Vector2f(400,200), 300));
}

MyGame::~MyGame() {
	delete level;
}

void MyGame::handleKeyEvents() {
	if (eventSystem->isDown(Mouse::BTN_LEFT)) {
		Point2 mousePos = eventSystem->getMousePos();
		level->CreateSplash(mousePos, 1);
	}
	if (eventSystem->isDown(Mouse::BTN_RIGHT)) {
		Point2 mousePos = eventSystem->getMousePos();
		level->CreateSplash(mousePos, 2);
	}
	if (eventSystem->isDown(Key::A)) {
		mySystem->RegisterNewObject(level->SpawnFish(*(new Vector2f(350, 350))));
	}
}
  
void MyGame::update() {
	level->Update();
	mySystem->Update();
}

void MyGame::render() {
	gfx->lockWindow();
	level->Render();
	gfx->unlockWindow();
}

void MyGame::renderUI() {

}