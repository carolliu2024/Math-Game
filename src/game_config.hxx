//
// Created by Dannes Zhang on 11/22/21.
//
#pragma once
#include <ge211.hxx>
#ifndef GAME_GAME_CONFIG_HXX
#define GAME_GAME_CONFIG_HXX


struct Game_config
{
    // Constructs an instance with the default parameters.
    Game_config();

    // The dimensions of the whole window:
    ge211::Dims<int> scene_dims;

    // The ball's initial velocity {width, height}:
    ge211::Dims<int> velocity_0;

    // Boost to velocity on L2 (acceleration)
    ge211::Dims<int> boost;
        //only affects y

    // Number of pixels from sides of screen:
    int side_margin;

    // Number of pixels from bottom of screen to leave room for text box:
    int bottom_margin;

    // Life_generation_rate (1/min)
    int life_generation_rate;


    // The dimensions of each block
    ge211::Dims<int> l1_block_dims;
    ge211::Dims<int> l2_block_dims;


    int num_lives;
    int num_l1;     // Number of L1 questions before L2 begins




};

#endif //GAME_GAME_CONFIG_HXX
