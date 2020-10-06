#include <ge211.hxx>

struct Arrow
{
    ///
    /// CONSTRUCTORS
    ///

    Arrow();

    Arrow(ge211::Position, ge211::Dimensions, std::string);

    ///
    /// MEMBER VARIABLES
    ///

    // The velocity of the arrow in pixels per tick.
    ge211::Dimensions           velocity_;

    // A string stating the color of the arrow.
    // Can be "grey", "green", "red", "white", "yellow"
    std::string                 color_;

    // Indicates the direction of the arrow.
    enum direction
    {   up,
        down,
        left,
        right,
    }                           dir_;

    // The top-left position of the arrow.
    ge211::Position   position_;
};