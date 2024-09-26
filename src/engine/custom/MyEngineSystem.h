#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include "../GameMath.h"
#include <vector>
using namespace std;
class Object;
class Collider;
class MovableCollider;
class ImmovableCollider;
class Mover;
class ControllableCollider;

class MyEngineSystem {
	friend class XCube2Engine;
	private:
		MyEngineSystem();
		vector<Object*> objects;
		vector<Collider*> colliders; //has same references as objects list, but only includes things to collide with
	public:
		void Update();
		void RegisterNewObject(Object* newObject);
		void DeregisterObject(Object* oldObject);
};
class Object {
protected:
	Point2 PosAsInt();
public: 
	float size;
	Vector2f pos;
	virtual void UpdatePhysics(vector<Collider*> colliders) = 0;
};
class Collider : public Object {
public:
	Collider(Vector2f pos, float size);
	bool Intersects(Vector2f pos, float size);
};
class MovableCollider : public Collider { //these are circles
private:
	Vector2f velo;
	bool bouncy;
public:
	MovableCollider::MovableCollider(Vector2f pos, float size, bool pBouncy = false, Vector2f pVelo = *new Vector2f(0 ,0));
	void UpdatePhysics(vector<Collider*> colliders) override;
};
class ImmovableCollider : public Collider{ //nothing can move past this, these are also circles
private:
public:
	ImmovableCollider(Vector2f pos, float size);
	void UpdatePhysics(vector<Collider*> colliders) override;
};
class Mover : public Object{ //things dont collide with this but it collides with things
private:
	bool bouncy;
	float friction;
	void Slow();
protected:
	Vector2f velo;
	float bounceDamping;
public:
	Mover(Vector2f pPos, float pSize, float pFriction, bool pBouncy = true, float bounceDamp =1, Vector2f pVelo = *(new Vector2f(0, 0)));
	void UpdatePhysics(vector<Collider*> colliders) override;
	void ApplyForce(Vector2f force);
};
class ControllableCollider : public Object { // gives complete control of handling when and what to collide with to the child
protected:
	void SetCollider(Vector2f location, float radius);
	vector<Object*> currentOverlappingObjects;
public:
	ControllableCollider();
	void UpdatePhysics(vector<Collider*> colliders) override;
	void UpdatePhysicsAllObjects(vector<Object*> objects);
	bool Intersects(Object* o);
};


#endif