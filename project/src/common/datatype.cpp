#ifndef __COMMON_DATATYPE_H__
#define __COMMON_DATATYPE_H__

#include <glm/glm.hpp>

#define SINGLE 32
#define DOUBLE 64

#define FLOAT_RESOLUTION SINGLE
#define INT_RESOLUTION SINGLE

#if (FLOAT_RESOLUTION == SINGLE)
    #define quantity_float_scalar glm::float32
    #define quantity_vector2d glm::vec2
#elif (FLOAT_RESOLUTION == DOUBLE)
    #define quantity_float_scalar glm::float64
    #define quantity_vector2d glm::dvec2
#else
    #error FLOAT_RESOLUTION is must be defined and restricted to SINGLE or DOUBLE
#endif

#if (INT_RESOLUTION == SINGLE)
    #define quantity_indice uint32_t
#elif (INT_RESOLUTION == DOUBLE)
    #define quantity_indice uint64_t
#else
    #error INT_RESOLUTION is must be defined and restricted to SINGLE or DOUBLE
#endif

#endif