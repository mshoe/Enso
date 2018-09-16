#include "InputEngine.h"



InputEngine::InputEngine()
{
}


InputEngine::~InputEngine()
{
}

void InputEngine::SystemKeys()
{
	
}

void InputEngine::PlayerMovement(shared_ptr<PlayerActor> &player)
{
	if (slGetKey(SL_KEY_RIGHT)) {
		player->direction[EAST] = true;
		player->direction[WEST] = false;
	}
	else if (slGetKey(SL_KEY_LEFT)) {
		player->direction[EAST] = false;
		player->direction[WEST] = true;
	}
	else {
		player->direction[EAST] = false;
		player->direction[WEST] = false;
	}
	if (slGetKey(SL_KEY_UP)) {
		player->direction[NORTH] = true;
		player->direction[SOUTH] = false;
	}
	else if (slGetKey(SL_KEY_DOWN)) {
		player->direction[NORTH] = false;
		player->direction[SOUTH] = true;
	}
	else {
		player->direction[NORTH] = false;
		player->direction[SOUTH] = false;
	}
	if (slGetKey(SL_KEY_LEFT_SHIFT)) {
		player->internal_friction = 0.f;
	}
	else {
		player->internal_friction = 0.0f;
	}
}
