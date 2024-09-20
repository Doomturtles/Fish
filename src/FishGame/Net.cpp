#include "Net.h"
#include "Fisherman.h"
Net::Net(Attack* attack) {
	p1 = attack->attackStart;
	p2 = attack->attackEnd;
	stage = 0; // 0 = alert being shown
	timer = 0;
	alertTime = 20;
	swipeTime = 5;
}
bool Net::IsDone() {
	return stage == 3;
}
void Net::Update() {
	timer += 0.1f;
	if (timer > alertTime + swipeTime) {
		stage = 3;
	}
	else if (timer > alertTime) {
		stage = 2;
	}
	else {
		stage = 1;
	}
}
void Net::Render(shared_ptr<GraphicsEngine> pgfx) {
	if (stage == 1 && (int)timer % 2 == 0) { //this makes the alert flash
		pgfx->setDrawColor(SDL_COLOR_RED);
		pgfx->DrawAlert(p1, p2, 100);
	}
	else if (stage == 2) {
		float netProgress = (timer - alertTime) / swipeTime;
		Point2 posDifference = p2 - p1;
		posDifference = posDifference * netProgress;
		Point2 imagePos = (p1 + posDifference);
		SDL_Rect* src = new SDL_Rect{ 0, 0, 1500, 1000 };
		SDL_Rect* dst = new SDL_Rect{ imagePos.x, imagePos.y, 50 ,50 };
		pgfx->drawTexture(Media::Image("Fish"), src, dst, Vector2f::Vector2fToDegrees(*new Vector2f(posDifference.x, posDifference.y)));
		
	}
}