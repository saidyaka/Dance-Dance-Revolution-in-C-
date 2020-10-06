#include "arrow.hxx"
#include <ge211.hxx>
#include <utility>

Arrow::Arrow()
        : velocity_ ( { 0, 0 } )
        , color_ ( "white" )
        , dir_ ( Arrow::left )
        , position_(0, 0)
{}

Arrow::Arrow(ge211::Position posn, ge211::Dimensions dims, std::string str)
        : velocity_( dims )
        , color_(std::move( str ))
        , dir_ (Arrow::left)
        , position_( posn )
{}

// white for moving
// grey for not moving
// golden for fancy
// green for good
// red for bad