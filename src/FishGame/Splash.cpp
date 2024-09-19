#include "Splash.h"
using namespace std;
Splash::Splash(Point2 splashPos) {
	pos = splashPos;
	age = 0;
	maxAge = 100;
	deleteMe = false;
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
	pgfx->drawCircle(pos, age);
}