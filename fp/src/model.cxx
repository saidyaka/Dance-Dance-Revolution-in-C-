#include "model.hxx"

Model::Model(Geometry const& geometry)
        : geometry_(geometry)
        , stationary_arrows_ ( { Arrow(), Arrow(), Arrow(), Arrow() } )
        , score_ ( 0 )
        , lives_ ( 5 )
        , state_ ( false )
        , counter_ ( 0 )
        , additional_lives_ ( 0 )
        , arrow_velocity ( { 0, -5} )
{
    stationary_arrows_[0].velocity_ = { 0, 0 };
    stationary_arrows_[0].color_ = "grey";
    stationary_arrows_[0].dir_ = Arrow::left;
    stationary_arrows_[0].position_ = { geometry_.side_margin, geometry_.top_margin };

    stationary_arrows_[1].velocity_ = { 0, 0 };
    stationary_arrows_[1].color_ = "grey";
    stationary_arrows_[1].dir_ = Arrow::up;
    stationary_arrows_[1].position_ =
            { stationary_arrows_[0].position_.x + geometry_.arrow_dims().width + geometry_.arrow_spacing,
              geometry_.top_margin };

    stationary_arrows_[2].velocity_ = { 0, 0 };
    stationary_arrows_[2].color_ = "grey";
    stationary_arrows_[2].dir_ = Arrow::down;
    stationary_arrows_[2].position_ =
            { stationary_arrows_[1].position_.x + geometry_.arrow_dims().width + geometry_.arrow_spacing,
              geometry_.top_margin };

    stationary_arrows_[3].velocity_ = { 0, 0 };
    stationary_arrows_[3].color_ = "grey";
    stationary_arrows_[3].dir_ = Arrow::right;
    stationary_arrows_[3].position_ =
            { stationary_arrows_[2].position_.x + geometry_.arrow_dims().width + geometry_.arrow_spacing,
              geometry_.top_margin };
}

// Public

void Model::go()
{
    score_ = 0;
    state_ = true;
}

void Model::reset_game()
{
    for (int x = 0; x < left_arrows_.size(); x++)
    {
        destroy_arrow_(left_arrows_);
    }
    for (int x = 0; x < up_arrows_.size(); x++)
    {
        destroy_arrow_(up_arrows_);
    }
    for (int x = 0; x < down_arrows_.size(); x++)
    {
        destroy_arrow_(down_arrows_);
    }
    for (int x = 0; x < right_arrows_.size(); x++)
    {
        destroy_arrow_(right_arrows_);
    }
    state_ = false;
}

void Model::update(int frame_count)
{
    if (lives_ <= 0)
    {
        reset_game();
    }
    if (state_)
    {
        for (int x = 0; x < left_arrows_.size(); x++) {
            left_arrows_[x]->position_ += left_arrows_[x]->velocity_;
        }
        for (int x = 0; x < up_arrows_.size(); x++) {
            up_arrows_[x]->position_ += up_arrows_[x]->velocity_;
        }
        for (int x = 0; x < down_arrows_.size(); x++) {
            down_arrows_[x]->position_ += down_arrows_[x]->velocity_;
        }
        for (int x = 0; x < right_arrows_.size(); x++) {
            right_arrows_[x]->position_ += right_arrows_[x]->velocity_;
        }
        arrow_hits_top_(left_arrows_);
        arrow_hits_top_(up_arrows_);
        arrow_hits_top_(down_arrows_);
        arrow_hits_top_(right_arrows_);

        if (frame_count % 100 == 0)
        {
            int i = rand() % 4;
            int i2 = rand() % 50;
            Arrow* new_arrow = new Arrow();
            new_arrow->velocity_ = arrow_velocity;
            arrow_velocity.height -= 1;
            if (i2 == 0)
                new_arrow->color_ = "yellow";
            else
                new_arrow->color_ = "white";

            if (i == 0)
            {
                new_arrow->dir_ = Arrow::left;
                new_arrow->position_ = { geometry_.side_margin, geometry_.scene_dims.height };
                left_arrows_.push_back(new_arrow);
            }
            else if (i == 1)
            {
                new_arrow->dir_ = Arrow::up;
                new_arrow->position_ =
                        { stationary_arrows_[0].position_.x + geometry_.arrow_dims().width + geometry_.arrow_spacing,
                          geometry_.scene_dims.height };
                up_arrows_.push_back(new_arrow);
            }
            else if (i == 2)
            {
                new_arrow->dir_ = Arrow::down;
                new_arrow->position_ =
                        { stationary_arrows_[1].position_.x + geometry_.arrow_dims().width + geometry_.arrow_spacing,
                          geometry_.scene_dims.height };
                down_arrows_.push_back(new_arrow);
            }
            else if (i == 3)
            {
                new_arrow->dir_ = Arrow::right;
                new_arrow->position_ =
                        { stationary_arrows_[2].position_.x + geometry_.arrow_dims().width + geometry_.arrow_spacing,
                          geometry_.scene_dims.height };
                right_arrows_.push_back(new_arrow);
            }
        }
    }
}

