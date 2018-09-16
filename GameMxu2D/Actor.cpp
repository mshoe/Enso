#include "Actor.h"



Actor::Actor()
{
}


Actor::~Actor()
{
}

PlayerActor::PlayerActor(glm::vec2 pos_, const string name_)
{
	pos = pos_;
	name = name_;
	vel = glm::vec2(0);
	acc = glm::vec2(0);
	mass = PLAYER_CIRCLE_MASS;
	des_speed = PLAYER_SPEED;
	shape = Circle(PLAYER_CIRCLE_SIZE);
	team = PLAYER;
	movedThisFrame = false;

	direction.resize(4, false);
}

void PlayerActor::Update()
{
}

shared_ptr<Actor> PlayerActor::Clone()
{
	return shared_ptr<Actor>();
}

RedActor::RedActor(glm::vec2 pos_, const string name_)
{
	pos = pos_;
	mass = RED_CIRCLE_MASS;
	name = name_;
	vel = glm::vec2(0);
	acc = glm::vec2(0);
	shape = Circle(RED_CIRCLE_SIZE);
	des_speed = RED_SPEED;
	team = ENEMY;
	movedThisFrame = false;
}

void RedActor::Update()
{
}

shared_ptr<Actor> RedActor::Clone()
{
	return shared_ptr<Actor>();
}


GreenActor::GreenActor(glm::vec2 pos_, const string name_)
{
	pos = pos_;
	mass = GREEN_CIRCLE_MASS;
	name = name_;
	vel = glm::vec2(0);
	acc = glm::vec2(0);
	shape = Circle(GREEN_CIRCLE_SIZE);
	des_speed = GREEN_SPEED;
	team = ALLY;
	movedThisFrame = false;
}

void GreenActor::Update()
{
}

shared_ptr<Actor> GreenActor::Clone()
{
	return shared_ptr<Actor>();
}

Wall::Wall(glm::vec2 pos_, float width, float height, const string name_)
{
	pos = pos_;
	name = name_;
	mass = INF_MASS;
	infMass = true;
	team = NEUTRAL;
	shape = Rectangle(width, height);
}

void Wall::Update()
{
}

shared_ptr<Actor> Wall::Clone()
{
	return shared_ptr<Actor>();
}
