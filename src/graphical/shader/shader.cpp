#ifndef __GRAPHICAL_CPP__
#define __GRAPHICAL_CPP__

#include <array>
#include <memory>
#include <vector>

#include <iostream>
#include <sstream>
#include <fstream>

#include <GLAD/glad.h>

#include "../auxiliary/error.cpp"

#include "../../common/debug_handler.cpp"

namespace graphical::shader {
    enum class Type {
        vertex,
        geometry,
        fragment
    }; 

    std::array<GLenum, 3> type_table = { 
        GL_VERTEX_SHADER, 
        GL_GEOMETRY_SHADER, 
        GL_FRAGMENT_SHADER, 
    };

    std::array<std::string, 3> name_table = { 
        std::string("vertex"), 
        std::string("geometry"), 
        std::string("fragment"), 
    }; 

    class Shader {
    public:
        Shader(
            Type type,
            std::unique_ptr<graphical::shader::ILoadable> loadable
        ) : type(type), loadable(std::move(loadable)) {}

        void prepare() {
            const char* source = loadable->load_source().c_str();
            int success;
            char log[1024];

            shader_index = glCreateShader(type_table.at(static_cast<int>(type))); 
            glShaderSource(shader_index, 1, &source, NULL);
            glCompileShader(shader_index);

            glGetShaderiv(shader_index, GL_COMPILE_STATUS, &success);

            if (!success) {
                glGetShaderInfoLog(shader_index, 1024, NULL, log);
                throw graphical::auxiliary::ShaderCompilationFailure(
                    name_table.at(static_cast<int>(type)),
                    std::string(log)
                ); 
            }
        }

        GLuint get_shader_index() {
            return shader_index;
        }

    private:
        GLuint shader_index; 
        Type type;
        std::unique_ptr<graphical::shader::ILoadable> loadable;
    };

    class Program {
    public:
        void register_shader(std::unique_ptr<graphical::shader::Shader> shader) {
            shaders.push_back(std::move(shader));
        }

        void prepare() {
            int success;
            char log[1024]; 

            program_index = glCreateProgram();

            for (auto& shader: shaders)
                glAttachShader(program_index, shader->get_shader_index());

            glLinkProgram(program_index);

            glGetProgramiv(program_index, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(program_index, 1024, NULL, log);
                throw graphical::auxiliary::ProgramCompilationFailure(
                    std::string(log)
                ); 
            }

            for (const auto& shader : shaders)
                glDeleteShader(shader->get_shader_index());
        }

        void use() {
            glUseProgram(program_index);
        }

        void send_integer_scalar(const std::string& var_name, int value) {
            glUniform1i(glGetUniformLocation(program_index, var_name.c_str()), value);
        }

    private:
        GLuint program_index;
        std::vector<std::unique_ptr<Shader>> shaders;
    }; 
}

#endif