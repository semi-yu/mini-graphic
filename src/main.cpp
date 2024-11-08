#include <iostream>
#include <memory>

#include <fmt/core.h>

#include "./graphical/shader/loader.cpp"
#include "./graphical/shader/shader.cpp"
#include "./graphical/auxiliary/structure.cpp"

#include "./graphical/frame.cpp"
#include "./window/frame.cpp"

#include "./common/debug_handler.cpp"

int main() {
    auto window_frame = std::make_unique<window::Frame>(800, 600, "My Window"); 
    
    auto vertex_loader = std::make_unique<graphical::shader::FileLoader>("../src/shader/vertex.txt");
    auto fragment_loader = std::make_unique<graphical::shader::FileLoader>("../src/shader/fragment.txt");

    auto vertex = std::make_unique<graphical::shader::Shader>(
        graphical::shader::Type::vertex,
        std::move(vertex_loader)
    );
    vertex->prepare();

    auto fragment = std::make_unique<graphical::shader::Shader>(
        graphical::shader::Type::fragment,
        std::move(fragment_loader)
    );
    fragment->prepare();

    auto program = std::make_unique<graphical::shader::Program>();
    program->register_shader(std::move(vertex));
    program->register_shader(std::move(fragment));
    program->prepare();

    graphical::Frame graphical_frame(
        std::move(window_frame),
        std::move(program)
    );

    // ----------
    
    graphical::drawable::Drawable2dBuilder builder;

    quantity_float_scalar h = 0.7;

    float angle = 3.14/6;

    std::vector<quantity_vector2d> vertices;
    vertices.push_back(quantity_vector2d(0, h));
    vertices.push_back(
        quantity_vector2d(-h*glm::cos(angle), 
        -h*glm::sin(angle))
    );
    vertices.push_back(
        quantity_vector2d(h*glm::cos(angle), 
        -h*glm::sin(angle))
    );

    auto fill_colors = std::vector<graphical::auxiliary::colorRGBA>(); 
    fill_colors.push_back(graphical::auxiliary::colorRGBA(0.9, 0.27, 0.2, 0.3));

    auto stroke_colors = std::vector<graphical::auxiliary::colorRGBA>();
    stroke_colors.push_back(graphical::auxiliary::colorRGBA(0.9, 0.27, 0.2, 1.0));

    auto triangle = std::make_unique<graphical::drawable::Drawable2d>(builder
                    .vertices(vertices)
                    .fill_color(fill_colors)
                    .stroke_color(stroke_colors)
                    .build()
    );
    triangle->configure_opengl_context();

    graphical_frame.register_drawable(std::move(triangle));
    graphical_frame.program_loop();
    
    glCheckError();
    fmt::print("The program terminated without any problem if you see this message.");
    return 0;
}