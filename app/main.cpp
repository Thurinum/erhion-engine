#include <iostream>

#include "window.h"

using namespace Erhion;

int main() {
    Engine::Window w("Erhion Engine");

    w.BeginRenderLoop([]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });

    return EXIT_SUCCESS;
}