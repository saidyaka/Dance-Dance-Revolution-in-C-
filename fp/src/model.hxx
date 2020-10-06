#pragma once

#include <ge211.hxx>
#include <vector>
#include "geometry.hxx"
#include "arrow.hxx"
#include <random>

class Model
{
public:

    ///
    /// CONSTRUCTOR
    ///

    explicit Model(Geometry const& geometry = Geometry());

    ///
    /// PUBLIC MEMBER FUNCTIONS
    ///

    // Sets the state of the game to true and resets the score.
    void go();

    // Returns the game to a dead state.
    void reset_game();

    // Updates the state of the game for one frame.
    void update(int);

    // Runs checks when directional keys are pressed.
    void left_key();
    void right_key();
    void down_key();
    void up_key();


    // Views the states of each of the vectors of arrows.
    std::vector<Arrow*> const& get_up_arrows() const;
    std::vector<Arrow*> const& get_down_arrows() const;
    std::vector<Arrow*> const& get_left_arrows() const;
    std::vector<Arrow*> const& get_right_arrows() const;
    std::vector<Arrow> const& get_stationary_arrows() const;

    // Returns what state the game is in.
    bool get_state() const;

    // Returns the number of lives the user has.
    const int get_lives() const;

    // Returns a const copy of the geometry.
    const Geometry get_geometry() const;

    const int get_score() const;

    // Test access for testing.
    friend struct Test_access;

    struct Test_access
    {
        Model& m;

        void add_arrow(Arrow* arr)
        {
            m.left_arrows_.push_back(arr);
        }
    };

private:

    ///
    /// POSSIBLE HELPER FUNCTIONS
    ///

    // Determines whether an arrow hits the top of
    // the screen. If so, it destroys it.
    void arrow_hits_top_(std::vector<Arrow*>&);

    // Removes the first arrow from the vector.
    void destroy_arrow_(std::vector<Arrow*>&);

    // Changes the color of the indicated arrow to the color given.
    void change_color_(Arrow&, std::string);

    // Returns the corresponding score gained with the given distance
    // and arrow color.
    double score_gain_(int, std::string);

    // Returns whether the user should gain another life.
    void life_plus_();

    ///
    /// PRIVATE MEMBER VARIABLES
    ///

    // The geometry parameters of the model.
    Geometry const geometry_;

    // Vectors of Arrows (a class we will make) for storing the moving arrows.
    std::vector<Arrow*> up_arrows_;
    std::vector<Arrow*> down_arrows_;
    std::vector<Arrow*> left_arrows_;
    std::vector<Arrow*> right_arrows_;

    // A vector of Arrows for storing the stationary arrows.
    std::vector<Arrow> stationary_arrows_;

    // The score
    double score_;

    // The current number of lives
    int lives_;

    // The number of lives that have been added
    int additional_lives_;

    // Game state
    bool state_;

    // The combo counter
    int counter_;

    // The current arrow velocity
    ge211::Dimensions arrow_velocity;
};