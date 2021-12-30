#include "controller.hxx"
#include "model.hxx"

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
Controller::Controller(Model& model)
        : model(model),
          view(model)
{ }

///
/// CONTROLLER FUNCTIONS
///

void
Controller::on_key_up(ge211::Key key)
{
    if (key == ge211::Key::code(' ')) {
        //std::cout << "enter key pressed \n";
        //call check_answer()
        model.check_answer();
    }
    if (key == ge211::Key::code('1') ||
        key == ge211::Key::code('2') ||
        key == ge211::Key::code('3') ||
        key == ge211::Key::code('4') ||
        key == ge211::Key::code('5') ||
        key == ge211::Key::code('6') ||
        key == ge211::Key::code('7') ||
        key == ge211::Key::code('8') ||
        key == ge211::Key::code('9') ||
        key == ge211::Key::code('0') ||
        key == ge211::Key::code('-')) {
        //std::cout << "player_input if \n";
//    std::cout << "hi";
        char c = key.code();
        //retains the key for view to use
        model.on_key(c);
//        player_input = player_input + c;
//        std::cout << "player_input controller: " << player_input <<"\n";
    }

    if (key == ge211::Key::code('q')) {
        quit();
    }
}

void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int> pos)
{
    //Click within replay button range to restart game
    if(model.game_over()){
        float button_left = model.config.scene_dims.width * 1/3;
        float button_right = model.config.scene_dims.width * 2/3;
        float button_top = model.config.scene_dims.height / 2;
        float button_bot = button_top + model.config.scene_dims.height/5;
        if (pos.x > button_left && pos.x < button_right && pos.y > button_top && pos.y < button_bot){
            //Restart game here
            model.restart_game();
        }
    }
}

void
Controller::on_frame(double dt)
{
    model.on_frame(dt);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view.initial_window_dimensions();
}

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view.draw(sprites);
}
