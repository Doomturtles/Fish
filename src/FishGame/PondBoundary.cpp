#include "PondBoundary.h"
PondBoundary::PondBoundary(Vector2f pos, float size) : InvertedImmovableCollider(pos, size){
}
void PondBoundary::Render(shared_ptr<GraphicsEngine> pgfx) {
	pgfx->setDrawColor(SDL_COLOR_VIOLET);
	pgfx->drawCircle(*new Point2(pos.x, pos.y), size);
}