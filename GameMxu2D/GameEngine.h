#pragma once
#include <memory>
#include <vector>
#include <chrono>

#include "CollisionEngine.h"
#include "InputEngine.h"
#include "RenderEngine.h"

#include "Actor.h"
#include "sl.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void Init();
	void Loop();
	void InitActors();

private:
	unique_ptr<CollisionEngine> colEngine;
	unique_ptr<InputEngine> inputEngine;
	unique_ptr<RenderEngine> renderEngine;
	vector<shared_ptr<Actor>> actors;
	shared_ptr<PlayerActor> player;

	int score = 0;
};

