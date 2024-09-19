#pragma once
#include "MyGame.h"
class Rock : public ImmovableCollider
{
private:
public:
	Rock(Vector2f pos, float size);
	void Render(shared_ptr<GraphicsEngine> pgfx);
};

