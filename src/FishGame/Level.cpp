#include "Level.h"
#include "Creature.h"
#include "Enemy.h"
#include "Splash.h"
#include "Fish.h"
#include "Rock.h"
#include "Fisherman.h"
Level::Level(shared_ptr<GraphicsEngine> pgfx, shared_ptr<MyEngineSystem> psystem, Point2 centrePoint) {
	gfx = pgfx;
	centre = centrePoint;
}
Level::~Level() {
	creatures.clear();
	enemies.clear();
	splashes.clear();
	rocks.clear();
}
void Level::Update() {
	//update creatures
	for (Creature* c : creatures) {
		c->Update();
	}
	//update enemy
	for (Enemy* e : enemies) {
		e->Update(creatures);
	}
	//update splashes
	for (Splash* s : splashes) {
		s->Update();
	}
	//delete old splashes
	for (Splash* s : splashes) {
		if (s->deleteMe) {
			//find the current splash
			std::vector<Splash*>::iterator it = std::find(splashes.begin(), splashes.end(), s);
			//remove it from the list
			splashes.erase(it);
			//delete it
			delete(s);
			return; //escape the loop, this way only 1 splash is deleted per frame BUT if
			// 2 splashes were deleted in the same frame it would break the loop and the 
			// vector index would mess up
		}
	}
}
void Level::CreateSplash(Point2 splashPos, int splashType) {
	splashes.push_back(new Splash(splashPos, splashType));
	//alert creatures
	for (Creature* c : creatures) {
		c->AlertSplash(splashPos, splashType);
	}
}
Mover* Level::SpawnFish(Vector2f pos) {
	Fish* newFish = new Fish(pos, centre);
	creatures.push_back(newFish);
	return newFish;
}
ImmovableCollider* Level::CreateBoundary(Vector2f pos, int rockType) {
	Rock* newRock = new Rock(pos, 1);
	rocks.push_back(newRock);
	return newRock;
}
Enemy* Level::CreateEnemy() {
	Attack* attack1 = new Attack{*new Point2(200, 200), *new Point2(200, 300)};
	Attack* attack2 = new Attack{ *new Point2(300, 200), *new Point2(300, 300) };
	Attack* attack3 = new Attack{ *new Point2(400, 200), *new Point2(400, 300) };
	Attack* attack4 = new Attack{ *new Point2(500, 200), *new Point2(500, 300) };
	Enemy* enemy = new Fisherman(*new vector<Attack*>{ attack1, attack2, attack3, attack4 });
	enemies.push_back(enemy);
	return enemy;
}
void Level::Render() {
	//render creatures
	for (Creature* c : creatures) {
		c->Render(gfx);
	}
	//render enemies
	for (Enemy* e : enemies) {
		e->Render(gfx);
	}
	//render splashes
	for (Splash* s : splashes) {
		s->Render(gfx);
	}
	//render rocks
	for (Rock* r : rocks) {
		r->Render(gfx);
	}
}