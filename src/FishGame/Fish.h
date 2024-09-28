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
	Vector2f* dir;
	Vector2f* dirSlow; // a vector that slowly follows the direciton of the fish, used to animate
	void RandomMovement();
public:
	Fish(Vector2f fishPos, Point2 centrePoint);
	void Render(shared_ptr<GraphicsEngine> pgfx) override;
	void Update() override;
	void AlertSplash(Point2 splashPos, int splashType) override;
};

