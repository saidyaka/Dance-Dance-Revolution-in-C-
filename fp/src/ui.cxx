// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "ui.hxx"

///
/// VIEW CONSTANTS
///

// Colors are red-green-blue(-alpha), each component
// from 0 to
//


ge211::Color const normalArrowColor   {255, 255, 255};
ge211::Color const goldenArrowColor  {255, 215, 0};
ge211::Color const stationaryArrowColor   {128, 128, 128};
ge211::Color const correctArrowColor   {55, 235, 52};
ge211::Color const falseArrowColor   {240, 0 , 0};


///
/// VIEW FUNCTIONS
///

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
Ui::Ui(Model& model)
        : model_(model)
{
    frameCounter = 0;
}

ge211::Dimensions Ui::initial_window_dimensions() const
{
    return model_.get_geometry().scene_dims;
}

/*std::vector<Arrow> const& get_up_arrows() const;
    std::vector<Arrow> const& get_down_arrows() const;
    std::vector<Arrow> const& get_left_arrows() const;
    std::vector<Arrow> const& get_right_arrows() const;
     std::vector<Arrow> const& get_stationary_arrows() const;
    */

void Ui::draw(ge211::Sprite_set& sprites)
{

//sprites.add_sprite(down_arrow,)
  //  sprites.add_sprite(ball_sprite_, model_.ball_.top_left());

  if(!model_.get_state()) {
      ge211::Position textPositions = {model_.get_geometry().scene_dims.width / 2,
                                       (model_.get_geometry().scene_dims.height * 2) / 3};
      sprites.add_sprite(pretext1, textPositions);
     sprites.add_sprite(pretext2, {textPositions.x, model_.get_geometry().scene_dims.height/2});
     sprites.add_sprite(pretext3, {textPositions.x, textPositions.y/2});
  } else {

      left_arrow = ge211::Text_sprite::Builder(arrow_font_)
              .message("f")
              .color(colorPicker(model_.get_stationary_arrows()[0].color_))
              .build();

      up_arrow = ge211::Text_sprite::Builder(arrow_font_)
              .message("h")
              .color(colorPicker(model_.get_stationary_arrows()[1].color_))
              .build();

      down_arrow = ge211::Text_sprite::Builder(arrow_font_)
              .message("c")
              .color(colorPicker(model_.get_stationary_arrows()[2].color_))
              .build();

      right_arrow = ge211::Text_sprite::Builder(arrow_font_)
              .message("g")
              .color(colorPicker(model_.get_stationary_arrows()[3].color_))
              .build();

      sprites.add_sprite(left_arrow, model_.get_stationary_arrows()[0].position_);
      sprites.add_sprite(up_arrow, model_.get_stationary_arrows()[1].position_);
      sprites.add_sprite(down_arrow, model_.get_stationary_arrows()[2].position_);
      sprites.add_sprite(right_arrow, model_.get_stationary_arrows()[3].position_);

      for (Arrow *up_arrows : model_.get_up_arrows()) {
          up_arrow = ge211::Text_sprite::Builder(arrow_font_)
                  .message("h")
                  .color(colorPicker(up_arrows->color_))
                  .build();
          sprites.add_sprite(up_arrow, up_arrows->position_);
      }
      for (Arrow *down_arrows : model_.get_down_arrows()) {
          down_arrow = ge211::Text_sprite::Builder(arrow_font_)
                  .message("c")
                  .color(colorPicker(down_arrows->color_))
                  .build();

          sprites.add_sprite(down_arrow, down_arrows->position_);
      }
      for (Arrow *left_arrows : model_.get_left_arrows()) {
          left_arrow = ge211::Text_sprite::Builder(arrow_font_)
                  .message("f")
                  .color(colorPicker(left_arrows->color_))
                  .build();

          sprites.add_sprite(left_arrow, left_arrows->position_);
      }
      for (Arrow *right_arrows : model_.get_up_arrows()) {
          right_arrow = ge211::Text_sprite::Builder(arrow_font_)
                  .message("g")
                  .color(colorPicker(right_arrows->color_))
                  .build();

          sprites.add_sprite(right_arrow, right_arrows->position_);
      }
      for (int i = 1; i <= model_.get_lives(); i++) {
          ge211::Position heart_pos = model_.get_geometry().score_posn();
          heart_pos.y += model_.get_geometry().score_dims_.height;
          sprites.add_sprite(heart, heart_pos + model_.get_geometry().life_dims());
      }

  }
}

ge211::Color Ui::colorPicker(const std::string& StringColor)
{
    if(StringColor == "gray")
        return stationaryArrowColor;
    if (StringColor== "yellow")
        return goldenArrowColor;
    if (StringColor == "green")
        return correctArrowColor;
    if (StringColor == "red")
        return falseArrowColor;
    return normalArrowColor;
}

///
/// CONTROLLER FUNCTIONS
///

void Ui::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q'))
        quit();

    if (key == ge211::Key::code(' '))
        model_.go();
//add another function to destroy arrows.
    if (key == ge211::Key::left())
        model_.left_key();
    if (key == ge211::Key::up())
        model_.up_key();
    if (key == ge211::Key::down())
        model_.down_key();
    if (key == ge211::Key::right())
        model_.right_key();
}

void Ui::on_frame(double)
{
 frameCounter++;

 model_.update(frameCounter);
}





