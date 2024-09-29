#pragma once
#include "MyGame.h"
class Rock : public ImmovableCollider
{
private:
public:
	Rock(Vector2f pos, const int rockType);
	void Render(shared_ptr<GraphicsEngine> pgfx);
};

