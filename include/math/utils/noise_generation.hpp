#pragma once

#include <FastNoiseLite.h>

#include <math/vec2_t_decl.hpp>
#include <math/vec3_t_decl.hpp>

namespace math {

template <typename FloatType>
class NoiseGenerator {
 public:
    enum NoiseType {
        TYPE_PERLIN = FastNoiseLite::NoiseType::NoiseType_Perlin,
        TYPE_SIMPLEX = FastNoiseLite::NoiseType::NoiseType_OpenSimplex2,
    };

    explicit NoiseGenerator(NoiseType noise_type) {
        m_FnlGenerator.SetNoiseType(
            static_cast<FastNoiseLite::NoiseType>(noise_type));
    }

    MATH3D_NODISCARD auto GetNoise1D(FloatType x);

    MATH3D_NODISCARD auto GetNoise2D(FloatType x, FloatType y);

    MATH3D_NODISCARD auto GetNoise2D(Vector2<FloatType> xy);

    MATH3D_NODISCARD auto GetNoise3D(FloatType x, FloatType y, FloatType z);

    MATH3D_NODISCARD auto GetNoise3D(Vector3<FloatType> xyz);

 protected:
    FastNoiseLite m_FnlGenerator;
};

}  // namespace math
