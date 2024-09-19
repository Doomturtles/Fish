#pragma once
#include "Creature.h"
#include "../engine/GameMath.h"
using namespace std;
class Fish : public Creature
{
private:
	float movementCD;
	float maxCD;
	Point2 centre;
	void RandomMovement();
public:
	Fish(Vector2f fishPos, Point2 centrePoint);
	void Render(shared_ptr<GraphicsEngine> pgfx) override;
	void Update() override;
	void AlertSplash(Point2 splashPos) override;
};

