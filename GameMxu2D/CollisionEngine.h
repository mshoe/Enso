#pragma once
#include <memory>
#include <vector>
#include <iostream>

#include "Actor.h"

using namespace std;
class CollisionEngine
{
public:
	CollisionEngine();
	~CollisionEngine();

	void ComputeCollisions(vector<shared_ptr<Actor>> actors);
	void ResolveCollision(shared_ptr<Actor> a1, shared_ptr<Actor> a2);
	void ResolveInfCollision(shared_ptr<Actor> a, shared_ptr<Actor> ainf);
	void UpdatePositions(vector<shared_ptr<Actor>> actors, shared_ptr<PlayerActor> player, float td);
	void PositionalCorrection(shared_ptr<Actor> a1, shared_ptr<Actor> a2);
	bool AABBOverlap(shared_ptr<Actor> a1, shared_ptr<Actor> a2);
	bool CircleCollision(shared_ptr<Actor> a1, shared_ptr<Actor> a2);
	
	void CruiseControl(shared_ptr<PlayerActor> a, float td);
	void ComputeBorderEffects(vector<shared_ptr<Actor>> actors, int i, float td);

	int counter_;

};

