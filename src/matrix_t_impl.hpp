
#include <matrix_t.h>

// @todo: check matrix traversal, as a column-major traversal might give better 
//        performance than a row-major traversal

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
    Matrix<Scalar_T, SizeN>::Matrix( const Matrix<Scalar_T,SizeN+1>& mat )
    {
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                m_buff[i + j * SizeN] = mat(i,j);
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN>::Matrix( const Matrix<Scalar_T,SizeN-1>& mat )
        : Matrix()
    {
        // set upper-left section
        set( mat );
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN>::Matrix( const Matrix<Scalar_T,SizeN-1>& mat, const Vector<Scalar_T,SizeN-1>& vec )
        : Matrix()
    {
        // set upper-left section
        set( mat );
        // set last column first n-1 elements
        set( vec, SizeN - 1 );
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
    void Matrix<Scalar_T,SizeN>::transpose_()
    {
        for ( size_t i = 0; i < SizeN - 1; i++ )
        {
            for ( size_t j = i + 1; j < SizeN; j++ )
            {
                Scalar_T _tmp = m_buff[i + j * SizeN];
                m_buff[i + j * SizeN] = m_buff[j + i * SizeN];
                m_buff[j + i * SizeN] = _tmp;
            }
        }
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
    Vector<Scalar_T,SizeN> Matrix<Scalar_T,SizeN>::operator() ( size_t index )
    {
        assert( index < SizeN );
        return col( index );
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
    void Matrix<Scalar_T,SizeN>::set( const Vector<Scalar_T,SizeN>& vec, size_t index )
    {
        assert( index < SizeN );
        for ( size_t i = 0; i < SizeN; i++ )
            _set( i, index, vec( i ) );
    }

    template< typename Scalar_T, size_t SizeN >
    void Matrix<Scalar_T,SizeN>::set( const Vector<Scalar_T,SizeN-1>& vec, size_t index )
    {
        assert( index < SizeN );
        for ( size_t i = 0; i < (SizeN-1); i++ )
            _set( i, index, vec( i ) );
    }

    template< typename Scalar_T, size_t SizeN >
    void Matrix<Scalar_T,SizeN>::set( const Matrix<Scalar_T,SizeN-1>& mat )
    {
        for ( size_t i = 0; i < (SizeN-1); i++ )
            for ( size_t j = 0; j < (SizeN-1); j++ )
                _set( i, j, mat(i, j) );
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
        auto _res = Matrix<Scalar_T, SizeN>();
        _res.setZero();
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
                _res(i) += m_buff[i + k * SizeN] * vec(k); // @todo: friend?
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
    Matrix<Scalar_T, SizeN> operator* ( const Matrix<Scalar_T, SizeN>& mat, tfloat val )
    {
        auto _res = Matrix<Scalar_T, SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            for ( size_t j = 0; j < SizeN; j++ )
                _res(i, j) = mat(i, j) * val;
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    Matrix<Scalar_T, SizeN> operator* ( tfloat val, const Matrix<Scalar_T, SizeN>& mat )
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

    template< typename Scalar_T, size_t SizeN >
    bool allclose( const Matrix<Scalar_T,SizeN >& mat1, const Matrix<Scalar_T,SizeN>& mat2, Scalar_T tolerance )
    {
        for ( size_t i = 0; i < SizeN; i++ )
        {
            for ( size_t j = 0; j < SizeN; j++ )
            {
                if ( std::abs( mat1( i, j ) - mat2( i, j ) ) >= tolerance )
                    return false;
            }
        }

        return true;
    }

    template< typename Scalar_T >
    Matrix<Scalar_T, 2 > inverse( const Matrix<Scalar_T, 2>& mat )
    {
        auto m00 = mat( 0, 0 ); auto m01 = mat( 0, 1 );
        auto m10 = mat( 1, 0 ); auto m11 = mat( 1, 1 );

        auto det = m00 * m11 - m10 * m01;
        return Matrix<Scalar_T, 2>( { m11 / det, -m01 / det,
                                      -m10 / det, m00 / det } );
    }

    template< typename Scalar_T >
    Matrix<Scalar_T, 3 > inverse( const Matrix<Scalar_T, 3>& mat )
    {
        Matrix<Scalar_T, 3> _resmat;

        auto m00 = mat( 0, 0 ); auto m01 = mat( 0, 1 ); auto m02 = mat( 0, 2 );
        auto m10 = mat( 1, 0 ); auto m11 = mat( 1, 1 ); auto m12 = mat( 1, 2 );
        auto m20 = mat( 2, 0 ); auto m21 = mat( 2, 1 ); auto m22 = mat( 2, 2 );

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
        auto _invdet = 1 / _det;

        // Generate the inverse in-place using the transpose of the cofactors matrix
        _resmat( 0, 0 ) =_c00 * _invdet;
        _resmat( 0, 1 ) =_c10 * _invdet;
        _resmat( 0, 2 ) =_c20 * _invdet;

        _resmat( 1, 0 ) = _c01 * _invdet;
        _resmat( 1, 1 ) = _c11 * _invdet;
        _resmat( 1, 2 ) = _c21 * _invdet;

        _resmat( 2, 0 ) = _c02 * _invdet;
        _resmat( 2, 1 ) = _c12 * _invdet;
        _resmat( 2, 2 ) = _c22 * _invdet;

        return _resmat;
    }

    template< typename Scalar_T >
    Matrix<Scalar_T, 4 > inverse( const Matrix<Scalar_T, 4>& mat )
    {
        Matrix<Scalar_T, 4> _resmat;

        auto m00 = mat( 0, 0 ); auto m01 = mat( 0, 1 );
        auto m10 = mat( 1, 0 ); auto m11 = mat( 1, 1 );
        auto m20 = mat( 2, 0 ); auto m21 = mat( 2, 1 );
        auto m30 = mat( 3, 0 ); auto m31 = mat( 3, 1 );

        auto m02 = mat( 0, 2 ); auto m03 = mat( 0, 3 );
        auto m12 = mat( 1, 2 ); auto m13 = mat( 1, 3 );
        auto m22 = mat( 2, 2 ); auto m23 = mat( 2, 3 );
        auto m32 = mat( 3, 2 ); auto m33 = mat( 3, 3 );

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

        auto _invdet = 1 / _det;

        // Generate transpose of "cofactors" matrix ( also divide by determinant ) in place
        _resmat( 0, 0 ) = ( m11 * _m2323 - m21 * _m1323 + m31 * _m1223 ) *  _invdet;
        _resmat( 0, 1 ) = ( m01 * _m2323 - m21 * _m0323 + m31 * _m0223 ) * -_invdet;
        _resmat( 0, 2 ) = ( m01 * _m1323 - m11 * _m0323 + m31 * _m0123 ) *  _invdet;
        _resmat( 0, 3 ) = ( m01 * _m1223 - m11 * _m0223 + m21 * _m0123 ) * -_invdet;

        _resmat( 1, 0 ) = ( m10 * _m2323 - m20 * _m1323 + m30 * _m1223 ) * -_invdet;
        _resmat( 1, 1 ) = ( m00 * _m2323 - m20 * _m0323 + m30 * _m0223 ) *  _invdet;
        _resmat( 1, 2 ) = ( m00 * _m1323 - m10 * _m0323 + m30 * _m0123 ) * -_invdet;
        _resmat( 1, 3 ) = ( m00 * _m1223 - m10 * _m0223 + m20 * _m0123 ) *  _invdet;

        _resmat( 2, 0 ) = ( m33 * _m1201 - m23 * _m1301 + m13 * _m2301 ) *  _invdet;
        _resmat( 2, 1 ) = ( m33 * _m0201 - m23 * _m0301 + m03 * _m2301 ) * -_invdet;
        _resmat( 2, 2 ) = ( m33 * _m0101 - m13 * _m0301 + m03 * _m1301 ) *  _invdet;
        _resmat( 2, 3 ) = ( m23 * _m0101 - m13 * _m0201 + m03 * _m1201 ) * -_invdet;

        _resmat( 3, 0 ) = ( m32 * _m1201 - m22 * _m1301 + m12 * _m2301 ) * -_invdet;
        _resmat( 3, 1 ) = ( m32 * _m0201 - m22 * _m0301 + m02 * _m2301 ) *  _invdet;
        _resmat( 3, 2 ) = ( m32 * _m0101 - m12 * _m0301 + m02 * _m1301 ) * -_invdet;
        _resmat( 3, 3 ) = ( m22 * _m0101 - m12 * _m0201 + m02 * _m1201 ) *  _invdet;

        return _resmat;
    }

}