#include "model.hxx"

Model::Model(Game_config const& config)
        : config(config),
          t(ge211::Timer()),
          random_x_coor_(0, config.scene_dims.width - config.block_dims.width),
          random_life_(1, 60),
          block_generation_rate(5),
          block_(Block(config)),
          player(Player()),
          restart_button(),
          player_input(),
          random_life_second(0)
{
}

bool increment_velocity = true;
int i = 2;
int j = 0;

void
Model::on_frame(double dt)
{
    //Spawn new blocks once game starts. Use Timer t
    double elapsed_time = (t.elapsed_time().seconds());
    //std::fmod(elapsed_time, block_generation_rate
    // if(elapsed_time >= i)..
    //std::cout << "random life second" << random_life_second << "\n";
    if (std::fmod(roundf(elapsed_time), 60) == 0) {
        //std::cout << "elapsed time == random_life_second \n";
        //add life to block

        //std::cout << "elapsed time" << roundf(elapsed_time) << "divisible by 3 \n";
        random_life_second = get_random_life();
        //random_life_second += 60;
    }

    //Advance level if pass 10 L1 questions
    if(player.pass_l1()){
        block_.advance_level();
    }

    //what do we want to do if block is out of bounds from above? ie player got it correct?
    if (block_.coord.y < 0) {
        block_.coord.x = random_x_coor_.next();
        block_.coord.y = 0;
        block_.create_q_text();
        block_.next(dt, block_);
    }

    //If block will hit bottom, reposition block so it respawns at top
    if (block_.next(dt,block_).hits_bottom(config)) {
        //std::cout << "next block hits bottom \n";
        block_.life = false;
        //std::cout << "block life once hit_bottom" << block_.life << "\n";
        //Randomize the spawn location of the block, at top of screen
        block_.coord.x = random_x_coor_.next();
        block_.coord.y = 0;
        block_.create_q_text();
        player.lose_life();
//        block_.next(dt, block_);

        //if a block has hit bottom AND the elapsed time is greater than equal to random life,
        //increment random_life_second so it doesn't keep being generated
        //std::cout << "model rounded elapsed_time: " << roundf(elapsed_time) << "\n";
        //std::cout << "model random_life_second: " << j+ random_life_second << "\n";
        if (roundf(elapsed_time)  >= j + random_life_second) {
            //std::cout << "elapsed time == random_life_second \n";
            //add life to block
            //std::cout << "elapsed_time >= j+random - block life becomes true \n";
            block_.life = true;
            //random_life_second += 60;
            j+=60;
        }
    }
    //Increase block velocity over time
    int value = 1;

    //function is called 60 times per second
    //how to do something once and only once if condition is met
    if (elapsed_time >= value && increment_velocity == true) {
        block_.velocity.height += 10;
        increment_velocity = false;  //false until the next minute
        i++;
    }

    int a = 60.01;

    //is this different every time function is called?
//    int random_life_second = get_random_life() + 0.01;
    //increment_velocity should be turned to true at exactly time_elapsed

    if (std::fmod(roundf(elapsed_time * 100) , 100) == a) {
        //std::cout << "elapsed time == a \n";
        increment_velocity = true;
        a += 10;
    }

}
//When player presses "up" ("enter") key, check_answer is called:
//If player gets question correct:
//1. Increment num_q_correct
//2. Increment streak
//3. Destroy block by changing its coord to something out of bounds
//4. Check for combos

//If player gets question wrong:
//1. reset streak to 0
void
Model::check_answer() {
    if(block_.get_answer() != player_input){ //Player wrong
        player.streak = 0;
    } else { //Player correct
        //Increment number of questions correct for player

        player.increase_correct(block_);
        player.total_correct += 1;
        block_.coord.y = -1; //change coord out of bounds
        //Add to streak. If streak >= 3, score multiplier applies
        player.streak += 1;
        player.calculate_score(player, block_);
        if (block_.life == true) {
            player.add_life();
        }

        block_.life = false;
    }
    //player input to blank string? or view?
    player_input = "";
}

void Model::on_key(char input) {
    player_input += input;
}

bool Model::game_over() const {
    if (player.lives <= 0) {
//        std::cout << "num lives: "
        return true;
    }
    return false;
}

int Model::get_random_life() {
    return random_life_.next();
}

//restart_game: resets everything
void
Model::restart_game() {
    t = ge211::Timer(); //reset timer
    block_ = Block(config); //reset block members
    //reset player
    player = Player();
}
