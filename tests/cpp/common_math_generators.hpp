#include <catch2/catch.hpp>
#include <math/vec2_t.hpp>
#include <math/vec3_t.hpp>
#include <math/vec4_t.hpp>
#include <math/mat3_t.hpp>
#include <math/quat_t.hpp>

#include <random>

namespace math {

template <typename T, typename V>
class RandomValueBase : public Catch::Generators::IGenerator<V> {
 public:
    RandomValueBase(T val_range_min, T val_range_max)
        : m_Dist(val_range_min, val_range_max),  // NOLINT
          m_Gen(std::random_device{}()) {}       // NOLINT

    auto get() const -> const V& override { return m_Value; }

 protected:
    /// Distribution from which to generate random real values
    std::uniform_real_distribution<T> m_Dist;
    /// The method used to generate random numbers
    std::minstd_rand m_Gen;
    /// The vector value to be exposed
    V m_Value;
};

//****************************************************************************//
//                        Generators for Vector types                         //
//****************************************************************************//

template <typename T>
class RandomVec2Generator : public RandomValueBase<T, Vector2<T>> {
 public:
    RandomVec2Generator(T val_range_min, T val_range_max)
        : RandomValueBase<T, Vector2<T>>(val_range_min, val_range_max) {}

    auto next() -> bool override {
        this->m_value = {this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen)};
        return true;
    }
};

template <typename T>
class RandomVec3Generator : public RandomValueBase<T, Vector3<T>> {
 public:
    RandomVec3Generator(T val_range_min, T val_range_max)
        : RandomValueBase<T, Vector3<T>>(val_range_min, val_range_max) {}

    auto next() -> bool override {
        this->m_Value = {this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen),
                         this->m_Dist(this->m_Gen)};
        return true;
    }
};

template <typename T>
class RandomVec4Generator : public RandomValueBase<T, Vector4<T>> {
 public:
    RandomVec4Generator(T val_range_min, T val_range_max)
        : RandomValueBase<T, Vector4<T>>(val_range_min, val_range_max) {}

    auto next() -> bool override {
        this->m_Value = {this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen),
                         this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen)};
        return true;
    }
};

template <typename T>
auto random_vec2(T val_range_min = static_cast<T>(-1.0),
                 T val_range_max = static_cast<T>(1.0))
    -> Catch::Generators::GeneratorWrapper<Vector2<T>> {
    return Catch::Generators::GeneratorWrapper<Vector2<T>>(
        Catch::Generators::pf::make_unique<RandomVec2Generator<T>>(
            val_range_min, val_range_max));
}

template <typename T>
auto random_vec3(T val_range_min = static_cast<T>(-1.0),
                 T val_range_max = static_cast<T>(1.0))
    -> Catch::Generators::GeneratorWrapper<Vector3<T>> {
    return Catch::Generators::GeneratorWrapper<Vector3<T>>(
        Catch::Generators::pf::make_unique<RandomVec3Generator<T>>(
            val_range_min, val_range_max));
}

template <typename T>
auto random_vec4(T val_range_min = static_cast<T>(-1.0),
                 T val_range_max = static_cast<T>(1.0))
    -> Catch::Generators::GeneratorWrapper<Vector4<T>> {
    return Catch::Generators::GeneratorWrapper<Vector4<T>>(
        Catch::Generators::pf::make_unique<RandomVec4Generator<T>>(
            val_range_min, val_range_max));
}

//****************************************************************************//
//                      Generators for Quaternion type                        //
//****************************************************************************//

template <typename T>
class RandomQuaternion : public RandomValueBase<T, Quaternion<T>> {
 public:
    RandomQuaternion() : RandomValueBase<T, Quaternion<T>>(-1.0, 1.0) {}

    auto next() -> bool override {
        this->m_Value = {this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen),
                         this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen)};
        return true;
    }
};

template <typename T>
auto random_quaternion() -> Catch::Generators::GeneratorWrapper<Quaternion<T>> {
    return Catch::Generators::GeneratorWrapper<Quaternion<T>>(
        Catch::Generators::pf::make_unique<RandomQuaternion<T>>());
}

}  // namespace math
