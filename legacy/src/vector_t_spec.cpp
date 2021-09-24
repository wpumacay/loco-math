
#include <vector_t.h>

namespace tinymath
{

    /**********************************************************************************************/
    /*                          Specializations for specific functions                            */
    /**********************************************************************************************/

    // Specializations for custom constructors (float32)
    template<>
    Vector<float, 2>::Vector( tfloat x, tfloat y ) 
    { m_buff[0] = x; m_buff[1] = y; }

    template<>
    Vector<float, 3>::Vector( tfloat x, tfloat y, tfloat z ) 
    { m_buff[0] = x; m_buff[1] = y; m_buff[2] = z; }

    template<>
    Vector<float, 4>::Vector( tfloat x, tfloat y, tfloat z, tfloat w ) 
    { m_buff[0] = x; m_buff[1] = y; m_buff[2] = z; m_buff[3] = w; }

    // Specializations for custom constructors (float64)
    template<>
    Vector<double, 2>::Vector( tfloat x, tfloat y ) 
    { m_buff[0] = x; m_buff[1] = y; }

    template<>
    Vector<double, 3>::Vector( tfloat x, tfloat y, tfloat z ) 
    { m_buff[0] = x; m_buff[1] = y; m_buff[2] = z; }

    template<>
    Vector<double, 4>::Vector( tfloat x, tfloat y, tfloat z, tfloat w ) 
    { m_buff[0] = x; m_buff[1] = y; m_buff[2] = z; m_buff[3] = w; }

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
    float Vector<float, 4>::w() const { return m_buff[3]; }

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
    double Vector<double, 4>::w() const { return m_buff[3]; }

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
    float& Vector<float, 4>::w() { return m_buff[3]; }

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
    double& Vector<double, 4>::w() { return m_buff[3]; }

}