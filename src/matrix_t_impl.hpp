
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
    Matrix<Scalar_T, SizeN >::Matrix( const Matrix<Scalar_T,SizeN-1>& mat, const Vector<Scalar_T,SizeN-1>& vec )
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

}