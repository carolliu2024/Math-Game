#include "controller.hxx"

Controller::Controller(ge211::Dims<int> screen_dimensions)
        : model_(Model Model(screen_dimensions)),
          view_(model_),
          player_input("")
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}

//For restart button
void
Controller::on_mouse_down(
        ge211::events::Mouse_button button,
        ge211::Posn<int> position)
{
    //If the button is active (when game over) AND
    // mouse pos is within button,

    // Restart game

    //How to reset game?
}

//Getting user input from typing
void
Controller::on_key_up(ge211::Key key)
{
    while (key != ge211::Key::code('\r')) {
        player_input = player_input + char(key.code());
    }
    //If the player hits enter, check if the answer is correct.
    //If correct, remove block from blocks_
    if(key == ge211::Key::code('\r')){
        //Check answer matches, destroy block, add points
        model_.check_answer(player_input);
        //Clear player_input
        player_input = "";
    }
}
