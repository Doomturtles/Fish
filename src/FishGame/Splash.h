#pragma once
#include "../engine/GameMath.h"
#include "MyGame.h"
using namespace std;
class Splash
{
private:
	Point2 pos;
	float age;
	float maxAge;
	int type;
public:
	bool deleteMe;
	Splash(Point2 splashPos, int splashType);
	~Splash();
	void Update();
	void Render(shared_ptr<GraphicsEngine> pgfx);
};

