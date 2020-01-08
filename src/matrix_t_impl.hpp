
#include <matrix_t.h>

namespace tinymath
{
    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN>::Matrix()
    {
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                m_buff[i + j * SizeN] = ( ( i == j ) ? 1.0 : 0.0 );
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN>::Matrix( const std::vector<Scalar_T>& elements )
    {
        if ( elements.size() != ( SizeN * SizeN ) )
            throw std::runtime_error( "tinymath::Matrix >>> elements list doesn't have same size as the matrix" );

        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                m_buff[i + j * SizeN] = elements[j + i * SizeN];
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN>::~Matrix()
    {
        // nothing to release manually
    }

    template< typename Scalar_T, size_t SizeN >
    void Matrix<Scalar_T, SizeN>::setIdentity()
    {
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                m_buff[i + j * SizeN] = ( ( i == j ) ? 1.0 : 0.0 );
    }

    template< typename Scalar_T, size_t SizeN >
    void Matrix<Scalar_T, SizeN>::setZero()
    {
        for ( size_t i = 0; i < ( SizeN * SizeN ); i++ )
            m_buff[i] = 0.0;
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN> Matrix<Scalar_T, SizeN>::transpose() const
    {
        auto _resmat = Matrix<Scalar_T,SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                _resmat.m_buff[i + j * SizeN] = m_buff[j + i * SizeN];

        return _resmat;
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN> Matrix<Scalar_T, SizeN>::inverse() const
    {
        throw std::runtime_error( std::string( "tinymath::Matrix::inverse() >>> method not implemented for this dimensions: (" ) + 
                                  std::to_string( SizeN ) +  "," + std::to_string( SizeN ) + ")" );
        return Matrix<Scalar_T,SizeN>();
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T Matrix<Scalar_T, SizeN>::operator() ( size_t row, size_t col ) const
    {
        assert( row < SizeN && col < SizeN );
        return m_buff[ row + col * SizeN ];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T& Matrix<Scalar_T, SizeN>::operator() ( size_t row, size_t col )
    {
        assert( row < SizeN && col < SizeN );
        return m_buff[ row + col * SizeN ];
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T, SizeN> Matrix<Scalar_T, SizeN>::row( size_t index ) const
    {
        assert( index < SizeN );
        auto _resvec = Vector<Scalar_T,SizeN>();
        for ( size_t j = 0; j < SizeN; j++ )
            _resvec[j] = m_buff[index + j * SizeN];
        return _resvec;
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T, SizeN> Matrix<Scalar_T, SizeN>::col( size_t index ) const
    {
        assert( index < SizeN );
        auto _resvec = Vector<Scalar_T,SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            _resvec[i] = m_buff[i + index * SizeN];
        return _resvec;
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN> Matrix<Scalar_T, SizeN>::operator+ ( const Matrix<Scalar_T, SizeN>& other ) const
    {
        auto _res = Matrix<Scalar_T, SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                _res.m_buff[i + j * SizeN] = m_buff[i + j * SizeN] + other.m_buff[i + j * SizeN];
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN> Matrix<Scalar_T, SizeN>::operator- ( const Matrix<Scalar_T, SizeN>& other ) const
    {
        auto _res = Matrix<Scalar_T, SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                _res.m_buff[i + j * SizeN] = m_buff[i + j * SizeN] - other.m_buff[i + j * SizeN];
        return _res;
    }


    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN> Matrix<Scalar_T, SizeN>::operator* ( const Matrix<Scalar_T, SizeN>& other ) const
    {
        auto _res = Matrix<Scalar_T, SizeN>( 0.0, 0.0, 0.0, 0.0 );
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                for ( size_t k = 0; k < SizeN; k++ )
                    _res.m_buff[i + j * SizeN] += m_buff[i + k * SizeN] * other.m_buff[k + j * SizeN];
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T, SizeN> Matrix<Scalar_T, SizeN>::operator* ( const Vector<Scalar_T, SizeN>& vec ) const
    {
        auto _res = Vector<Scalar_T, SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t k = 0; k < SizeN; k++ )
                _res.m_buff[i] += m_buff[i + k * SizeN] * vec(k); // @todo: friend?
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T Matrix<Scalar_T, SizeN>::_get( size_t row, size_t col ) const
    {
        assert( row < SizeN && col < SizeN );
        return m_buff[ row + col * SizeN ];
    }

    template< typename Scalar_T, size_t SizeN >
    void Matrix<Scalar_T, SizeN>::_set( size_t row, size_t col, Scalar_T val )
    {
        assert( row < SizeN && col < SizeN );
        m_buff[ row + col * SizeN ] = val;
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN> operator* ( const Matrix<Scalar_T, SizeN>& mat, Scalar_T val )
    {
        auto _res = Matrix<Scalar_T, SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                _res(i, j) = mat(i, j) * val;
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN> operator* ( Scalar_T val, const Matrix<Scalar_T, SizeN>& mat )
    {
        auto _res = Matrix<Scalar_T, SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                _res(i, j) = mat(i, j) * val;
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    std::string toString( const Matrix<Scalar_T, SizeN>& mat )
    {
        std::string _strrep = "[ ";
        for ( size_t i = 0; i < SizeN; i++ )
        {
            _strrep += ( i != 0 ) ? "  " : "";
            for ( size_t j = 0; j < SizeN; j++ )
                _strrep += std::to_string( mat( i, j ) ) + ( ( i == (SizeN - 1) && j == (SizeN - 1) ) ? "" : "\t" );

            if ( i != (SizeN - 1) )
                _strrep += "\n";
        }
        _strrep += " ]";

        return _strrep;
    }

    /**********************************************************************************************/
    /*                          Specializations for specific methods                              */
    /**********************************************************************************************/

    // inverse method for dimensions 2, 3 and 4 (float32)

    template<>
    Matrix<float, 2> Matrix<float, 2>::inverse() const
    {
        auto m00 = m_buff[0]; auto m01 = m_buff[2];
        auto m10 = m_buff[1]; auto m11 = m_buff[3];

        auto det = m00 * m11 - m10 * m01;
        return Matrix<float, 2>( { ((float)( m11 / det)), ((float)(-m01 / det)),
                                   ((float)(-m10 / det)), ((float)(m00 / det)) } );
    }

    template<>
    Matrix<float, 3> Matrix<float, 3>::inverse() const
    {
        Matrix<float, 3> _resmat;

        auto m00 = _get( 0, 0 ); auto m01 = _get( 0, 1 ); auto m02 = _get( 0, 2 );
        auto m10 = _get( 1, 0 ); auto m11 = _get( 1, 1 ); auto m12 = _get( 1, 2 );
        auto m20 = _get( 2, 0 ); auto m21 = _get( 2, 1 ); auto m22 = _get( 2, 2 );

        // calculate some intermediate values - cofactors
        auto _c00 = ( m11 * m22 - m21 * m12 );
        auto _c10 = -( m01 * m22 - m21 * m02 );
        auto _c20 = ( m01 * m12 - m11 * m02 );

        auto _c01 = -( m10 * m22 - m20 * m12 );
        auto _c11 = ( m00 * m22 - m20 * m02 );
        auto _c21 = -( m00 * m12 - m10 * m02 );

        auto _c02 = ( m10 * m21 - m20 * m11 );
        auto _c12 = -( m00 * m21 - m20 * m01 );
        auto _c22 = ( m00 * m11 - m10 * m01 );

        auto _det = m00 * _c00 + m10 * _c10 + m20 * _c20;
        auto _invdet = 1.0 / _det;

        // Generate the inverse in-place using the transpose of the cofactors matrix
        _resmat._set( 0, 0, _c00 * _invdet );
        _resmat._set( 0, 1, _c10 * _invdet );
        _resmat._set( 0, 2, _c20 * _invdet );

        _resmat._set( 1, 0, _c01 * _invdet );
        _resmat._set( 1, 1, _c11 * _invdet );
        _resmat._set( 1, 2, _c21 * _invdet );

        _resmat._set( 2, 0, _c02 * _invdet );
        _resmat._set( 2, 1, _c12 * _invdet );
        _resmat._set( 2, 2, _c22 * _invdet );

        return _resmat;
    }

    template<>
    Matrix<float, 4> Matrix<float, 4>::inverse() const
    {
        Matrix<float, 4> _resmat;

        auto m00 = _get( 0, 0 ); auto m01 = _get( 0, 1 );
        auto m10 = _get( 1, 0 ); auto m11 = _get( 1, 1 );
        auto m20 = _get( 2, 0 ); auto m21 = _get( 2, 1 );
        auto m30 = _get( 3, 0 ); auto m31 = _get( 3, 1 );

        auto m02 = _get( 0, 2 ); auto m03 = _get( 0, 3 );
        auto m12 = _get( 1, 2 ); auto m13 = _get( 1, 3 );
        auto m22 = _get( 2, 2 ); auto m23 = _get( 2, 3 );
        auto m32 = _get( 3, 2 ); auto m33 = _get( 3, 3 );

        // Calculate some intermediate values - "minors" of order 2
        auto _m2323 = m22 * m33 - m32 * m23;
        auto _m1323 = m12 * m33 - m32 * m13;
        auto _m0323 = m02 * m33 - m32 * m03;
        auto _m1223 = m12 * m23 - m22 * m13;
        auto _m0223 = m02 * m23 - m22 * m03;
        auto _m0123 = m02 * m13 - m12 * m03;

        auto _m1201 = m10 * m21 - m20 * m11;
        auto _m1301 = m10 * m31 - m30 * m11;
        auto _m2301 = m20 * m31 - m30 * m21;
        auto _m0201 = m00 * m21 - m20 * m01;
        auto _m0301 = m00 * m31 - m30 * m01;
        auto _m0101 = m00 * m11 - m10 * m01;

        auto _det = m00 * ( m11 * _m2323 - m21 * _m1323 + m31 * _m1223 ) -
                    m10 * ( m01 * _m2323 - m21 * _m0323 + m31 * _m0223 ) +
                    m20 * ( m01 * _m1323 - m11 * _m0323 + m31 * _m0123 ) - 
                    m30 * ( m01 * _m1223 - m11 * _m0223 + m21 * _m0123 );

        auto _invdet = 1.0 / _det;

        // Generate transpose of "cofactors" matrix ( also divide by determinant ) in place
        _resmat._set( 0, 0, ( m11 * _m2323 - m21 * _m1323 + m31 * _m1223 ) *  _invdet );
        _resmat._set( 0, 1, ( m01 * _m2323 - m21 * _m0323 + m31 * _m0223 ) * -_invdet );
        _resmat._set( 0, 2, ( m01 * _m1323 - m11 * _m0323 + m31 * _m0123 ) *  _invdet );
        _resmat._set( 0, 3, ( m01 * _m1223 - m11 * _m0223 + m21 * _m0123 ) * -_invdet );

        _resmat._set( 1, 0, ( m10 * _m2323 - m20 * _m1323 + m30 * _m1223 ) * -_invdet );
        _resmat._set( 1, 1, ( m00 * _m2323 - m20 * _m0323 + m30 * _m0223 ) *  _invdet );
        _resmat._set( 1, 2, ( m00 * _m1323 - m10 * _m0323 + m30 * _m0123 ) * -_invdet );
        _resmat._set( 1, 3, ( m00 * _m1223 - m10 * _m0223 + m20 * _m0123 ) *  _invdet );

        _resmat._set( 2, 0, ( m33 * _m1201 - m23 * _m1301 + m13 * _m2301 ) *  _invdet );
        _resmat._set( 2, 1, ( m33 * _m0201 - m23 * _m0301 + m03 * _m2301 ) * -_invdet );
        _resmat._set( 2, 2, ( m33 * _m0101 - m13 * _m0301 + m03 * _m1301 ) *  _invdet );
        _resmat._set( 2, 3, ( m23 * _m0101 - m13 * _m0201 + m03 * _m1201 ) * -_invdet );

        _resmat._set( 3, 0, ( m32 * _m1201 - m22 * _m1301 + m12 * _m2301 ) * -_invdet );
        _resmat._set( 3, 1, ( m32 * _m0201 - m22 * _m0301 + m02 * _m2301 ) *  _invdet );
        _resmat._set( 3, 2, ( m32 * _m0101 - m12 * _m0301 + m02 * _m1301 ) * -_invdet );
        _resmat._set( 3, 3, ( m22 * _m0101 - m12 * _m0201 + m02 * _m1201 ) *  _invdet );

        return _resmat;
    }

    // inverse method for dimensions 2, 3 and 4 (float64)

    template<>
    Matrix<double, 2> Matrix<double, 2>::inverse() const
    {
        auto m00 = m_buff[0]; auto m01 = m_buff[2];
        auto m10 = m_buff[1]; auto m11 = m_buff[3];

        auto det = m00 * m11 - m10 * m01;
        return Matrix<double, 2>( { ((double)( m11 / det)),  ((double)(-m01 / det)),
                                    ((double)(-m10 / det)),  ((double)( m00 / det)) } );
    }

    template<>
    Matrix<double, 3> Matrix<double, 3>::inverse() const
    {
        Matrix<double, 3> _resmat;

        auto m00 = _get( 0, 0 ); auto m01 = _get( 0, 1 ); auto m02 = _get( 0, 2 );
        auto m10 = _get( 1, 0 ); auto m11 = _get( 1, 1 ); auto m12 = _get( 1, 2 );
        auto m20 = _get( 2, 0 ); auto m21 = _get( 2, 1 ); auto m22 = _get( 2, 2 );

        // calculate some intermediate values - cofactors
        auto _c00 = ( m11 * m22 - m21 * m12 );
        auto _c10 = -( m01 * m22 - m21 * m02 );
        auto _c20 = ( m01 * m12 - m11 * m02 );

        auto _c01 = -( m10 * m22 - m20 * m12 );
        auto _c11 = ( m00 * m22 - m20 * m02 );
        auto _c21 = -( m00 * m12 - m10 * m02 );

        auto _c02 = ( m10 * m21 - m20 * m11 );
        auto _c12 = -( m00 * m21 - m20 * m01 );
        auto _c22 = ( m00 * m11 - m10 * m01 );

        auto _det = m00 * _c00 + m10 * _c10 + m20 * _c20;
        auto _invdet = 1.0 / _det;

        // Generate the inverse in-place using the transpose of the cofactors matrix
        _resmat._set( 0, 0, _c00 * _invdet );
        _resmat._set( 0, 1, _c10 * _invdet );
        _resmat._set( 0, 2, _c20 * _invdet );

        _resmat._set( 1, 0, _c01 * _invdet );
        _resmat._set( 1, 1, _c11 * _invdet );
        _resmat._set( 1, 2, _c21 * _invdet );

        _resmat._set( 2, 0, _c02 * _invdet );
        _resmat._set( 2, 1, _c12 * _invdet );
        _resmat._set( 2, 2, _c22 * _invdet );

        return _resmat;
    }

    template<>
    Matrix<double, 4> Matrix<double, 4>::inverse() const
    {
        Matrix<double, 4> _resmat;

        auto m00 = _get( 0, 0 ); auto m01 = _get( 0, 1 );
        auto m10 = _get( 1, 0 ); auto m11 = _get( 1, 1 );
        auto m20 = _get( 2, 0 ); auto m21 = _get( 2, 1 );
        auto m30 = _get( 3, 0 ); auto m31 = _get( 3, 1 );

        auto m02 = _get( 0, 2 ); auto m03 = _get( 0, 3 );
        auto m12 = _get( 1, 2 ); auto m13 = _get( 1, 3 );
        auto m22 = _get( 2, 2 ); auto m23 = _get( 2, 3 );
        auto m32 = _get( 3, 2 ); auto m33 = _get( 3, 3 );

        // Calculate some intermediate values - "minors" of order 2
        auto _m2323 = m22 * m33 - m32 * m23;
        auto _m1323 = m12 * m33 - m32 * m13;
        auto _m0323 = m02 * m33 - m32 * m03;
        auto _m1223 = m12 * m23 - m22 * m13;
        auto _m0223 = m02 * m23 - m22 * m03;
        auto _m0123 = m02 * m13 - m12 * m03;

        auto _m1201 = m10 * m21 - m20 * m11;
        auto _m1301 = m10 * m31 - m30 * m11;
        auto _m2301 = m20 * m31 - m30 * m21;
        auto _m0201 = m00 * m21 - m20 * m01;
        auto _m0301 = m00 * m31 - m30 * m01;
        auto _m0101 = m00 * m11 - m10 * m01;        

        auto _det = m00 * ( m11 * _m2323 - m21 * _m1323 + m31 * _m1223 ) -
                    m10 * ( m01 * _m2323 - m21 * _m0323 + m31 * _m0223 ) +
                    m20 * ( m01 * _m1323 - m11 * _m0323 + m31 * _m0123 ) - 
                    m30 * ( m01 * _m1223 - m11 * _m0223 + m21 * _m0123 );

        auto _invdet = 1.0 / _det;

        // Generate transpose of "cofactors" matrix ( also divide by determinant ) in place
        _resmat._set( 0, 0, ( m11 * _m2323 - m21 * _m1323 + m31 * _m1223 ) *  _invdet );
        _resmat._set( 0, 1, ( m01 * _m2323 - m21 * _m0323 + m31 * _m0223 ) * -_invdet );
        _resmat._set( 0, 2, ( m01 * _m1323 - m11 * _m0323 + m31 * _m0123 ) *  _invdet );
        _resmat._set( 0, 3, ( m01 * _m1223 - m11 * _m0223 + m21 * _m0123 ) * -_invdet );

        _resmat._set( 1, 0, ( m10 * _m2323 - m20 * _m1323 + m30 * _m1223 ) * -_invdet );
        _resmat._set( 1, 1, ( m00 * _m2323 - m20 * _m0323 + m30 * _m0223 ) *  _invdet );
        _resmat._set( 1, 2, ( m00 * _m1323 - m10 * _m0323 + m30 * _m0123 ) * -_invdet );
        _resmat._set( 1, 3, ( m00 * _m1223 - m10 * _m0223 + m20 * _m0123 ) *  _invdet );

        _resmat._set( 2, 0, ( m33 * _m1201 - m23 * _m1301 + m13 * _m2301 ) *  _invdet );
        _resmat._set( 2, 1, ( m33 * _m0201 - m23 * _m0301 + m03 * _m2301 ) * -_invdet );
        _resmat._set( 2, 2, ( m33 * _m0101 - m13 * _m0301 + m03 * _m1301 ) *  _invdet );
        _resmat._set( 2, 3, ( m23 * _m0101 - m13 * _m0201 + m03 * _m1201 ) * -_invdet );

        _resmat._set( 3, 0, ( m32 * _m1201 - m22 * _m1301 + m12 * _m2301 ) * -_invdet );
        _resmat._set( 3, 1, ( m32 * _m0201 - m22 * _m0301 + m02 * _m2301 ) *  _invdet );
        _resmat._set( 3, 2, ( m32 * _m0101 - m12 * _m0301 + m02 * _m1301 ) * -_invdet );
        _resmat._set( 3, 3, ( m22 * _m0101 - m12 * _m0201 + m02 * _m1201 ) *  _invdet );

        return _resmat;
    }
}