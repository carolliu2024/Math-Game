//
// Created by Dannes Zhang on 11/22/21.
//

#pragma once

#include "game_config.hxx"

#include <ge211.hxx>

#include <iostream>
#ifndef GAME_BLOCK_HXX
#define GAME_BLOCK_HXX

///   struct Position
///   {
///       float x;   // pixel distance from left edge of window
///       float y;   // pixel distance from top edge of window
///   };
using Position = ge211::Posn<float>;

///   struct Velocity
///   {
///       float width;   // horizontal rate of change (px/s)
///       float height;  // vertical rate of change (px/s)
///   };
using Velocity = ge211::Dims<float>;

///   struct Block
///   {
///       int x;       // x coordinate of left side of rectangle
///       int y;       // y coordinate of top side of rectangle
///       int width;
///       int height;
///   };
using rect = ge211::Rect<int>;

class Block
{
        ///Data members
        Position coord;       // top left corner of block
        int width;
        int height;
        char question;      //math question
        bool life;          //whether the block has an extra life attached
        Velocity velocity;      // The velocity of the block in pixels per tick.
        enum class Block_Level  //determines whether the question is single or
                                // double digits
        {
            l1,
            l2
        };

        ///Constructors
        Block();
        Block(Position coord);

        ///Member functions
        //Assigns the coordinates for a block
        //y coordinate is always 0; x coordinate is randomized
        Position assign_coord();
        bool destroy_block(Block block) const;

private:
        ge211::Random_source<int> random_x_coor_;     //for assigning coord
        ge211::Random_source<int> random_life;     //for assigning random life
    };

//Compares two Blocks for equality. This may be useful for testing.
bool
operator==(Block const&, Block const&);

//Inequality for Blocks.
bool
operator!=(Block const&, Block const&);

// Stream insertion (printing) for Block
std::ostream&
operator<<(std::ostream&, Block const&);


#endif //GAME_BLOCK_HXX
