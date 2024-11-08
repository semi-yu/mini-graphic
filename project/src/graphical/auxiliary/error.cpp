#ifndef __AUXILIARY_GRAPHICAL_ERROR_CPP__
#define __AUXILIARY_GRAPHICAL_ERROR_CPP__

#include <fmt/core.h>

#include "../../common/error.cpp"

namespace graphical::auxiliary {
    class FileOpenFailure : public common::BaseError {
    public:
        FileOpenFailure(
            const std::string& path
        ) {
            message = fmt::format("The file at {} could not be opened.", path); 
        }
    };

    class ShaderCompilationFailure : public common::BaseError {
    public:
        ShaderCompilationFailure(
            const std::string& shader_type,
            const std::string& error_message
        ) {
            message = fmt::format("[{0} shader compilation error]\n{1}", shader_type, error_message); 
        }
    };

    class ProgramCompilationFailure : public common::BaseError {
    public:
        ProgramCompilationFailure(
            const std::string& error_message
        ) {
            message = fmt::format("[program compilation error]\n{}", error_message);
        }
    }; 

    class InvalidSizeForInterleavingVector : public common::BaseError {
    public:
        InvalidSizeForInterleavingVector(
            const std::string& vector_name1, const std::string& vector_name2
        ) {
            message = fmt::format("Vector({0}) and Vector({1}) cannot be interleaved. Sub vector({1})'s size must be either 1 or same with the main vector({0})", vector_name1, vector_name2); 
        }
    }; 
}

#endif