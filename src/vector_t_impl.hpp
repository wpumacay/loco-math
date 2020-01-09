
#include <vector_t.h>

namespace tinymath
{

    //////////////////////////////////////////////////////////////////////////
    //                              Vector                                  //
    //////////////////////////////////////////////////////////////////////////

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN>::Vector()
    {
        for ( size_t i = 0; i < SizeN; i++ )
            m_buff[i] = 0.0;
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN>::Vector( Scalar_T val )
    {
        for ( size_t i = 0; i < SizeN; i++ )
            m_buff[i] = val;
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN>::Vector( std::initializer_list<Scalar_T> values )
    {
        assert( values.size() == SizeN );
        size_t i = 0;
        for ( auto val : values )
        {
            m_buff[i] = val;
            i++;
        }
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN>::Vector( const std::vector<Scalar_T>& values )
    {
        assert( values.size() == SizeN );
        for ( size_t i = 0; i < SizeN; i++ )
            m_buff[i] = values[i];
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN>::~Vector()
    {
        // nothing to release manually
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T Vector<Scalar_T,SizeN>::length() const
    {
        Scalar_T len = 0.0;
        for ( size_t i = 0; i < SizeN; i++ )
            len += m_buff[i] * m_buff[i];
        return std::sqrt( len );
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T Vector<Scalar_T,SizeN>::dot( const Vector<Scalar_T,SizeN>& other ) const
    {
        Scalar_T _sum = 0.0;
        for ( size_t i = 0; i < SizeN; i++ )
            _sum += m_buff[i] * other.m_buff[i];
        return _sum;
    }

    template< typename Scalar_T, size_t SizeN >
    void Vector<Scalar_T,SizeN>::normalize()
    {
        auto len = length();
        for ( size_t i = 0; i < SizeN; i++ )
            m_buff[i] /= len;
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> Vector<Scalar_T,SizeN>::normalized() const
    {
        auto _res = Vector<Scalar_T,SizeN>();
        auto len = length();
        for ( size_t i = 0; i < SizeN; i++ )
            _res.m_buff[i] = m_buff[i] / len;
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    void Vector<Scalar_T,SizeN>::scale( Scalar_T val )
    {
        for ( size_t i = 0; i < SizeN; i++ )
            m_buff[i] *= val;
    }

    template< typename Scalar_T, size_t SizeN >
    void Vector<Scalar_T,SizeN>::scale( const Vector<Scalar_T,SizeN>& other )
    {
        for ( size_t i = 0; i < SizeN; i++ )
            m_buff[i] *= other.m_buff[i];
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> Vector<Scalar_T,SizeN>::scaled( Scalar_T val ) const
    {
        auto _res = Vector<Scalar_T,SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            _res.m_buff[i] = m_buff[i] * val;
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> Vector<Scalar_T,SizeN>::scaled( const Vector<Scalar_T,SizeN>& other ) const
    {
        auto _res = Vector<Scalar_T,SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            _res.m_buff[i] = m_buff[i] * other.m_buff[i];
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T Vector<Scalar_T,SizeN>::x() const
    {
        throw std::runtime_error( "tinymath::Vector::x() >>> x-component getter not supported" );
        return m_buff[0];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T Vector<Scalar_T,SizeN>::y() const
    {
        throw std::runtime_error( "tinymath::Vector::y() >>> y-component getter not supported" );
        return m_buff[1];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T Vector<Scalar_T,SizeN>::z() const
    {
        throw std::runtime_error( "tinymath::Vector::z() >>> z-component getter not supported" );
        return m_buff[2];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T Vector<Scalar_T,SizeN>::w() const
    {
        throw std::runtime_error( "tinymath::Vector::w() >>> w-component getter not supported" );
        return m_buff[3];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T& Vector<Scalar_T,SizeN>::x()
    {
        throw std::runtime_error( "tinymath::Vector::x() >>> x-component getter not supported" );
        return m_buff[0];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T& Vector<Scalar_T,SizeN>::y()
    {
        throw std::runtime_error( "tinymath::Vector::y() >>> y-component getter not supported" );
        return m_buff[1];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T& Vector<Scalar_T,SizeN>::z()
    {
        throw std::runtime_error( "tinymath::Vector::z() >>> z-component getter not supported" );
        return m_buff[2];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T& Vector<Scalar_T,SizeN>::w()
    {
        throw std::runtime_error( "tinymath::Vector::w() >>> w-component getter not supported" );
        return m_buff[3];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T Vector<Scalar_T,SizeN>::operator[] ( size_t indx ) const
    {
        assert( indx < SizeN );

        return m_buff[indx];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T& Vector<Scalar_T,SizeN>::operator[] ( size_t indx )
    {
        assert( indx < SizeN );

        return m_buff[indx];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T Vector<Scalar_T,SizeN>::operator() ( size_t indx ) const
    {
        assert( indx < SizeN );

        return m_buff[indx];
    }

    template< typename Scalar_T, size_t SizeN >
    Scalar_T& Vector<Scalar_T,SizeN>::operator() ( size_t indx )
    {
        assert( indx < SizeN );

        return m_buff[indx];
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> Vector<Scalar_T,SizeN>::operator+ ( const Vector<Scalar_T,SizeN>& other ) const
    {
        auto _res = Vector<Scalar_T,SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            _res.m_buff[i] = m_buff[i] + other.m_buff[i];
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> Vector<Scalar_T,SizeN>::operator- ( const Vector<Scalar_T,SizeN>& other ) const
    {
        auto _res = Vector<Scalar_T,SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            _res.m_buff[i] = m_buff[i] - other.m_buff[i];
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> Vector<Scalar_T,SizeN>::operator* ( const Vector<Scalar_T,SizeN>& other ) const
    {
        auto _res = Vector<Scalar_T,SizeN>();
        for ( size_t i = 0; i < SizeN; i++ )
            _res.m_buff[i] = m_buff[i] * other.m_buff[i];
        return _res;
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> operator* ( const Vector<Scalar_T,SizeN>& vec, Scalar_T val )
    {
        return vec.scaled( val );
    }

    template< typename Scalar_T, size_t SizeN >
    Vector<Scalar_T,SizeN> operator* ( Scalar_T val, const Vector<Scalar_T,SizeN>& vec )
    {
        return vec.scaled( val );
    }

    template< typename Scalar_T, size_t SizeN >
    std::string toString( const Vector<Scalar_T,SizeN>& vec )
    {
        std::string _strrep = "[ ";
        for ( size_t i = 0; i < SizeN; i++ )
            _strrep += std::to_string( vec[i] ) + ( ( i < (SizeN - 1) ) ? ", " : " ]" );
        return _strrep;
    }

    /**********************************************************************************************/
    /*                          Specializations for specific functions                            */
    /**********************************************************************************************/

    // Value-getters for x,y,z,w

    template<>
    float Vector<float, 2>::x() const { return m_buff[0]; }
    template<>
    float Vector<float, 2>::y() const { return m_buff[1]; }
    template<>
    float Vector<float, 3>::x() const { return m_buff[0]; }
    template<>
    float Vector<float, 3>::y() const { return m_buff[1]; }
    template<>
    float Vector<float, 3>::z() const { return m_buff[2]; }
    template<>
    float Vector<float, 4>::x() const { return m_buff[0]; }
    template<>
    float Vector<float, 4>::y() const { return m_buff[1]; }
    template<>
    float Vector<float, 4>::z() const { return m_buff[2]; }
    template<>
    float Vector<float, 4>::w() const { return m_buff[0]; }

    template<>
    double Vector<double, 2>::x() const { return m_buff[0]; }
    template<>
    double Vector<double, 2>::y() const { return m_buff[1]; }
    template<>
    double Vector<double, 3>::x() const { return m_buff[0]; }
    template<>
    double Vector<double, 3>::y() const { return m_buff[1]; }
    template<>
    double Vector<double, 3>::z() const { return m_buff[2]; }
    template<>
    double Vector<double, 4>::x() const { return m_buff[0]; }
    template<>
    double Vector<double, 4>::y() const { return m_buff[1]; }
    template<>
    double Vector<double, 4>::z() const { return m_buff[2]; }
    template<>
    double Vector<double, 4>::w() const { return m_buff[0]; }

    // Reference-getters for x,y,z,w

    template<>
    float& Vector<float, 2>::x() { return m_buff[0]; }
    template<>
    float& Vector<float, 2>::y() { return m_buff[1]; }
    template<>
    float& Vector<float, 3>::x() { return m_buff[0]; }
    template<>
    float& Vector<float, 3>::y() { return m_buff[1]; }
    template<>
    float& Vector<float, 3>::z() { return m_buff[2]; }
    template<>
    float& Vector<float, 4>::x() { return m_buff[0]; }
    template<>
    float& Vector<float, 4>::y() { return m_buff[1]; }
    template<>
    float& Vector<float, 4>::z() { return m_buff[2]; }
    template<>
    float& Vector<float, 4>::w() { return m_buff[0]; }

    template<>
    double& Vector<double, 2>::x() { return m_buff[0]; }
    template<>
    double& Vector<double, 2>::y() { return m_buff[1]; }
    template<>
    double& Vector<double, 3>::x() { return m_buff[0]; }
    template<>
    double& Vector<double, 3>::y() { return m_buff[1]; }
    template<>
    double& Vector<double, 3>::z() { return m_buff[2]; }
    template<>
    double& Vector<double, 4>::x() { return m_buff[0]; }
    template<>
    double& Vector<double, 4>::y() { return m_buff[1]; }
    template<>
    double& Vector<double, 4>::z() { return m_buff[2]; }
    template<>
    double& Vector<double, 4>::w() { return m_buff[0]; }
}