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

enable_testing()

add_test(test_game_new ./test_game_slascostes game_new)
add_test(test_game_nb_moves_max ./test_game_slascostes game_nb_moves_max)
add_test(test_game_copy ./test_game_slascostes game_copy)

add_test(test_nb_moves_cur ./test_game_elhdiallo nb_moves_cur)
add_test(test_game_set_cell_init ./test_game_elhdiallo game_set_cell_init)
add_test(test_game_is_over ./test_game_elhdiallo game_is_over)

add_test(test_emolere ./test_game_emolere)
add_test(test_vsamson ./test_game_vsamson)