#pragma once
#include "MyGame.h"
class PondBoundary : public InvertedImmovableCollider {
public:
	PondBoundary(vector<Vector2f*> pos, vector<float> size);
	void Render(shared_ptr<GraphicsEngine> pgfx);
};

