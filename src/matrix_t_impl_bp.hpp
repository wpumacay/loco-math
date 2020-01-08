
#include <matrix_t.h>

namespace tinymath
{
    template< typename Scalar_T >
    Matrix2<Scalar_T>::Matrix2()
    {
        m_buff[0] = 1.0; m_buff[2] = 0.0;
        m_buff[1] = 0.0; m_buff[3] = 1.0;
    }

    template< typename Scalar_T >
    Matrix2<Scalar_T>::Matrix2( Scalar_T m00, Scalar_T m01,
                                Scalar_T m10, Scalar_T m11 )
    {
        m_buff[0] = m00; m_buff[2] = m01;
        m_buff[1] = m10; m_buff[3] = m11;
    }

    template< typename Scalar_T >
    Matrix2<Scalar_T>::Matrix2( const Vector2<Scalar_T>& col1, const Vector2<Scalar_T>& col2 )
    {
        m_buff[0] = col1.x(); m_buff[2] = col2.x();
        m_buff[1] = col1.y(); m_buff[3] = col2.y();
    }

    template< typename Scalar_T >
    Matrix2<Scalar_T>::~Matrix2()
    {
        // nothing to release manually
    }

    template< typename Scalar_T >
    void Matrix2<Scalar_T>::setIdentity()
    {
        m_buff[0] = 1.0; m_buff[2] = 0.0;
        m_buff[1] = 0.0; m_buff[3] = 1.0;
    }

    template< typename Scalar_T >
    Matrix2<Scalar_T> Matrix2<Scalar_T>::transpose() const
    {
        return { m_buff[0], m_buff[1], 
                 m_buff[2], m_buff[3] };
    }

    template< typename Scalar_T >
    Matrix2<Scalar_T> Matrix2<Scalar_T>::inverse() const
    {
        auto m00 = m_buff[0]; auto m01 = m_buff[2];
        auto m10 = m_buff[1]; auto m11 = m_buff[3];

        auto det = m00 * m11 - m10 * m01;
        return { m11 / det, -m01 / det,
                 -m10 / det, m00 / det };
    }

    template< typename Scalar_T >
    Scalar_T Matrix2<Scalar_T>::operator() ( size_t row, size_t col ) const
    {
        assert( row < 2 && col < 2 );
        return m_buff[ row + col * 2 ];
    }

    template< typename Scalar_T >
    Scalar_T& Matrix2<Scalar_T>::operator() ( size_t row, size_t col )
    {
        assert( row < 2 && col < 2 );
        return m_buff[ row + col * 2 ];
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> Matrix2<Scalar_T>::row( size_t index ) const
    {
        assert( index < 2 );
        return { m_buff[index], m_buff[index + 2] };
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> Matrix2<Scalar_T>::col( size_t index ) const
    {
        assert( index < 2 );
        return { m_buff[index * 2], m_buff[1 + index * 2] };
    }

    template< typename Scalar_T >
    Matrix2<Scalar_T> Matrix2<Scalar_T>::operator+ ( const Matrix2<Scalar_T>& other ) const
    {
        auto _res = Matrix2<Scalar_T>();
        for ( size_t i = 0; i < 2; i++ )
            for ( size_t j = 0; j < 2; j++ )
                _res.m_buff[i + j * 2] = m_buff[i + j * 2] + other.m_buff[i + j * 2];
        return _res;
    }

    template< typename Scalar_T >
    Matrix2<Scalar_T> Matrix2<Scalar_T>::operator- ( const Matrix2<Scalar_T>& other ) const
    {
        auto _res = Matrix2<Scalar_T>();
        for ( size_t i = 0; i < 2; i++ )
            for ( size_t j = 0; j < 2; j++ )
                _res.m_buff[i + j * 2] = m_buff[i + j * 2] - other.m_buff[i + j * 2];
        return _res;
    }


    template< typename Scalar_T >
    Matrix2<Scalar_T> Matrix2<Scalar_T>::operator* ( const Matrix2<Scalar_T>& other ) const
    {
        auto _res = Matrix2<Scalar_T>( 0.0, 0.0, 0.0, 0.0 );
        for ( size_t i = 0; i < 2; i++ )
            for ( size_t j = 0; j < 2; j++ )
                for ( size_t k = 0; k < 2; k++ )
                    _res.m_buff[i + j * 2] += m_buff[i + k * 2] * other.m_buff[k + j * 2];
        return _res;
    }

    template< typename Scalar_T >
    Vector2<Scalar_T> Matrix2<Scalar_T>::operator* ( const Vector2<Scalar_T>& vec ) const
    {
        auto _res = Vector2<Scalar_T>();
        for ( size_t i = 0; i < 2; i++ )
            for ( size_t k = 0; k < 2; k++ )
                _res.m_buff[i] += m_buff[i + k * 2] * vec(k); // @todo: friend?
        return _res;
    }

    template< typename Scalar_T >
    Matrix2<Scalar_T> operator* ( const Matrix2<Scalar_T>& mat, Scalar_T val )
    {
        auto _res = Matrix2<Scalar_T>();
        for ( size_t i = 0; i < 2; i++ )
            for ( size_t j = 0; j < 2; j++ )
                _res(i, j) = mat(i, j) * val;
        return _res;
    }

    template< typename Scalar_T >
    Matrix2<Scalar_T> operator* ( Scalar_T val, const Matrix2<Scalar_T>& mat )
    {
        auto _res = Matrix2<Scalar_T>();
        for ( size_t i = 0; i < 2; i++ )
            for ( size_t j = 0; j < 2; j++ )
                _res(i, j) = mat(i, j) * val;
        return _res;
    }

    template< typename Scalar_T >
    std::string toString( const Matrix2<Scalar_T>& mat )
    {
        std::string _strrep = "[ ";
        for ( size_t i = 0; i < 2; i++ )
        {
            _strrep += ( i != 0 ) ? "  " : "";
            for ( size_t j = 0; j < 2; j++ )
                _strrep += std::to_string( mat( i, j ) ) + ( ( i == 1 && j == 1 ) ? "" : "\t" );

            if ( i != 1 )
                _strrep += "\n";
        }
        _strrep += " ]";

        return _strrep;
    }
}