#pragma once
#include <vector>
#include "../engine/GameMath.h"
#include "Enemy.h"
#include "Net.h"
#include "Creature.h"
using namespace std;
struct Attack {
	Point2 attackStart;
	Point2 attackEnd;
};
class Fisherman : public Enemy
{
private:
	vector<Attack*> attacks;
	void InitiateAttack();
	vector<Net*> currentNets;
	float attackTimer;
public:
	Fisherman(vector<Attack*> pAttacks);
	void Update(vector<Creature*>) override;
	void Render(shared_ptr<GraphicsEngine> pgfx) override;
};

