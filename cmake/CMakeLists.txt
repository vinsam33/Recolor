cmake_minimum_required(VERSION 2.6)

project(projet_techno C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

add_library(libgame.a game_io.c game.c)


add_executable(recolor_text recolor_text.c)
target_link_libraries(recolor_text libgame.a)

add_executable(test_game_slascostes test_game_slascostes.c)
target_link_libraries(test_game_slascostes  libgame.a)

add_executable(test_game_elhdiallo test_game_elhdiallo.c)
target_link_libraries(test_game_elhdiallo libgame.a)

add_executable(test_game_emolere test_game_emolere.c)
target_link_libraries(test_game_emolere libgame.a)

add_executable(test_game_vsamson test_game_vsamson.c)
target_link_libraries(test_game_vsamson libgame.a)


add_test(test test_game_slascostes.c test_game_elhdiallo.c test_game_emolere.c test_game_vsamson.c)

add_test(test_slascostes test_game_slascostes.c)
add_test(test_elhdiallo test_game_elhdiallo.c)
add_test(test_emolere test_game_emolere.c)
add_test(test_vsamson test_game_vsamson.c)

enable_testing()
add_test(test1 ./tot)
