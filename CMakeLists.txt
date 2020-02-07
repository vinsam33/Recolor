cmake_minimum_required(VERSION 2.6)

project(projet_techno C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall  --coverage")

add_library(game game_io.c game.c)

add_executable(recolor_text recolor_text.c)
target_link_libraries(recolor_text game)

add_executable(recolor_solve recolor_solve.c)
target_link_libraries(recolor_solve game)

add_executable(test_game_slascostes test_game_slascostes.c)
target_link_libraries(test_game_slascostes game)

add_executable(test_game_elhdiallo test_game_elhdiallo.c)
target_link_libraries(test_game_elhdiallo game)

add_executable(test_game_emolere test_game_emolere.c)
target_link_libraries(test_game_emolere game)

add_executable(test_game_vsamson test_game_vsamson.c)
target_link_libraries(test_game_vsamson game)

include(CTest)
enable_testing()

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_test(test_game_new ./test_game_slascostes game_new)
add_test(test_game_nb_moves_max ./test_game_slascostes game_nb_moves_max)
add_test(test_game_copy ./test_game_slascostes game_copy)
add_test(test_game_new_ext ./test_game_slascostes game_new_ext)

add_test(test_nb_moves_cur ./test_game_elhdiallo nb_moves_cur)
add_test(test_game_set_cell_init ./test_game_elhdiallo game_set_cell_init)
add_test(test_game_is_over ./test_game_elhdiallo game_is_over)
add_test(test_game_is_wrapping ./test_game_elhdiallo game_is_wrapping)
add_test(test_game_width ./test_game_elhdiallo game_width)

add_test(test_game_set_max_moves ./test_game_emolere game_set_max_moves)
add_test(test_game_play_one_move ./test_game_emolere game_play_one_move)
add_test(test_game_restart ./test_game_emolere game_restart)
add_test(test_game_new_empty_ext ./test_game_emolere game_new_empty_ext)
add_test(test_game_load ./test_game_emolere game_load)

add_test(test_game_new_empty ./test_game_vsamson game_new_empty)
add_test(test_game_cell_current_color ./test_game_vsamson game_cell_current_color)
add_test(test_game_delete ./test_game_vsamson game_delete)
add_test(test_game_height ./test_game_vsamson game_height)
add_test(test_game_save ./test_game_vsamson game_save)