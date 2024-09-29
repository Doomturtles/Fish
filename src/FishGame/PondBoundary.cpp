#include "PondBoundary.h"
PondBoundary::PondBoundary(vector<Vector2f*> pos, vector<float> size) : InvertedImmovableCollider(pos, size){
}
void PondBoundary::Render(shared_ptr<GraphicsEngine> pgfx) {
	pgfx->setDrawColor(SDL_COLOR_AQUA);
	for (int i = 0; i < positions.size(); i++) {
		Vector2f pos = *positions[i];
		pgfx->DrawFilledCircle(pos.x, pos.y, sizes[i]);
	}
}