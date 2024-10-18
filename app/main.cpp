#include "window.h"

using namespace Erhion::Engine;

DECLARE_LOG_CATEGORY(App)

int main() {
    Window w("My Super Window");
    
    w.BeginRenderLoop([]() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });

    return EXIT_SUCCESS;
}