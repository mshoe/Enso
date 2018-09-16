#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>

#include "Transform.h"
#include "Shape.h"

using namespace std;

const int PLAYER_CIRCLE_SIZE = 15;
const int RED_CIRCLE_SIZE = 10;
const int GREEN_CIRCLE_SIZE = 12;
const float RED_CIRCLE_MASS = 10;
const float GREEN_CIRCLE_MASS = 12;
const float PLAYER_CIRCLE_MASS = 15;
const float INF_MASS = 0;
const float PLAYER_SPEED = 200;
const float PLAYER_ACC = 200;
const float RED_SPEED = 100;
const float RED_ACC = 50;
const float RED_FRICTION = 0.5f;
const float GREEN_SPEED = 50;
const float GREEN_ACC = 20;
const float GREEN_FRICTION = 0.9f;
const float PLAYER_FRICTION = 0.4f;

enum Team {
	PLAYER,
	ENEMY,
	ALLY,
	NEUTRAL
};

enum DIRECTION {
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update() = 0;
	virtual shared_ptr<Actor> Clone() = 0;

	Shape shape;
	string name;

	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;

	float rotation = 0;

	float mass;
	bool infMass = false;
	float des_speed;
	int team;
	bool movedThisFrame;
	float internal_friction = 0.f;
	bool touchedGoal = false;
};

class PlayerActor : public Actor
{
public:
	PlayerActor(glm::vec2 pos_, const string name_);
	virtual ~PlayerActor() {};
	virtual void Update(); // process player keyboard input to move
	virtual shared_ptr<Actor> Clone();
	
	vector<bool> direction;
private:
	PlayerActor() {}
};

class RedActor : public Actor
{
public:
	RedActor(glm::vec2 pos_, const string name_);
	virtual ~RedActor() {};
	virtual void Update(); // Check the position of the PlayerActor to determine where to move
	virtual shared_ptr<Actor> Clone();
	
	shared_ptr<PlayerActor> player;
};

class GreenActor : public Actor
{
public:
	GreenActor(glm::vec2 pos_, const string name_);
	virtual ~GreenActor() {};
	virtual void Update(); // check position of the PlayerActor to determine where to move
	virtual shared_ptr<Actor> Clone();

	shared_ptr<PlayerActor> player;
};

class Wall : public Actor
{
public:
	Wall(glm::vec2 pos_, float width, float height, const string name_);
	virtual ~Wall() {};
	virtual void Update();
	virtual shared_ptr<Actor> Clone();
};