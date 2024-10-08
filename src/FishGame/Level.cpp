#include "Level.h"
#include "Creature.h"
#include "Enemy.h"
#include "Splash.h"
#include "Fish.h"
#include "Rock.h"
#include "PondBoundary.h"
#include "Fisherman.h"
#include <algorithm>
#include <vector>
using namespace std;
Level::Level(shared_ptr<GraphicsEngine> pgfx, shared_ptr<MyEngineSystem> psystem, Point2 centrePoint) {
	gfx = pgfx;
	centre = centrePoint;
	system = psystem;
}
Level::~Level() {
	creatures.clear();
	enemies.clear();
	splashes.clear();
	rocks.clear();
	boundaries.clear();
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
	Rock* newRock = new Rock(pos, rockType);
	rocks.push_back(newRock);
	return newRock;
}
InvertedImmovableCollider* Level::CreatePondBoundary(vector<Vector2f*> pos, vector<float> size) {
	PondBoundary* newBound = new PondBoundary(pos, size);
	boundaries.push_back(newBound);
	return newBound;
}
Enemy* Level::CreateEnemy() {
	Enemy* enemy = new Fisherman(this, system, *new vector<Attack*>{
		new Attack{ *new Point2(250, 200), *new Point2(250, 300)},
		new Attack{*new Point2(150, 200), *new Point2(150, 300)},
		new Attack{ *new Point2(400, 200), *new Point2(400, 300) } });
	enemies.push_back(enemy);
	return enemy;
}
void Level::Render() {
	//render boundaries
	for (PondBoundary* pb : boundaries) {
		pb->Render(gfx);
	}
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
	for (Enemy* e : enemies) {
		e->Render(gfx);
	}
}
void Level::Kill(Creature* creature) {
	creatures.erase(std::remove(creatures.begin(), creatures.end(), creature), creatures.end());
}