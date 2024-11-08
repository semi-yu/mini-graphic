#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

#include "../../common/datatype.cpp"

namespace graphical::auxiliary {
    struct colorRGBA {
    public:
        colorRGBA(
            quantity_float_scalar r,
            quantity_float_scalar g,
            quantity_float_scalar b,
            quantity_float_scalar a,
            bool is_visible=true
        ) : r(r), g(g), b(b), a(a), is_visible(is_visible) {}

        std::array<quantity_float_scalar, 4> value() {
            return std::array<quantity_float_scalar, 4>({r, g, b, static_cast<quantity_float_scalar>(is_visible?1.0:0.0)}); 
        }

        bool is_visible;
        quantity_float_scalar r, g, b, a;
    }; 

}

#endif