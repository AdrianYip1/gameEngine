#include "../include/application/application.h"

// argc: number of command line words
// argv: array of these words
// This is done to seperate the engine/editor with the actual games
// CreateApplication creates a game when argc = 1
// editor mode when argc > 1 (with a flag)
extern Application* CreateApplication(int argc, char** argv);

int main(int argc, char** argv)
{
    Application* app = CreateApplication(argc, argv);
    app->run();
    delete app;
    return 0;
}
