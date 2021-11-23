//
// Created by Dannes Zhang on 11/22/21.
//

#include "block.hxx"

Block::Block()
{

}

Block::Block(Position coord)
{

}

Position
Block::assign_coord()
{
    return Position(0, 0);
}

bool
Block::destroy_block(Block block) const
{
    return false;
}
