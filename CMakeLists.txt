cmake_minimum_required(VERSION 3.3)

# TODO: Change “game” to the name of your game (no spaces!):
set(GAME_EXE game)

project(${GAME_EXE} CXX)
include(.cs211/cmake/CMakeLists.txt)

# TODO: PUT ADDITIONAL MODEL .cxx FILES IN THIS LIST:
set(MODEL_SRC
        src/model.cxx
        src/game_config.cxx
        src/block.cxx
        src/player.cxx)

# TODO: PUT ADDITIONAL NON-MODEL (UI) .cxx FILES IN THIS LIST:
add_program(math
        src/main.cxx
        src/view.cxx
        src/controller.cxx
        ${MODEL_SRC})

target_link_libraries(math ge211)

add_test_program(model_test
        test/model_test.cxx
        ${MODEL_SRC})

add_test_program(block_test
        test/block_test.cxx
        ${MODEL_SRC})

add_test_program(player_test
        test/player_test.cxx
        ${MODEL_SRC})


target_link_libraries(model_test ge211)


# vim: ft=cmake
