#define SDL_MAIN_HANDLED
#include "Application.h"

int main(int argc, char** argv)
{
	Crystal::Application* app = new Crystal::Application(Crystal::Application::Arguments(argc,argv), 
		Crystal::Application::Configuration().SetTitle("Test Application").SetSize({800,600}));
	return app->Exec();
}