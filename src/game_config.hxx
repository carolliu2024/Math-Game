//
// Created by Dannes Zhang on 11/22/21.
//
#pragma once

#include <ge211.hxx>


struct Game_config
{
    // Constructs an instance with the default parameters.
    Game_config();

    // The dimensions of the whole window:
    ge211::Dims<int> scene_dims;
    int screen_bottom;

    ge211::Dims<int> block_dims;

    ge211::Dims<int> restart_dims;

    ge211::Dims<int> block_velocity_0;

    // Number of pixels from top of screen to top of brick formation:
    int top_margin;

    // Number of pixels from sides of screen to sides of brick formation:
    int side_margin;

    // Number of pixels from *top* of screen to *bottom* of brick formation.
    // unused parameter?
    int brick_depth;

    // Number of pixels from bottom of screen to bottom of paddle.
    // unused parameter?
    int bottom_margin;

};
