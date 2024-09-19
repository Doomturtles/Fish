#include "MyGame.h"
#include "Level.h"
#include "../engine/custom/Media.h"
MyGame::MyGame() : AbstractGame(){
	TTF_Font* font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->useFont(font);
	gfx->setVerticalSync(true);
	level = new Level(gfx, *new Point2(350, 350));
	gfx->InitializeMedia();
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
	if (eventSystem->isDown(Key::S)) {
		float rockSize = 150;
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(200, 0), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(400, 0), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(600, 0), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(0, 150), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(0, 300), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(0, 450), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(200, 600), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(400, 600), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(600, 600), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(800, 150), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(800, 300), rockSize));
		mySystem->RegisterNewObject(level->CreateBoundary(*new Vector2f(800, 450), rockSize));
		level->CreateEnemy();
	}
}
  
void MyGame::update() {
	level->Update();
	mySystem->Update();
}

void MyGame::render() {
	level->Render();
}

void MyGame::renderUI() {

}