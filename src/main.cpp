#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "glfwHelpers.h"
#include "../include/window/window.h"
#include "../include/application/application.h"
#include "../include/game/game.h"
#include "../include/editor/editor.h"

int main()
{
    Game game;
    game.run();
    return 0;
}
