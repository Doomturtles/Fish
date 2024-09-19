#pragma once
#include <vector>
#include "Creature.h"
using namespace std;
class Enemy
{
public:
	virtual void Update(vector<Creature*> creatures) = 0;
	virtual void Render(shared_ptr <GraphicsEngine> pgfx) = 0;
};