void Model::left_key()
{
    if (state_) {
        double score_gain = score_gain_(abs(left_arrows_[0]->position_.y - stationary_arrows_[0].position_.y),
                                        left_arrows_[0]->color_);
        if (score_gain == 0.0) {
            lives_--;
            counter_ = 0;
            change_color_(*left_arrows_[0], "red");
            score_ -= 20;
        } else {
            counter_++;
            change_color_(*left_arrows_[0], "green");
            destroy_arrow_(left_arrows_);
            score_ += score_gain;
        }
    }
}

void Model::up_key()
{
    if (state_) {
        double score_gain = score_gain_(abs(up_arrows_[0]->position_.y - stationary_arrows_[1].position_.y),
                                        up_arrows_[0]->color_);
        if (score_gain == 0.0) {
            lives_--;
            counter_ = 0;
            change_color_(*up_arrows_[0], "red");
            score_ -= 20;
        } else {
            counter_++;
            change_color_(*up_arrows_[0], "green");
            destroy_arrow_(up_arrows_);
            score_ += score_gain;
        }
    }
}

void Model::down_key()
{
    if (state_) {
        double score_gain = score_gain_(abs(down_arrows_[0]->position_.y - stationary_arrows_[2].position_.y),
                                        down_arrows_[0]->color_);
        if (score_gain == 0.0) {
            lives_--;
            counter_ = 0;
            change_color_(*down_arrows_[0], "red");
            score_ -= 20;
        } else {
            counter_++;
            change_color_(*down_arrows_[0], "green");
            destroy_arrow_(down_arrows_);
            score_ += score_gain;
        }
    }
}

void  Model::right_key()
{
    if (state_) {
        double score_gain = score_gain_(abs(right_arrows_[0]->position_.y - stationary_arrows_[3].position_.y),
                                        right_arrows_[0]->color_);
        if (score_gain == 0.0) {
            lives_--;
            counter_ = 0;
            change_color_(*right_arrows_[0], "red");
            score_ -= 20;
        } else {
            counter_++;
            change_color_(*right_arrows_[0], "green");
            destroy_arrow_(right_arrows_);
            score_ += score_gain;
        }
    }
}

std::vector<Arrow*> const& Model::get_up_arrows() const
{
    return up_arrows_;
}

std::vector<Arrow*> const& Model::get_down_arrows() const
{
    return down_arrows_;
}

std::vector<Arrow*> const& Model::get_left_arrows() const
{
    return left_arrows_;
}

std::vector<Arrow*> const& Model::get_right_arrows() const
{
    return right_arrows_;
}

std::vector<Arrow> const& Model::get_stationary_arrows() const
{
    return stationary_arrows_;
}

bool Model::get_state() const
{
    return state_;
}

const int Model::get_lives() const
{
    return lives_;
}

const Geometry Model::get_geometry() const
{
    return geometry_;
}

const int Model::get_score() const
{
    return score_;
}

// Private

void Model::arrow_hits_top_(std::vector<Arrow*>& vector)
{
    if (!vector.empty() && vector[0]->position_.y < 0)
    {
        destroy_arrow_(vector);
        score_ = 0;
        counter_ = 0;
    }
}

void Model::destroy_arrow_(std::vector<Arrow*>& vector)
{
    delete vector[0];
    for (int x = 0; x < vector.size() - 1; x++)
    {
        vector[x] = vector[x + 1];
    }
    vector.pop_back();
}

void Model::change_color_(Arrow& arrow, std::string color)
{
    arrow.color_ = color;
}

double Model::score_gain_(int distance, std::string arrow_color)
{
    int score_bonus = 1;
    if ( arrow_color == "yellow" )
        score_bonus = 5;
    if ( distance > 30 )
        return 0.0;
    if ( distance > 20 )
        return 2.0 * score_bonus;
    if ( distance > 10 )
        return 5.0 * score_bonus;
    if ( distance > 5 )
        return 7.0 * score_bonus;
    if ( distance >= 0 )
        return 10.0 * score_bonus;
    return 0.0;
}

void Model::life_plus_()
{
    if ((int) score_ % 500 > additional_lives_)
    {
        additional_lives_++;
        lives_++;
    }
}