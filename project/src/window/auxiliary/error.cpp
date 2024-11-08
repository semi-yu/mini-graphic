#ifndef __AUXILIARY_WINDOW_ERROR_CPP__
#define __AUXILIARY_WINDOW_ERROR_CPP__

#include <fmt/core.h>

#include "../../common/error.cpp"

namespace window::auxiliary {
    class GlfwInitFailure : public common::BaseError {
    public:
        GlfwInitFailure() {
            message = "GLFW window initialization have failed."; 
        }
    };

    class GladInitFailure : public common::BaseError {
    public:
        GladInitFailure() {
            message = "GLAD window initialization have failed."; 
        }
    }; 
}

#endif