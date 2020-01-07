
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