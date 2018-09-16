#include "CollisionEngine.h"



CollisionEngine::CollisionEngine()
{
	counter_ = 0;
}


CollisionEngine::~CollisionEngine()
{
}

void CollisionEngine::ComputeCollisions(vector<shared_ptr<Actor>> actors)
{
	/* Certainty: collision algorithm needs a vector of all the Actors
	 *

	 */
	for (int i = 0; i != actors.size()-1; ++i) {
		for (int j = i + 1; j != actors.size(); ++j) {
			if (AABBOverlap(actors[i], actors[j])) {
				if (CircleCollision(actors[i], actors[j])) {

					// resolve collision
					ResolveCollision(actors[i], actors[j]);
					PositionalCorrection(actors[i], actors[j]);
				}
			}
		}
	}
}

void CollisionEngine::ResolveCollision(shared_ptr<Actor> a1, shared_ptr<Actor> a2)
{
	if (a1 == nullptr || a2 == nullptr)
		return;
	glm::vec2 vel1 = (a1->vel * (a1->mass - a2->mass) + 2 * a2->mass * a2->vel) / (a1->mass + a2->mass);
	glm::vec2 vel2 = (a2->vel * (a2->mass - a1->mass) + 2 * a1->mass * a1->vel) / (a1->mass + a2->mass);

	a1->vel = vel1;
	a2->vel = vel2;
}

void CollisionEngine::ResolveInfCollision(shared_ptr<Actor> a, shared_ptr<Actor> ainf)
{
	// Collision where a has finite mass and ainf has infinite mass
	a->vel.x *= -1;
	
}

void CollisionEngine::UpdatePositions(vector<shared_ptr<Actor>> actors, shared_ptr<PlayerActor> player, float td)
{
	CruiseControl(player, td);
	for (int i = 0; i < actors.size(); ++i) {
		//if (actors[i]->movedThisFrame)
		//	continue;
		
		actors[i]->vel += actors[i]->acc * td;
		if (actors[i]->team == PLAYER) {
			actors[i]->vel -= actors[i]->vel * (PLAYER_FRICTION + actors[i]->internal_friction)* td;
		}

		if (actors[i]->team != PLAYER) { // move circle to player
			
			if (actors[i]->team == ENEMY) {
				glm::vec2 player_dir = glm::normalize(player->pos - actors[i]->pos);
				actors[i]->vel += player_dir * RED_ACC * td;
				actors[i]->vel -= actors[i]->vel * (RED_FRICTION + actors[i]->internal_friction) * td;
			}

			if (actors[i]->team == ALLY) {
				glm::vec2 player_dir = glm::normalize(player->pos - actors[i]->pos);
				actors[i]->vel += player_dir * GREEN_ACC * td;
				actors[i]->vel -= actors[i]->vel * (GREEN_FRICTION + actors[i]->internal_friction) * td;
			}
		}
		
		
		actors[i]->pos += actors[i]->vel * td;

		
		ComputeBorderEffects(actors, i, td);
		

		//actors[i]->movedThisFrame = true;
	}
}

void CollisionEngine::PositionalCorrection(shared_ptr<Actor> a1, shared_ptr<Actor> a2)
{
	glm::vec2 pos_diff = a2->pos - a1->pos;
	glm::vec2 normal = glm::normalize(pos_diff);
	const float percent = 0.8;
	const float slop = 0.01;

	float sum_radii = a1->shape.radius + a2->shape.radius;
	float penetrationDepth = sum_radii - glm::length(pos_diff);
	glm::vec2 correction = fmax(penetrationDepth - slop, 0.0f) * (1/a1->mass + 1/a2->mass) * percent * normal;
	a1->pos -= correction / a1->mass;
	a2->pos += correction / a2->mass;
}

bool CollisionEngine::AABBOverlap(shared_ptr<Actor> a1, shared_ptr<Actor> a2)
{
	// check if possible collision by AABB
	if (a1->pos.x + a1->shape.radius + a2->shape.radius > a2->pos.x
		&& a1->pos.x < a2->pos.x + a1->shape.radius + a2->shape.radius
		&& a1->pos.y + a1->shape.radius + a2->shape.radius > a2->pos.y
		&& a1->pos.y < a2->pos.y + a1->shape.radius + a2->shape.radius) {
		return true;
	}
	return false;
}

bool CollisionEngine::CircleCollision(shared_ptr<Actor> a1, shared_ptr<Actor> a2)
{
	// sum radii of circles, then compare with distance between circles

	float sum_radii = a1->shape.radius + a2->shape.radius;
	glm::vec2 distance = a1->pos - a2->pos;
	if ( pow(sum_radii, 2) >= glm::dot(distance, distance) ) {
		return true;
	}
	return false;
}

void CollisionEngine::CruiseControl(shared_ptr<PlayerActor> a, float td)
{
	// Cruise control system
	// Make player go at desired speed

	float a_speed = glm::length(a->vel);
	float error = a->des_speed - a_speed;

	
	float des_acc_mag = (error + PLAYER_FRICTION * a_speed);
	//cout << error << endl;
	a->acc = glm::vec2(0);
	for (int i = 0; i < 4; i++) {
		if (a->direction[i]) {
			switch (i) {
			case NORTH:
				a->acc.y = 0.7071f;
				break;
			case EAST:
				a->acc.x = 0.7071f;
				break;
			case SOUTH:
				a->acc.y = -0.7071f;
				break;
			case WEST:
				a->acc.x = -0.7071f;
				break;
			default:
				break;
			}
		}
	}
	a->acc *= des_acc_mag;

	
}

void CollisionEngine::ComputeBorderEffects(vector<shared_ptr<Actor>> actors, int i, float td)
{
	// BORDERS

	if (actors[i]->pos.x <= 0 || actors[i]->pos.x >= 400) {
		actors[i]->vel.x *= -1;
		actors[i]->pos.x += actors[i]->vel.x * td;
	}


	if (actors[i]->pos.y <= 0 || actors[i]->pos.y >= 400) {
		actors[i]->vel.y *= -1;
		actors[i]->pos.y += actors[i]->vel.y * td;
	}

	// GOAL BOX
	if (actors[i]->team != PLAYER) {
		if (actors[i]->pos.x >= 175 &&
			actors[i]->pos.x <= 225 &&
			actors[i]->pos.y >= 175 &&
			actors[i]->pos.y <= 225)
		{
			cout << "RED GOAL INTERSECT" << endl;
			actors[i]->touchedGoal = true;
			// true to let UpdatePositions know that actors has erased something
		}
	}
}
