#pragma once
#include <memory>
#include <iostream>

#include "Actor.h"
#include "sl.h"

class InputEngine
{
public:
	InputEngine();
	~InputEngine();

	void SystemKeys();
	void PlayerMovement(shared_ptr<PlayerActor> &player);
};

