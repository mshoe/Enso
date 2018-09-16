#pragma once
#include <memory>
#include <vector>
#include <iostream>

#include "sl.h"
#include "Actor.h"
class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();

	void DrawActors(vector<shared_ptr<Actor>> &actors);
};

