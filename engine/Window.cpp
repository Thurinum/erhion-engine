#include "window.h"

Erhion::Engine::Window::Window() {
    if (!glfwInit())
        Log(CRITICAL, "window", "Failed to initialize GLFW");
}
