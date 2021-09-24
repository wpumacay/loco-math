
#include <matrix_t.h>

namespace tinymath
{

    /**********************************************************************************************/
    /*                          Specializations for specific functions                            */
    /**********************************************************************************************/

    template<>
    Matrix<float,2> Matrix<float,2>::inverse() const
    { return tinymath::inverse( *this ); }

    template<>
    Matrix<float,3> Matrix<float,3>::inverse() const
    { return tinymath::inverse( *this ); }

    template<>
    Matrix<float,4> Matrix<float,4>::inverse() const
    { return tinymath::inverse( *this ); }

    template<>
    Matrix<double,2> Matrix<double,2>::inverse() const
    { return tinymath::inverse( *this ); }

    template<>
    Matrix<double,3> Matrix<double,3>::inverse() const
    { return tinymath::inverse( *this ); }

    template<>
    Matrix<double,4> Matrix<double,4>::inverse() const
    { return tinymath::inverse( *this ); }

}