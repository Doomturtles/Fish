#include "Fish.h"
#include "../engine/custom/Media.h"
Fish::Fish(Vector2f fishPos, Point2 centrePoint) : Creature(fishPos, 30, 0.9f, true, 0.1f){
	maxCD = 10;
	movementCD = 1;
	centre = centrePoint;
}
void Fish::Render(shared_ptr<GraphicsEngine> pgfx) {
	SDL_Rect* src = new SDL_Rect{ 0, 0, 1500, 1000 };
	SDL_Rect* dst = new SDL_Rect{(int)pos.x, (int)pos.y, 50, 50};
	pgfx->drawTexture(Media::Image("Fish"), src, dst, Vector2f::Vector2fToDegrees(velo));
}
void Fish::Update() {
	movementCD -= 0.1f;
	if (movementCD < 0) {
		movementCD += maxCD;
		RandomMovement();
	}
}

void Fish::RandomMovement() {
	//50/50 chance of either a completely random direction, or a direction pointing towards the centre
	if (getRandom(1, 2) == 1) {
		ApplyForce(*Vector2f::GetRandomNormalisedVector() * 10);
	}
	else {
		ApplyForce(*Vector2f::GetRandomNormalisedVectorPointingTowards(new Vector2f(pos.x, pos.y), new Vector2f(centre.x, centre.y)) * 10);
	}
}

void Fish::AlertSplash(Point2 splashPos) {
	Vector2f* splashPosf = new Vector2f(splashPos.x, splashPos.y);
	Vector2f* angle = *splashPosf - pos;
	float splashDist = Vector2f::Magnitude(*angle) * 0.0001; //adjust the magnitude to a reasonable size
	float splashDistReciprocal = 1 / splashDist; //the reciprocal of the splash distance gets bigger the
	//closer the splash was, so the fish gets more scared and moves more if the splash was closer
	angle = Vector2f::Normalise(*angle);
	ApplyForce(*angle * -0.1f * splashDistReciprocal); //move in the direction of the splash, inverted
	//multiplied by the reciprocal of the distance so they move further if the splash was closer
}