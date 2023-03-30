#include <catch2/catch.hpp>
#include <math/vec2_t.hpp>
#include <math/vec3_t.hpp>
#include <math/vec4_t.hpp>
#include <math/mat3_t.hpp>
#include <math/quat_t.hpp>
#include <math/mat4_t.hpp>

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
    /// The random value to be exposed
    V m_Value;
};

//****************************************************************************//
//                        Generators for Vector types                         //
//****************************************************************************//

//-------------------//
// Custom Generators //
//-------------------//

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

//--------------------//
// Generator wrappers //
//--------------------//

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
//                       Generators for Matrix3 types                         //
//****************************************************************************//

//-------------------//
// Custom Generators //
//-------------------//

template <typename T>
class RandomMatrix3 : public RandomValueBase<T, Matrix3<T>> {
 public:
    RandomMatrix3(T range_min, T range_max)
        : RandomValueBase<T, Matrix3<T>>(range_min, range_max) {}

    auto next() -> bool override {
        this->m_Value =
            Matrix3<T>(this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen),
                       this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen),
                       this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen),
                       this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen),
                       this->m_Dist(this->m_Gen));
        return true;
    }
};

template <typename T>
class RandomRotationXMatrix3 : public RandomValueBase<T, Matrix3<T>> {
 public:
    RandomRotationXMatrix3(T angle_min, T angle_max)
        : RandomValueBase<T, Matrix3<T>>(angle_min, angle_max) {}

    auto next() -> bool override {
        this->m_Value = Matrix3<T>::RotationX(this->m_Dist(this->m_Gen));
        return true;
    }
};

template <typename T>
class RandomRotationYMatrix3 : public RandomValueBase<T, Matrix3<T>> {
 public:
    RandomRotationYMatrix3(T angle_min, T angle_max)
        : RandomValueBase<T, Matrix3<T>>(angle_min, angle_max) {}

    auto next() -> bool override {
        this->m_Value = Matrix3<T>::RotationY(this->m_Dist(this->m_Gen));
        return true;
    }
};

template <typename T>
class RandomRotationZMatrix3 : public RandomValueBase<T, Matrix3<T>> {
 public:
    RandomRotationZMatrix3(T angle_min, T angle_max)
        : RandomValueBase<T, Matrix3<T>>(angle_min, angle_max) {}

    auto next() -> bool override {
        this->m_Value = Matrix3<T>::RotationZ(this->m_Dist(this->m_Gen));
        return true;
    }
};

//--------------------//
// Generator wrappers //
//--------------------//

template <typename T>
auto random_mat3(T val_range_min = static_cast<T>(-10.0),
                 T val_range_max = static_cast<T>(10.0))
    -> Catch::Generators::GeneratorWrapper<Matrix3<T>> {
    return Catch::Generators::GeneratorWrapper<Matrix3<T>>(
        Catch::Generators::pf::make_unique<RandomMatrix3<T>>(val_range_min,
                                                             val_range_max));
}

template <typename T>
auto random_rotx_mat3(T angle_min = static_cast<T>(-::math::PI),
                      T angle_max = static_cast<T>(::math::PI))
    -> Catch::Generators::GeneratorWrapper<Matrix3<T>> {
    return Catch::Generators::GeneratorWrapper<Matrix3<T>>(
        Catch::Generators::pf::make_unique<RandomRotationXMatrix3<T>>(
            angle_min, angle_max));
}

template <typename T>
auto random_roty_mat3(T angle_min = static_cast<T>(-::math::PI),
                      T angle_max = static_cast<T>(::math::PI))
    -> Catch::Generators::GeneratorWrapper<Matrix3<T>> {
    return Catch::Generators::GeneratorWrapper<Matrix3<T>>(
        Catch::Generators::pf::make_unique<RandomRotationYMatrix3<T>>(
            angle_min, angle_max));
}

template <typename T>
auto random_rotz_mat3(T angle_min = static_cast<T>(-::math::PI),
                      T angle_max = static_cast<T>(::math::PI))
    -> Catch::Generators::GeneratorWrapper<Matrix3<T>> {
    return Catch::Generators::GeneratorWrapper<Matrix3<T>>(
        Catch::Generators::pf::make_unique<RandomRotationZMatrix3<T>>(
            angle_min, angle_max));
}

