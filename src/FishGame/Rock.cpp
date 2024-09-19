#include "Rock.h"
Rock::Rock(Vector2f pos, float size) : ImmovableCollider(pos, size){

}
void Rock::Render(shared_ptr<GraphicsEngine> pgfx) {
	pgfx->setDrawColor(SDL_COLOR_ORANGE);
	pgfx->drawCircle(PosAsInt(), size);
}