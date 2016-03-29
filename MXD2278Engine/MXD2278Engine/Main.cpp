#include "Engine.h"

int main() {
	Engine engine = Engine();

	if (!engine.init())
		return -1;

	if (!engine.bufferModels())
		return -1;

	//Create clear color
	glClearColor(.392f, .584f, .929f, 1.0f);
	if(engine.useShaders())
		engine.gameLoop();

	return 0;
}