#include "Rock.h"
#include "../engine/custom/Media.h"
Rock::Rock(Vector2f pos, const int rockType) : ImmovableCollider(pos, size){
	switch (rockType) {
	case 1:
		size = 150;
		rockTexture = Media::Image("Fish");
		break;
	default:
		size = 159;
		rockTexture = Media::Image("Fish");
		break;
	}
}
void Rock::Render(shared_ptr<GraphicsEngine> pgfx) {
	SDL_Rect* src = new SDL_Rect{0, 0, 1500, 1000};
	SDL_Rect* dst = new SDL_Rect{ (int)pos.x - (int)size/2, (int)pos.y - (int)size / 2, (int)size, (int)size};
	pgfx->drawTexture(rockTexture, src, dst);
}