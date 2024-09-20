#pragma once
#include "MyGame.h"
class Rock : public ImmovableCollider
{
private:
	SDL_Texture* rockTexture;
public:
	Rock(Vector2f pos, const int rockType);
	void Render(shared_ptr<GraphicsEngine> pgfx);
};

