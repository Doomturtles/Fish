#include "Fish.h"
#include "../engine/custom/Media.h"
Fish::Fish(Vector2f fishPos, Point2 centrePoint) : Creature(fishPos, 30, 0.9f, true, 0.1f){
	maxCD = 10;
	movementCD = 1;
	centre = centrePoint;
	dir = new Vector2f(0, 0);
	dirSlow = new Vector2f(0, 0);
}
void Fish::Render(shared_ptr<GraphicsEngine> pgfx) {
	float numCircles = 5;
	float circleSpacing = 20;
	for (float i = -1; i <= 1; i += (2 / numCircles)) {
		Vector2f circlePos = pos + ((*dir * i) * 30);
		pgfx->setDrawColor(SDL_COLOR_PINK);
		if (i == 1) {
			pgfx->DrawFilledCircle(circlePos.x, circlePos.y, 12);
		}
		else {
			pgfx->DrawFilledCircle(circlePos.x, circlePos.y, 10);
		}
	}
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
	Vector2f movementDirection;
	if (getRandom(1, 2) == 1) {
		movementDirection = *Vector2f::GetRandomNormalisedVector() * 10;
	}
	else {
		movementDirection = *Vector2f::GetRandomNormalisedVectorPointingTowards(new Vector2f(pos.x, pos.y), new Vector2f(centre.x, centre.y)) * 10;
	}
	dir = Vector2f::Normalise(movementDirection);
	ApplyForce(movementDirection);
}

void Fish::AlertSplash(Point2 splashPos, int splashType) {
	Vector2f* splashPosf = new Vector2f(splashPos.x, splashPos.y);
	Vector2f* angle = *splashPosf - pos;
	float splashDist = Vector2f::Magnitude(*angle) * 0.0001; //adjust the magnitude to a reasonable size
	float splashDistReciprocal = 1 / splashDist; //the reciprocal of the splash distance gets bigger the
	//closer the splash was, so the fish gets more scared and moves more if the splash was closer
	angle = Vector2f::Normalise(*angle);
	dir = angle;
	if (splashType == 1) {
		ApplyForce(*angle * -0.1f * splashDistReciprocal); //move in the direction of the splash, inverted
		//multiplied by the reciprocal of the distance so they move further if the splash was closer
	}
	else if (splashType == 2) {
		ApplyForce(*angle * 0.1f * splashDist * 5000); //move in the direction of the splash, inverted
		//multiplied by the splash distance so they move further if the splash was further
	}
}