//****************************************************************************//
//                      Generators for Quaternion type                        //
//****************************************************************************//

//-------------------//
// Custom Generators //
//-------------------//

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
class RandomUnitQuaternion : public RandomValueBase<T, Quaternion<T>> {
 public:
    RandomUnitQuaternion() : RandomValueBase<T, Quaternion<T>>(-1.0, 1.0) {}

    auto next() -> bool override {
        this->m_Value = {this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen),
                         this->m_Dist(this->m_Gen), this->m_Dist(this->m_Gen)};
        this->m_Value.normalize();
        return true;
    }
};

//--------------------//
// Generator wrappers //
//--------------------//

template <typename T>
auto random_quaternion() -> Catch::Generators::GeneratorWrapper<Quaternion<T>> {
    return Catch::Generators::GeneratorWrapper<Quaternion<T>>(
        Catch::Generators::pf::make_unique<RandomQuaternion<T>>());
}

template <typename T>
auto random_unit_quaternion()
    -> Catch::Generators::GeneratorWrapper<Quaternion<T>> {
    return Catch::Generators::GeneratorWrapper<Quaternion<T>>(
        Catch::Generators::pf::make_unique<RandomUnitQuaternion<T>>());
}

//****************************************************************************//
//                     Generators for Euler angles type                       //
//****************************************************************************//

//-------------------//
// Custom Generators //
//-------------------//

template <typename T>
class RandomEuler : public RandomValueBase<T, Euler<T>> {
 public:
    RandomEuler()
        : RandomValueBase<T, Euler<T>>(static_cast<T>(-::math::PI),
                                       static_cast<T>(::math::PI)) {}

    auto next() -> bool override {
        this->m_Value.x = this->m_Dist(this->m_Gen);
        this->m_Value.y = this->m_Dist(this->m_Gen);
        this->m_Value.z = this->m_Dist(this->m_Gen);
        return true;
    }
};

//--------------------//
// Generator wrappers //
//--------------------//

template <typename T>
auto random_euler() -> Catch::Generators::GeneratorWrapper<Euler<T>> {
    return Catch::Generators::GeneratorWrapper<Euler<T>>(
        Catch::Generators::pf::make_unique<RandomEuler<T>>());
}

//****************************************************************************//
//                    Generators for Transform(Mat4) type                     //
//****************************************************************************//

//-------------------//
// Custom Generators //
//-------------------//

template <typename T>
class RandomTransformMat4 : public Catch::Generators::IGenerator<Matrix4<T>> {
 public:
    RandomTransformMat4()
        : m_DistPosition(static_cast<T>(-10.0), static_cast<T>(10.0)),
          m_DistRotation(static_cast<T>(-1.0), static_cast<T>(1.0)),
          m_Gen(std::random_device{}()) {}  // NOLINT

    auto get() const -> const Matrix4<T>& override { return m_Value; }

    auto next() -> bool override {
        m_Position.x() = m_DistPosition(m_Gen);
        m_Position.y() = m_DistPosition(m_Gen);
        m_Position.z() = m_DistPosition(m_Gen);

        m_Orientation.w() = m_DistRotation(m_Gen);
        m_Orientation.x() = m_DistRotation(m_Gen);
        m_Orientation.y() = m_DistRotation(m_Gen);
        m_Orientation.z() = m_DistRotation(m_Gen);
        m_Orientation.normalize();

        return true;
    }

 private:
    /// Distribution from which to generate random values for positions
    std::uniform_real_distribution<T> m_DistPosition;
    /// Distribution from which to generate random values for quaternions
    std::uniform_real_distribution<T> m_DistRotation;
    /// The method used to generate random numbers
    std::minstd_rand m_Gen;
    /// The random transform to be exposed
    Matrix4<T> m_Value;
    /// The position used to generate the transform
    Vector3<T> m_Position;
    /// The orientation used to generate the transform
    Quaternion<T> m_Orientation;
};

//--------------------//
// Generator wrappers //
//--------------------//

template <typename T>
auto random_transform_mat4()
    -> Catch::Generators::GeneratorWrapper<Matrix4<T>> {
    return Catch::Generators::GeneratorWrapper<Matrix4<T>>(
        Catch::Generators::pf::make_unique<RandomTransformMat4<T>>());
}

}  // namespace math
