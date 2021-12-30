//
// Created by Dannes Zhang on 11/22/21.
//

#include "block.hxx"
#include "game_config.hxx"
#include <iostream>
#include<sstream>

//Must take game_config as input because game_config must be initialized
// before random_x_coor_
Block::Block(Game_config game_config)
    : coord(assign_coord()),
    width(17),
    height(7),
    random_x_coor_(0, game_config.scene_dims.width - width),
    random_life_(0, 60),
    random_operator_(1, 4),
    random_num_l1_(0,9),
    random_num_l2_(0,99),
    block_level(1),
    player_(Player())
{}

Position
Block::assign_coord()
{
    int x = random_x_coor_.next();
    return Position(x, 0);
}

void
Block::create_question(Block block)
{
    if (block.block_level == 1) {
        //l1
        block.question[0] = ge211::to_string(random_num_l1_.next());
        block.question[2] = ge211::to_string(random_num_l1_.next());
    } else {
        //l2
        block.question[0] = ge211::to_string(random_num_l2_.next());
        block.question[2] = ge211::to_string(random_num_l2_.next());
    }
    block.question[1] = ge211::to_string(random_operator_.next());
}


void
Block::calculate_answer(Block block)
{
    //change block.answer
    int num1 = std::stoi(block.question[0]);
    int num2 = std::stoi(block.question[2]);
    if (block.question[1] == "1") {
        block.answer = num1 + num2;
    } else if (block.question[1] == "2") {
        block.answer = num1 - num2;
    } else if (block.question[1] == "3") {
        block.answer = num1 / num2;
    } else if (block.question[1] == "4") {
        block.answer = num1 * num2;
    }
}


Position
Block::get_coord(Block block)
{
    return block.coord;
}

int
Block::get_width(Block block)
{
    return block.width;
}

int
Block::get_height(Block block)
{
    return block.height;
}

std::string
Block::get_question(Block block)
{
    std::string s = "";
    for (int i=0; i < 2; i++) {
        s = s + block.question[i];
    }
    return s;
}

int
Block::get_answer(Block block)
{
    return block.answer;
}

void
Block::advance_level(Block block)
{
    if (block.block_level == 1) {
        block.block_level += 1;
    }
    block.height = 12;
    //update height and width
}

int
Block::get_block_level(Block block)
{
    return block.block_level;
}
