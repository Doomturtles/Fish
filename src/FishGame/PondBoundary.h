#pragma once
#include "MyGame.h"
class PondBoundary : public InvertedImmovableCollider {
public:
	PondBoundary(Vector2f ppos, float psize);
	void Render(shared_ptr<GraphicsEngine> pgfx);
};

