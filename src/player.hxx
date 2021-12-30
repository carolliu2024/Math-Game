//
// Created by Dannes Zhang on 11/22/21.
//
#pragma once

#include <iostream>
#include "block.hxx"

#ifndef GAME_PLAYER_HXX
#define GAME_PLAYER_HXX

//how to create default player class
struct Player
{
    //convention: put _ after every private data member as note to pay
    // attention to it
    int num_l1_correct;
    int num_l2_correct;        //worth more points

    int total_correct;
    int lives;
    int score;
    int streak;
    //bool game_over;
    //int input;         //input is whatever on_key collects from controller
    //bool answer_history[3]; //do not initialize

    //Block block_;

    Player();
    bool pass_l1();

    void add_life();

    void lose_life(); //Decrease lives by 1

    void increase_correct(Block b);

    void calculate_score(Player& player, Block& block);
    /*

    //need args?

    void calculate_total_correct(Player& player);
    bool correct_answer(Player& player, Block& block);

    //To retrieve in other files
    int get_total_correct(Player& player);
    int get_score();

    //create functions to return each data member in class
    //functions should be const bc don't modify data
    //don't need args

    */
};

#endif //GAME_PLAYER_HXX
