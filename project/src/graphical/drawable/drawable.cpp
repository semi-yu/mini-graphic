#include <GLAD/glad.h>

#include <fmt/core.h>

#include "../../common/datatype.cpp"
#include "../auxiliary/structure.cpp"
#include "../auxiliary/error.cpp"

namespace graphical::drawable {
    class Drawable2d {
    public:
        Drawable2d(
            const std::vector<quantity_vector2d> vertices, 
            const std::vector<graphical::auxiliary::colorRGBA> fill_color,
            const std::vector<graphical::auxiliary::colorRGBA> stroke_color
        ) : vertices(vertices), 
            fill_color(fill_color), 
            stroke_color(stroke_color), 
            raw_vertices_size(vertices.size()) {}

        ~Drawable2d() {
            glDeleteVertexArrays(1, &vertex_attribute_object);
            glDeleteBuffers(1, &vertex_buffer_object);
        }

        void bind() {
            glBindVertexArray(vertex_attribute_object);
        }
    
        void draw_fill() {
            glDrawArrays(GL_TRIANGLE_STRIP, 0, raw_vertices_size);
        }

        void draw_stroke() {
            glDrawArrays(GL_LINE_LOOP, 0, raw_vertices_size);
        }

        std::vector<quantity_float_scalar> __interleave() {
            if (fill_color.size() != 1 && fill_color.size() != vertices.size())
                throw graphical::auxiliary::InvalidSizeForInterleavingVector(
                    std::string("vertices"), std::string("fill_color")
                ); 
            if (stroke_color.size() != 1 && stroke_color.size() != vertices.size())
                throw graphical::auxiliary::InvalidSizeForInterleavingVector(
                    std::string("vertices"), std::string("stroke_color")
                ); 
            
            std::vector<quantity_float_scalar> res;
            res.reserve(vertices.size() * 10);

            unsigned int fsize = fill_color.size(), ssize = stroke_color.size();

            for (unsigned int vidx = 0; vidx < vertices.size(); vidx++) {
                unsigned int fidx = (fsize == 1)?0:vidx;
                unsigned int sidx = (ssize == 1)?0:vidx;

                res.push_back(quantity_float_scalar(vertices[vidx].x));
                res.push_back(quantity_float_scalar(vertices[vidx].y));

                auto [fr, fg, fb, fa] = fill_color[fidx].value();
                res.push_back(fr);
                res.push_back(fg);
                res.push_back(fb);
                res.push_back(fa);
                
                auto [sr, sg, sb, sa] = stroke_color[sidx].value();
                res.push_back(sr);
                res.push_back(sg);
                res.push_back(sb);
                res.push_back(sa);
            }

            return res;
        }

        void configure_opengl_context() {
            auto interleaved = __interleave();
            float* raw_vertices = interleaved.data();
            
            glGenVertexArrays(1, &vertex_attribute_object);
            glGenBuffers(1, &vertex_buffer_object);
            
            glBindVertexArray(vertex_attribute_object);

            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
            glBufferData(GL_ARRAY_BUFFER, interleaved.size() * sizeof(float), raw_vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
        
            // Unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0); 
            glBindVertexArray(0);
        }

    private:
        std::vector<quantity_vector2d> vertices;
        std::vector<graphical::auxiliary::colorRGBA> fill_color;
        std::vector<graphical::auxiliary::colorRGBA> stroke_color;

        size_t raw_vertices_size;

        GLuint vertex_attribute_object;
        GLuint vertex_buffer_object;
    };

    class Drawable2dBuilder {
    public:
        Drawable2dBuilder& vertices(const std::vector<quantity_vector2d> vertices) {
            this->build_vertices = vertices;
            return *this;
        }

        Drawable2dBuilder& fill_color(const std::vector<graphical::auxiliary::colorRGBA> color) {
            build_fill_color = color;
            return *this;
        }

        Drawable2dBuilder& stroke_color(const std::vector<graphical::auxiliary::colorRGBA> color) {
            build_stroke_color = color;
            return *this;
        }

        Drawable2d build() {
            auto ref = Drawable2d(
                build_vertices, 
                build_fill_color,
                build_stroke_color
            ); 
            return ref;
        }

    private:
        std::vector<quantity_vector2d> build_vertices;
        std::vector<graphical::auxiliary::colorRGBA> build_fill_color;
        std::vector<graphical::auxiliary::colorRGBA> build_stroke_color;
    }; 
}