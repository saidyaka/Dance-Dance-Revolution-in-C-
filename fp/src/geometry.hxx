#pragma once

#include <ge211.hxx>

struct Geometry
{
    // Constructs an instance with the default parameters.
    Geometry() noexcept;

    // The dimensions of the whole window:
    ge211::Dimensions scene_dims;

    // The number of pixels of space between each column of arrows
    int arrow_spacing;

    // The initial velocity of the moving arrows {width, height}:
    ge211::Dimensions arrow_velocity0;

    // Number of pixels from top of screen to top of row of arrows:
    int top_margin;

    // Number of pixels from left side of the screen to the left column of arrows:
    int side_margin;

    // The dimensions of the score:
    ge211::Dimensions score_dims_;

    // The number of points needed to gain an additional life.
    double score_threshold;

    // The dimensions of the combo counter:
    ge211::Dimensions combo_dims() const noexcept;

    // The top-left position of the combo counter:
    ge211::Position combo_posn() const noexcept;

    // The dimensions of each life:
    ge211::Dimensions life_dims() const noexcept;

    // The top-left position of the score:
    ge211::Position score_posn() const noexcept;

    // The dimensions of each arrow:
    ge211::Dimensions arrow_dims() const noexcept;
};