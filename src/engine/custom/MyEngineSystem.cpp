#include "MyEngineSystem.h"


MyEngineSystem::MyEngineSystem() {

}
void MyEngineSystem::Update()
{
	for (Object* o : objects) {
		o->UpdatePhysics(colliders);
	}
}

void MyEngineSystem::RegisterNewObject(Object* newObject)
{
	objects.push_back(newObject);
	if (dynamic_cast<Collider*>(newObject)) {
		colliders.push_back(static_cast<Collider*>(newObject));
	}
}

Point2 Object::PosAsInt() {
	return *new Point2((int)pos.x, (int)pos.y);
}

Collider::Collider(Vector2f pPos, float pSize) {
	pos = pPos;
	size = pSize;
}

bool Collider::Intersects(Vector2f otherPos, float otherSize)
{
	Vector2f* difference = pos - otherPos;
	float distance = Vector2f::Magnitude(*difference);
	return distance < (size + otherSize);
}

ImmovableCollider::ImmovableCollider(Vector2f pos, float size) : Collider(pos, size){
}

void ImmovableCollider::UpdatePhysics(vector<Collider*> colliders)
{
	//do nothing
}


MovableCollider::MovableCollider(Vector2f pos, float size, bool pBouncy, Vector2f pVelo) : Collider(pos, size){
	bouncy = pBouncy;
	velo = pVelo;
}
void MovableCollider::UpdatePhysics(vector<Collider*> colliders) {
	Vector2f oldPos = pos;// remember the old pos incase we collide with something and need to go back
	pos += velo;
	for (Collider* c : colliders) {
		//dont collide with self
		if (c != this) {
			//if, after moving we would intersect with a collider, then we dont move
			if (c->Intersects(pos, size)) {
				pos = oldPos;
				if (bouncy) {
					//if bouncy, bounce, again this should really calculate a collision normal
					//but its not really necesarry as these collisions shouldnt really happen  too often
					velo = velo * -1;
				}
			}
		}
	}
}





Mover::Mover(Vector2f pPos, float pSize, float pFriction, bool pBouncy, float bounceDamp, Vector2f pVelo) {
	pos = pPos;
	size = pSize;
	friction = pFriction;
	bouncy = pBouncy;
	bounceDamping = bounceDamp;
	velo = pVelo;
}
void Mover::UpdatePhysics(vector<Collider*> colliders) {
	Slow();
	Vector2f oldPos = pos;// remember the old pos incase we collide with something and need to go back
	pos += velo;
	for (Collider* c : colliders) {
		//if, after moving we would intersect with a collider, then we dont move
		if (c->Intersects(pos, size)) {
			pos = oldPos;
			//bounce if bouncy
			if (bouncy) {
				velo = velo * -1; //invert the velocity
				velo = velo * bounceDamping; //reduce the velocity so it doesnt bounce too much
			}
		}
	}
}
void Mover::ApplyForce(Vector2f force) {
	velo += force;
}
void Mover::Slow() { // used to calculate friction
	velo = velo * friction;
}

ControllableCollider::ControllableCollider() {
	currentOverlappingColliders = *new vector<Collider*>();
}
void ControllableCollider::SetCollider(Vector2f location, float radius) {
	size = radius;
	pos = location;
}
void ControllableCollider::UpdatePhysics(vector<Collider*> colliders) {
	currentOverlappingColliders.clear();
	for (Collider* c : colliders) {
		if (c->Intersects(pos, size)) {
			currentOverlappingColliders.push_back(c);
		}
	}
}