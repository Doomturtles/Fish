#pragma once
#include "../engine/GameMath.h"
#include "MyGame.h"
using namespace std;
class Creature : public Mover
{
private:
protected:
public:
	Creature(Vector2f pos, float size, float friction, bool bouncy, float bounceDamp);
	virtual void Render(shared_ptr<GraphicsEngine> pgfx) = 0;
	virtual void Update() = 0;
	virtual void AlertSplash(Point2 splashPos) = 0;
};

