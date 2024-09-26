#include "Fisherman.h"
void Fisherman::InitiateAttack() {
	Attack* currentAttack = attacks[(getRandom(0, attacks.size()))];
	Net* newNet = new Net(level, mySystem, currentAttack);
	currentNets.push_back(newNet);
	mySystem->RegisterNewObject(newNet);
}
Fisherman::Fisherman(Level* plevel, shared_ptr<MyEngineSystem> psystem, vector<Attack*> pAttacks) {
	attacks = pAttacks;
	attackTimer = 0;
	mySystem = psystem;
	level = plevel;
}
void Fisherman::Update(vector<Creature*> creatures) {
	attackTimer += 0.1f;
	if (attackTimer > 30) {
		attackTimer -= 30;
		InitiateAttack();
	}
	for (Net* net : currentNets) {
		net->Update();
	}
}
void Fisherman::Render(shared_ptr<GraphicsEngine> pgfx) {
	pgfx->setDrawColor(SDL_COLOR_RED);
	if (currentNets.size() > 0) {
		if (currentNets[0]->IsDone()) {
			currentNets.erase(currentNets.begin()); //only checking if the first net is done because they 
			// should always be added in order anyway
		}
	}
	for (Net* net : currentNets) {
		net->Render(pgfx);
	}
}