#include "geometry.hxx"

Geometry::Geometry() noexcept
        : scene_dims      { 1024, 768 }
        , score_dims_     {  100,  20 }
        , arrow_spacing   { 100 }
        // Make arrow_velocity0 a real number.
        , arrow_velocity0 { 0, 0 }
        , top_margin      { 100 }
        , side_margin     { 170 }
{ }

ge211::Dimensions Geometry::combo_dims() const noexcept
{
    return { score_dims_.width,
             scene_dims.height / 4 };
}

ge211::Position Geometry::combo_posn() const noexcept
{
    return { scene_dims.width - score_dims_.width,
             scene_dims.height / 3 };
}

ge211::Dimensions Geometry::life_dims() const noexcept
{
    return { score_dims_.width / 5,
             score_dims_.height };
}

ge211::Position Geometry::score_posn() const noexcept
{
    return { scene_dims.width - score_dims_.width,
             0 };
}

ge211::Dimensions Geometry::arrow_dims() const noexcept
{
    return { score_dims_.height,
             (scene_dims.width - side_margin - 4 * arrow_spacing - score_dims_.width) / 4 };
}