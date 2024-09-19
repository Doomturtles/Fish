#include "Splash.h"
using namespace std;
Splash::Splash(Point2 splashPos, int splashType) {
	pos = splashPos;
	age = 0;
	maxAge = 100;
	deleteMe = false;
	type = splashType;
}
Splash::~Splash() {

}
void Splash::Update() {
	age += 1;
	if (age > maxAge) {
		deleteMe = true;
	}
}
void Splash::Render(shared_ptr<GraphicsEngine> pgfx) {
	pgfx->setDrawColor(SDL_COLOR_VIOLET);
	if (type == 1) {
		pgfx->drawCircle(pos, age);

	}
	else if (type == 2) {
		pgfx->drawCircle(pos, maxAge - age);
	}
}