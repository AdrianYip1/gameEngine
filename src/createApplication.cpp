#include "../include/game/game.h"
#include "../include/editor/editor.h"
#include <string>

Application* CreateApplication(int argc, char** argv) {
	if (argc > 1 && std::string(argv[1]) == "--editor") return new Editor();
	
	return new Game();
}