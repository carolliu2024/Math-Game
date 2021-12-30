#include "view.hxx"
#include "model.hxx"

///
/// VIEW CONSTANTS
///

// Colors are red-green-blue(-alpha), each component
// from 0 to 255.
static ge211::Color const ball_color {255, 127, 127};
static ge211::Color const paddle_color {255, 255, 127};
static ge211::Color const brick_color {100, 100, 100};
static ge211::Color const block_color {250, 0, 80};
static ge211::Color const white {255, 255, 255};
static ge211::Color const pink {255, 170, 175};
static ge211::Color const red2 {255, 30, 50};
static ge211::Color const black {0, 0, 0};
static ge211::Color const orange {255,215,0};



///
/// VIEW CONSTRUCTOR
///

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
View::View(Model const& m)
        : model(m),
          background(m.config.scene_dims, white),
          background_p(m.config.scene_dims, pink),
          background_r(m.config.scene_dims, red2),
          block_sprite(m.config.block_dims, block_color),
          question_sprite(ge211::Text_sprite()),
          text_box_sprite({m.config.scene_dims.width/1, (m.config.scene_dims.height - m.config.screen_bottom)}, paddle_color),
          player_input_sprite(),
          life_sprite1(25, orange),
          end_game_sprite(m.config.scene_dims, red2),
          end_game_text(),
          replay_button_sprite({m.config.scene_dims.width/3, (m.config.scene_dims.height/5)}, pink),
          replay_text_sprite()
//question_sprites({ge211::Text_sprite()})
{}


///
/// VIEW FUNCTIONS
///

// Use `Sprite_set::add_sprite(Sprite&, Position)` to add each sprite
// to `sprites`.
void
View::draw(ge211::Sprite_set& sprites)
{
//    std::cout << "view block.y: " << model.block_.coord.y << "\n";

//    ge211::Circle_sprite const ball_sprite;
//    ge211::Rectangle_sprite const paddle_sprite;
//    ge211::Rectangle_sprite const brick_sprite;
/*
    sprites.add_sprite(ball_sprite, model.ball.top_left().into<int>(), 1);
    sprites.add_sprite(paddle_sprite, model.paddle.top_left(), 1);
//    config.paddle_top_left_0());
    for (blick p: model.bricks) {
        sprites.add_sprite(brick_sprite, p.top_left(), 1);
    }*/

    if (model.game_over() == false) {
        //Change Background color based on player's lives
        if (model.player.lives >= 3) {
            sprites.add_sprite(background, {0, 0}, 0);
        } else if (model.player.lives == 2) {
            sprites.add_sprite(background_p, {0, 0}, 0);
        } else if (model.player.lives <= 1) {
            sprites.add_sprite(background_r, {0, 0}, 0);
        }

        //Generating a block with a life:
        if (model.block_.life == true) {
            block_sprite.recolor(orange);
            sprites.add_sprite(block_sprite, model.block_.coord.into<int>(), 2);
        } else {
            //Generating a regular block
            block_sprite.recolor(block_color);
            sprites.add_sprite(block_sprite, model.block_.coord.into<int>(), 2);
        }

        ge211::Text_sprite::Builder question_builder(sans28_);
        question_builder.message(model.block_.q_text);
        question_sprite.reconfigure(question_builder);
        sprites.add_sprite(question_sprite, model.block_.coord.into<int>(), 3);

        ///if game is not over, render these:

        sprites.add_sprite(text_box_sprite, {0, (model.config.screen_bottom - 300)}, 4);
        //std::cout << "player_input" << model.player_input << "\n";
        if (model.player_input != "") {
            ge211::Text_sprite::Builder player_input_builder(sans28_);
            player_input_builder.color(black);
            player_input_builder << model.player_input;
            player_input_sprite.reconfigure(player_input_builder);
            sprites.add_sprite(player_input_sprite, {0, model.config.screen_bottom - 300}, 5);
        }




        //Generating lives in corner of screen:
        for (int i = 0; i < model.player.lives; i++) {
            //change coord to left side of screen
            sprites.add_sprite(life_sprite1, {30 + i * (10 + 50), 50}, 4);
        }
    }

    //BUGS: DONE Stop generating life sprites at some point for some reason
    //Color of background did not change to red

    //DONE Lives are not decremented when question hits bottom when there are only two lives left
    //DONE Extra life blocks are assigned to every block

    ///if game is over, render these:
    if (model.game_over() == true) {
        sprites.add_sprite(end_game_sprite, {0, 0}, 6);
//              end_game_text(),
//          replay_button_sprite({m.config.scene_dims.width/3, (m.config.scene_dims.height/5)}, white),
//          replay_text_sprite()

        ge211::Text_sprite::Builder end_text_builder(sans28_);
        end_text_builder.color(white);
        end_text_builder << "Game Over! Your score is "
                         << model.player.score
                         << " and you got "
                         << model.player.total_correct
                         << " questions correct.";
        end_game_text.reconfigure(end_text_builder);
        sprites.add_sprite(end_game_text, {60, 60}, 7);
        sprites.add_sprite(replay_button_sprite,
                           {model.config.scene_dims.width - (model.config.scene_dims.width / 3) * 2,
                            model.config.scene_dims.height / 2}, 7);
        ge211::Text_sprite::Builder replay_text_builder(sans28_);
        replay_text_builder.color(white);
        replay_text_builder << "Replay";
        replay_text_sprite.reconfigure(replay_text_builder);
        sprites.add_sprite(replay_text_sprite,
                           {(model.config.scene_dims.width - (model.config.scene_dims.width / 3) * 2) + 100,
                            model.config.scene_dims.height / 2 + 50}, 8);
        ///Make sure we like the position of the replay button. if we do:
        ///Get coord of each corner of replay_text_sprite
        ///Check if mouse clicks within these ranges
        ///If mouse does, relaunch game
    }


    /* if want multiple blocks on screen at once
    for(Block b : model.blocks_){

        sprites.add_sprite(question_sprite, b.coord.into<int>(),3);
    }
     */


    //Add string to every block
    //BUG: Each block on the screen has same question
    /*
    for(int i = 0; i < model.blocks_.size(); i++){
        ge211::Text_sprite& question_sprite = dynamic_cast<ge211::Text_sprite &>(model.blocks_[i].q_sprite);
        //uestion_sprite.reconfigure(question_builder);
        sprites.add_sprite(question_sprite, model.blocks_[i].coord.into<int>());
    }
        //sprites.add_sprite(ge211::Text_sprite(q, sans28_), b.coord.into<int>());
        */

}

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model.config.scene_dims;
}
