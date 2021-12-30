//
// Created by Dannes Zhang on 11/22/21.
//

#include "player.hxx"
#include "block.hxx"

Player::Player()
        : num_l1_correct(0),
          num_l2_correct(0),
          total_correct(0),
          lives(3),
          score(0),
          streak(0)
          //game_over(false)
          // block_(Block())
{
    //input

}

bool
Player::pass_l1()
{
    return num_l1_correct >= 10;
}

//Points can only increase, not decrease
//  Only affected by correct answers
//  L1 answers get +100
//  L2 answers get +150
//  Combos begin at three consecutive correct answers
//L1 answers get +110
//L2 answers get 1
//create a list of what correct_answer returns
//+10 for each question once combo begins

//How to assign a random block a life?


void
Player::lose_life()
{
    lives--;
}

void
Player::add_life()
{
    lives++;
}

void
Player::calculate_score(Player& player, Block& block)
{
    //calls calculate_combo for combo points
    if (streak >= 3) {
        //l1 questions
        if (block.block_level == 1) {
            player.score += 110;
        } else {//l2 questions
            player.score += 160;
        }
    } else {
        //l1 questions
        if (block.block_level == 1) {
            player.score += 100;
        } else { //l2 questions
            player.score += 150;
        }
    }
}

void
Player::increase_correct(Block b)
{
    if (b.block_level == 1) {
        num_l1_correct++;
    } else {
        num_l2_correct++;
    }
}
