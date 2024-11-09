#ifndef __AUXILIARY_ERROR_CPP__
#define __AUXILIARY_ERROR_CPP__

namespace common {
    class BaseError : public std::exception {
    public:
        const char* what() const noexcept override {
            return message.c_str(); 
        }
    protected:
        std::string message;
    }; 
}

#endif