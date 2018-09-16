#include "GameEngine.h"



GameEngine::GameEngine()
{
	colEngine = make_unique<CollisionEngine>();
	inputEngine = make_unique<InputEngine>();
	renderEngine = make_unique<RenderEngine>();

	Init();
}


GameEngine::~GameEngine()
{
}

void GameEngine::Init()
{
	// set up our window and a few resources we need
	slWindow(400, 400, "Simple SIGIL Example", false);
	slSetFont(slLoadFont("ttf/white_rabbit.ttf"), 24);
	slSetTextAlign(SL_ALIGN_CENTER);
	InitActors();
}


using namespace std::chrono;

void GameEngine::Loop()
{
	int tex = slLoadTexture("png/flare.png");
	
	// delete
	float x = 50;
	float y = 50;

	steady_clock::time_point t1 = steady_clock::now();

	//float dur = 1.f/60.f;
	duration<float> steady_dur = duration_cast<duration<float>>(t1 - t1);
	float addRedBall = 0.f;
	float addGreenBall = 0.f;
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		
		if (slGetKey(SL_KEY_ENTER)) {
			InitActors();
		}
		
		/*
		// background glow
		slSetForeColor(0.1, 0.9, 0.2, 0.4);
		slSprite(tex, 200, 240, 300, 200);
		*/
		// large text and fat line
		slSetForeColor(0.0, 0.8, 0.2, 1.0);
		slSetFontSize(24);
		string score_str = "SCORE: ";
		score_str += to_string(score);
		slText(200, 250, score_str.c_str());
		slRectangleFill(200, 240, 100, 7);
		/*
		// smaller subtext
		slSetFontSize(14);
		slText(200, 220, "A game by mxu!");
		slLine(48, 210, 352, 210);
		*/

		// GOAL BOX
		slSetForeColor(1, 1, 0, 1);
		slRectangleFill(200, 200, 50, 50);

		

		

		colEngine->UpdatePositions(actors, player, steady_dur.count());
		// get rid of actors that touch goal
		for (int i = 0; i < actors.size();) {
			if (actors[i]->touchedGoal) {
				if (actors[i]->team == ENEMY)
					score++;
				if (actors[i]->team == ALLY)
					score -= 1000;

				actors.erase(actors.begin() + i);
				
			}
			else {
				++i;
			}
		}

		//cout << "out of loop" << endl;

		colEngine->ComputeCollisions(actors);
		
		inputEngine->PlayerMovement(player);
		renderEngine->DrawActors(actors);

		//cout << player->pos.x << "," << player->pos.y << " | " << actors[1]->vel.x << "," << actors[1]->vel.y << endl;
		slRender();// draw everything
		

		// add ball randomly
		addRedBall += steady_dur.count();
		if (addRedBall >= 2.f) {
			addRedBall = 0.f;
			float rand_x = rand() % 375 + 25;
			float rand_y = rand() % 375 + 25;
			actors.insert(actors.end(), make_shared<RedActor>(glm::vec2(rand_x, rand_y), "ENEMY"));
			cout << "NEW ENEMY SPAWNED" << endl;
		}

		addGreenBall += steady_dur.count();
		if (addGreenBall >= 10.f) {
			addGreenBall = 0.f;
			float rand_x = rand() % 375 + 25;
			float rand_y = rand() % 75 + 25;
			actors.insert(actors.end(), make_shared<GreenActor>(glm::vec2(rand_x, rand_y), "ALLY"));
			cout << "NEW ALLY SPAWNED" << endl;
		}

		steady_clock::time_point t2 = steady_clock::now();
		steady_dur = duration_cast<duration<float>>(t2 - t1);
		t1 = t2;

		//cout << steady_dur.count() << endl;
	}
}

void GameEngine::InitActors()
{
	score = 0;
	actors.clear();
	player = make_shared<PlayerActor>(glm::vec2(50, 50), "PLAYER");
	actors.insert(actors.end(), player);

	actors.insert(actors.end(), make_shared<RedActor>(glm::vec2(300, 300), "ENEMY1"));
	actors.insert(actors.end(), make_shared<RedActor>(glm::vec2(200, 300), "ENEMY2"));
	actors.insert(actors.end(), make_shared<RedActor>(glm::vec2(100, 300), "ENEMY3"));
	actors.insert(actors.end(), make_shared<RedActor>(glm::vec2(300, 200), "ENEMY4"));
	actors.insert(actors.end(), make_shared<RedActor>(glm::vec2(200, 200), "ENEMY5"));
	actors.insert(actors.end(), make_shared<RedActor>(glm::vec2(100, 200), "ENEMY6"));
	actors.insert(actors.end(), make_shared<RedActor>(glm::vec2(300, 100), "ENEMY7"));
	actors.insert(actors.end(), make_shared<GreenActor>(glm::vec2(100, 50), "ALLY1"));
}
