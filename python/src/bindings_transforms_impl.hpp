
#include <bindings_transforms.h>

namespace tinymath
{

    template< typename Scalar_T >
    void bindings_transforms( py::module& m )
    {
        m.def( "quaternion", static_cast< Vector<Scalar_T,4> (*)( const Matrix<Scalar_T,3>& ) >( &tinymath::quaternion<Scalar_T> ) );
        m.def( "quaternion", static_cast< Vector<Scalar_T,4> (*)( const Matrix<Scalar_T,4>& ) >( &tinymath::quaternion<Scalar_T> ) );
        m.def( "euler", static_cast< Vector<Scalar_T,3> (*)( const Matrix<Scalar_T,3>& ) >( &tinymath::euler<Scalar_T> ) );
        m.def( "euler", static_cast< Vector<Scalar_T,3> (*)( const Matrix<Scalar_T,4>& ) >( &tinymath::euler<Scalar_T> ) );
        m.def( "axisAngle", static_cast< std::pair< Vector<Scalar_T,3>, Scalar_T > (*)( const Matrix<Scalar_T,3>& ) >( &tinymath::axisAngle<Scalar_T> ) );
        m.def( "axisAngle", static_cast< std::pair< Vector<Scalar_T,3>, Scalar_T > (*)( const Matrix<Scalar_T,4>& ) >( &tinymath::axisAngle<Scalar_T> ) );
        m.def( "rotation", static_cast< Matrix<Scalar_T,3> (*)( const Vector<Scalar_T,3>& ) >( &tinymath::rotation<Scalar_T> ) );
        m.def( "rotation", static_cast< Matrix<Scalar_T,3> (*)( const Vector<Scalar_T,4>& ) >( &tinymath::rotation<Scalar_T> ) );
        m.def( "rotation", static_cast< Matrix<Scalar_T,3> (*)( const Vector<Scalar_T,3>&, tfloat ) >( &tinymath::rotation<Scalar_T> ) );
        m.def( "rotationXf", &tinymath::rotationX<float> );
        m.def( "rotationYf", &tinymath::rotationY<float> );
        m.def( "rotationZf", &tinymath::rotationZ<float> );
        m.def( "rotationXd", &tinymath::rotationX<double> );
        m.def( "rotationYd", &tinymath::rotationY<double> );
        m.def( "rotationZd", &tinymath::rotationZ<double> );
    }

}