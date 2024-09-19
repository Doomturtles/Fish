#pragma once
#include <vector>
#include "../engine/GameMath.h"
#include "MyGame.h"
using namespace std;
class Creature;
class Enemy;
class Splash;
class Rock;
class Level
{
private:
	vector<Creature*> creatures; //fish ect
	vector<Enemy*> enemies; //should only ever be 1 but incase i want to do multi enemy levels later
	vector<Splash*> splashes;
	vector<Rock*> rocks;
	shared_ptr<GraphicsEngine> gfx;
	Point2 centre;
public:
	Level(shared_ptr<GraphicsEngine> pgfx, Point2 centrePoint);
	~Level();
	void Update();
	void CreateSplash(Point2 splashPos);
	Mover* SpawnFish(Vector2f pos);
	void Render();
	ImmovableCollider* CreateBoundary(Vector2f pos, float size);
	Enemy* CreateEnemy();
};

