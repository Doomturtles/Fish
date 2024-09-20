#pragma once
#include "../engine/GameMath.h"
#include "MyGame.h"
using namespace std;
struct Attack;
class Net : ControllableCollider {
private:
	Point2 p1;
	Point2 p2;
	int stage; //determines wether alert is being shown, net is being swung, or fish are being killed
	float timer;
	float swipeTime;
	float alertTime;
public:
	Net(Attack* attack);
	bool IsDone();
	void Render(shared_ptr<GraphicsEngine> pgfx);
	void Update();
};