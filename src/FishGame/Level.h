#pragma once
#include <vector>
#include "../engine/GameMath.h"
#include "MyGame.h"
using namespace std;
class Creature;
class Enemy;
class Splash;
class Rock;
class PondBoundary;
class Level
{
private:
	vector<Creature*> creatures; //fish ect
	vector<Enemy*> enemies; //should only ever be 1 but incase i want to do multi enemy levels later
	vector<Splash*> splashes;
	vector<Rock*> rocks;
	vector<PondBoundary*> boundaries;
	shared_ptr<GraphicsEngine> gfx;
	shared_ptr<MyEngineSystem> system;
	Point2 centre;
public:
	Level(shared_ptr<GraphicsEngine> pgfx, shared_ptr<MyEngineSystem> psystem, Point2 centrePoint);
	~Level();
	void Update();
	void CreateSplash(Point2 splashPos, int splashType);
	Mover* SpawnFish(Vector2f pos);
	void Render();
	ImmovableCollider* CreateBoundary(Vector2f pos, int rockType);
	InvertedImmovableCollider* CreatePondBoundary(vector<Vector2f*> pos, vector<float> size);
	Enemy* CreateEnemy();
	void Kill(Creature* creature);
};

