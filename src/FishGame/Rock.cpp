#include "Rock.h"
#include "../engine/custom/Media.h"
Rock::Rock(Vector2f pos, const int rockType) : ImmovableCollider(pos, size){
	switch (rockType) {
	case 1:
		size = 190;
		break;
	case 2:
		size = 50;
		break;
	default:
		size = 20;
		break;
	}
}
void Rock::Render(shared_ptr<GraphicsEngine> pgfx) {
	pgfx->setDrawColor(SDL_COLOR_GRAY);
	pgfx->DrawFilledCircle(pos.x, pos.y, size);
}