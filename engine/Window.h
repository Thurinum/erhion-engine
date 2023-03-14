#ifndef ERHION_ENGINE_WINDOW_H
#define ERHION_ENGINE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "logging.h"

namespace Erhion::Engine {
    using namespace Erhion::Utils;

    class Window {
    public:
        explicit Window(const string& title);
        Window(const string& title, int width, int height);

        const int DEFAULT_WIDTH = 800;
        const int DEFAULT_HEIGHT = 600;

        void BeginRenderLoop(const std::function<void()>& renderCallback);
    private:
        GLFWwindow* m_window;

        void InitWindow(const string &title, int width, int height);
    };
}


#endif //ERHION_ENGINE_WINDOW_H
