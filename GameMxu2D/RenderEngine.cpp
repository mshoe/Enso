#include "RenderEngine.h"



RenderEngine::RenderEngine()
{
}


RenderEngine::~RenderEngine()
{
}

void RenderEngine::DrawActors(vector<shared_ptr<Actor>> &actors)
{
	vector<shared_ptr<Actor>>::iterator it;
	for (it = actors.begin(); it != actors.end(); ++it) {
		
		Actor &actor = **it;
		switch (actor.team) {
		case PLAYER:
			slSetForeColor(1, 1, 1, 0.4);
			break;
		case ENEMY:
			slSetForeColor(1, 0, 0, 0.4);
			break;
		case ALLY:
			slSetForeColor(0, 1, 0, 0.4);
			break;
		default:
			break;
		}
		if (actor.team != NEUTRAL)
			slCircleFill(actor.pos.x, actor.pos.y, actor.shape.radius, 30);
		else
			slRectangleFill(actor.pos.x, actor.pos.y, actor.shape.width, actor.shape.height);
	}
}
