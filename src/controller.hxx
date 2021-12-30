#pragma once

#include "view.hxx"

#include <ge211.hxx>

struct Controller : ge211::Abstract_game
{
    //
    // CONSTRUCTOR
    //

    explicit Controller(Model&);


    //
    // MEMBER FUNCTIONS
    void on_key_up(ge211::Key) override;

    /// Defines how the game responds to mouse clicks (which is by
    /// telling the model to launch the ball).
    void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;

    void on_frame(double dt) override;

    ge211::Dims<int> initial_window_dimensions() const override;

    void draw(ge211::Sprite_set&) override;


    //
    // MEMBER VARIABLES
    //

    /// This is a reference to the model. It means that the controller
    /// doesn't own the model but has access to it. Thus, the client of
    /// the controller (brick_out.cxx) must create a `Model` first and
    /// then pass that by reference to the `Controller` constructor.
    Model& model;

    /// This is the view, which contains the game’s data and code for
    /// displaying the state of the model to the screen.
    View view;
    std::string player_input;
};
