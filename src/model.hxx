#pragma once
#include "block.hxx"
//#include "ball.hxx"
#include "player.hxx"
#include "game_config.hxx"

#include <vector>

// The logical state of the game.
struct Model
{
    ///
    /// CONSTRUCTOR
    ///

    explicit Model(Game_config const& config = Game_config());

    ///
    /// MEMBER FUNCTIONS
    ///

    void on_key(char input);

    void on_frame(double dt);

    //When player presses "enter" key, check_answer is called:
    //If player gets question correct:
    //1. Increment num_q_correct
    //2. Add bool true to end of answer_history
    //3. Destroy block by changing its coord to something out of bounds
    //4. Check for combos

    //If player gets question wrong:
    //1. Add bool false to end of answer_history
    void check_answer();
    bool game_over() const;
    void restart_game();

    ///
    /// MEMBER VARIABLES
    ///

    Game_config const config;

    //A timer to measure how much time has passed since the game started
    ge211::Timer t;

    ge211::Random_source<int> random_x_coor_;     //for assigning coord
    ge211::Random_source<int> random_life_;

    int get_random_life();
    //Block spawn rate
    int block_generation_rate;

    //Block question displayed on the screen
    Block block_;

    Player player;

    ge211::Rect<int> restart_button;

    std::string player_input;

    int random_life_second;

};
