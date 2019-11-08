cmake_minimum_required(VERSION 2.6)

project(projet_techno C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

add_library(game game_io.c game.c)


add_executable(recolor_text recolor_text.c)
target_link_libraries(recolor_text game)

add_executable(test_game_slascostes test_game_slascostes.c)
target_link_libraries(test_game_slascostes game)

add_executable(test_game_elhdiallo test_game_elhdiallo.c)
target_link_libraries(test_game_elhdiallo game)

add_executable(test_game_emolere test_game_emolere.c)
target_link_libraries(test_game_emolere game)

add_executable(test_game_vsamson test_game_vsamson.c)
target_link_libraries(test_game_vsamson game)


add_test(test test_game_slascostes.c test_game_elhdiallo.c test_game_emolere.c test_game_vsamson.c)


enable_testing()
add_test(test1 ./tot)
