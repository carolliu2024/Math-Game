#include "game_config.hxx"

// Default values of all the member variables.
Game_config::Game_config()
        : scene_dims {1024, 768},
          screen_bottom{scene_dims.height-50},
          block_dims {150, 50},
          restart_dims {150, 100},
          block_velocity_0 {0, 20}, //Initial block fall velocity
          top_margin {100},
          side_margin {170},
          brick_depth {300},
          bottom_margin {50}
{ }
