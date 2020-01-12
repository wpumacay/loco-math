
#include <bindings_transforms.h>

namespace tinymath
{

    template< typename Scalar_T >
    void bindings_transforms( py::module& m )
    {
        m.def( "quaternion", &tinymath::quaternion<Scalar_T> );
        m.def( "euler", &tinymath::euler<Scalar_T> );
        m.def( "axisAngle", &tinymath::axisAngle<Scalar_T> );
        m.def( "rotation", static_cast< Matrix<Scalar_T,3> (*)( const Vector<Scalar_T,3>& ) >( &tinymath::rotation<Scalar_T> ) );
        m.def( "rotation", static_cast< Matrix<Scalar_T,3> (*)( const Vector<Scalar_T,4>& ) >( &tinymath::rotation<Scalar_T> ) );
        m.def( "rotation", static_cast< Matrix<Scalar_T,3> (*)( const Vector<Scalar_T,3>&, tfloat ) >( &tinymath::rotation<Scalar_T> ) );
    }

}