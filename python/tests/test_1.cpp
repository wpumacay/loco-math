
#include <py_common.h>
#include <py_vectors.h>

namespace py = pybind11;

// consumer of the Vector2 class in c++
class Particle
{

public :

    Particle( const tinymath::Vector2& position )
        : m_position( position ) {}

    ~Particle() {}

    void setPosition( const tinymath::Vector2& pos ) { m_position = pos; }
    tinymath::Vector2 getPosition() const { return m_position; }

private :

    tinymath::Vector2 m_position;

};

PYBIND11_MODULE( test_1, m )
{
    py::class_< Particle >( m, "Particle" )
        .def( py::init< tinymath::Vector2 >() )
        .def( py::init( []( py::array_t< tinymath::tfloat >& position )
            {
                auto bufferInfo = position.request();
                if ( bufferInfo.size != 2 )
                    throw std::runtime_error( "tinymath::Particle >>> incompatible array size, (expected 2 floats) for position" );

                auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                return new Particle( { bufferData[0], bufferData[1] } );
            } ) )
        .def_property( "position", 
            []( const Particle& self ) -> py::array_t<tinymath::tfloat>
                {
                    auto position = self.getPosition();
                    auto npposition = py::array_t<tinymath::tfloat>( 2 );
                    auto bufferInfo = npposition.request();
                    auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                    bufferData[0] = position.x();
                    bufferData[1] = position.y();

                    return npposition;
                }, 
            []( Particle& self, py::array_t<tinymath::tfloat>& position )
                {
                    auto bufferInfo = position.request();
                    if ( bufferInfo.size != 2 )
                        throw std::runtime_error( "tinymath::Particle::setPosition() >>> incompatible array size, (expected 2 floats) for position" );

                    auto bufferData = (tinymath::tfloat*) bufferInfo.ptr;
                    self.setPosition( { bufferData[0], bufferData[1] } );
                } )
        .def( "__repr__", []( const Particle& self )
            {
                return std::string( "particle{\n\r" ) +
                       "\tposition(" + tinymath::toString( self.getPosition() ) + ")\n\r" +
                       "}";
            } );
}