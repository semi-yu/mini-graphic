
#include <memory>

#include <GLAD/glad.h>

#include "./drawable/drawable.cpp"
#include "../window/frame.cpp"

#include "../common/debug_handler.cpp"

namespace graphical {
    class Frame {
    public:
        Frame (
            std::unique_ptr<window::Frame> frame,
            std::unique_ptr<graphical::shader::Program> program
        ) : frame(std::move(frame)), program(std::move(program)) {}

        void draw_drawables() {
            for (auto& drawable: drawables) {
                std::string draw_mode("draw_mode");
                
                drawable->bind();
                
                program->send_integer_scalar(draw_mode, 0);
                drawable->draw_fill();

                program->send_integer_scalar(draw_mode, 1);
                drawable->draw_stroke();
            }
        }

        void register_drawable(std::unique_ptr<graphical::drawable::Drawable2d> drawable) {
            drawables.push_back(std::move(drawable));
        }

        void program_loop() {
            int cnt = 0;
            while(!frame->close_window()) {
                glClearColor(1.0, 1.0, 1.0, 1.0);
                glClear(GL_COLOR_BUFFER_BIT);

                program->use();
                draw_drawables();
                
                frame->post_process();
            }
            glCheckError();
        }
        
    private:
        std::unique_ptr<window::Frame> frame;
        std::unique_ptr<graphical::shader::Program> program;

        std::vector<std::unique_ptr<graphical::drawable::Drawable2d>> drawables; 
    }; 
}