#include "model.hxx"
#include <catch.hxx>

TEST_CASE("State true and false")
{
    Geometry geometry;
    Model model(geometry);
    CHECK_FALSE( model.get_state() );
    model.go();
    CHECK( model.get_state() );
    model.reset_game();
    CHECK_FALSE( model.get_state() );
}

TEST_CASE("Checking the score")
{
    Geometry geometry;
    Model model(geometry);
    Model::Test_access t{model};
    CHECK( model.get_score() == 0 );
    model.go();
    CHECK( model.get_score() == 0 );
    Arrow* arr = new Arrow( {geometry.side_margin, geometry.top_margin}, {0, 0}, "white");
    t.add_arrow(arr);
    model.left_key();
    CHECK( model.get_left_arrows().empty() );
    CHECK( model.get_score() == 10.0 );
}

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate at least six of the functional
// requirements.
//
