#ifndef ERHION_ENGINE_WINDOW_H
#define ERHION_ENGINE_WINDOW_H

#include <GLFW/glfw3.h>
#include "logging.h"

namespace Erhion::Engine {
    class Window {
    public:
        Window() {
            Utils::Log();

            if (!glfwInit()) {
                return;
            }
        }
    };
}


#endif //ERHION_ENGINE_WINDOW_H
