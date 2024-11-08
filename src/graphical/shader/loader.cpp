#ifndef __GRAPHICAL_SHADER_LOADER_CPP_
#define __GRAPHICAL_SHADER_LOADER_CPP_

#include <fstream>
#include <sstream>

#include "../auxiliary/error.cpp"

namespace graphical::shader {
    class ILoadable {
    public:
        virtual std::string load_source() = 0;
    }; 

    class DefaultLoader : public ILoadable {
    public:
        std::string load_source() override {
            return std::string("#version 440;\nint main() { }\n"); 
        }
    }; 

    class FileLoader : public ILoadable {
    public:
        FileLoader(
            const std::string& path
        ) : path(path) {}

        ~FileLoader() {}

        std::string load_source() override {
            std::ifstream file_stream(path);

            if (!file_stream.is_open()) {
                throw graphical::auxiliary::FileOpenFailure(path); 
            }

            std::stringstream buffer;
            buffer << file_stream.rdbuf();

            file_stream.close();

            return buffer.str();
        }

    private:
        std::string path;
    };
}

#endif