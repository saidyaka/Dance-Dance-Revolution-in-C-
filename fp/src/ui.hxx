// IT MIGHT BE OKAY TO MODIFY THIS FILE, BUT YOU PROBABLY DON'T
// WANT TO.
//
// Defines the structure and resources of the user interface.
//

#pragma once

#include "model.hxx"
#include <ge211.hxx>

///
/// VIEW CONSTANTS
///

extern ge211::Color const normalArrowColor, goldenArrowColor, stationaryArrowColor, correctArrowColor, falseArrowColor;

///
/// MAIN UI STRUCT
///

struct Ui : ge211::Abstract_game
{
    ///
    /// CONSTRUCTOR
    ///

    explicit Ui(Model&);

    ge211::Dimensions initial_window_dimensions() const override;

    void draw(ge211::Sprite_set&) override;

    ///
    /// MEMBER FUNCTIONS (for the controller)
    ///

    void on_key(ge211::Key) override;

    void on_frame(double dt) override;

    ge211::Color colorPicker(const std::string& StringColor);

    ///
    /// MEMBER VARIABLE (model reference)
    ///

    Model& model_;

    ///
    /// MEMBER VARIABLES (for the view)
    ///

    int frameCounter;

    ge211::Font const
            arrow_font_{"arrows.ttf", 50};

    ge211::Font const
            sans{"sans.ttf", 25};
    ge211::Text_sprite
            up_arrow{"h", arrow_font_};
    ge211::Text_sprite
            down_arrow{"c", arrow_font_};
    ge211::Text_sprite
            left_arrow{"f", arrow_font_};
    ge211::Text_sprite
            right_arrow{"g", arrow_font_};
    ge211::Text_sprite
            heart{"W", arrow_font_};

ge211::Text_sprite
      pretext1{"Welcome To Dance Dance Revolution 211", sans};
    ge211::Text_sprite
            pretext2{"To get Points tap the right keys at the right time, green means right red means wrong. Golden Arrows are extra points make sure to get them all", sans};

    ge211::Text_sprite
            pretext3{"PRESS SPACE TO START NOW", sans};

};
