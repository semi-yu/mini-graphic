#ifndef __FRAME_CPP__
#define __FRAME_CPP__

#include <GLFW/glfw3.h>

#include "./auxiliary/error.cpp"

namespace window {
    class Frame {
    public:
        Frame(
            int width, int height,
            const std::string& title
        ) : width(width), height(height), title(title) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

            if (window == NULL) {
                glfwTerminate();
                throw window::auxiliary::GlfwInitFailure();
            }

            glfwMakeContextCurrent(window);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                glfwTerminate();
                throw window::auxiliary::GladInitFailure();
            }

            glViewport(0, 0, width, height);
        }

        ~Frame() {
            glfwTerminate();
        }

        bool close_window() const { 
            return glfwWindowShouldClose(window); 
        }

        std::pair<int, int> width_height() const {
            return std::pair<int, int>(width, height);
        }

        void post_process() {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }


    protected:
        int width, height;
        std::string title;
        GLFWwindow* window;
    }; 
}


#endif