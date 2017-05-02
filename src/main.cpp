#include "Application2D.h"

int main() {
	
	BaseApplication* app = new Application2D();
	if (app->startup())
		app->run();
	app->shutdown();

	return 0;
}