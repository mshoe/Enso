#include "main.h"




int main(int args, char *argv[])
{
	
	std::cout << "test";
	unique_ptr<GameEngine> gameEngine = make_unique<GameEngine>();
	
	std::cout << "test";

	gameEngine->Loop();
	
	std::cout << "test" << std::endl;
	slClose();// close the window and shut down SIGIL
	return 0;
}