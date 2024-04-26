add_library(backend
        model/card.c
        model/deck.c
        model/column.c
        model/foundation_pile.c
        controller/handle_commands.c
        controller/handle_game_moves.c
        controller/game_state.c
)

target_include_directories(backend
        PUBLIC
        ../include
)

if (NOT USER_INTERFACE)
    set(MAIN_TARGET Main)
    add_executable(Main
        main.c
        view/terminal/column_view.c
        view/terminal/terminal_style.c
        view/terminal/command_parser.c
    )

    target_link_libraries(${MAIN_TARGET} backend)
ENDIF()

IF (USER_INTERFACE)
    set(MAIN_TARGET MainGui)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    #find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

    #find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

    #find_package(SDL2_image REQUIRED CONFIG COMPONENTS SDL2_image)


    find_package(SDL2 REQUIRED)

    include_directories(${SDL2_INCLUDE_DIRS})

    find_package(SDL2_image REQUIRED)

    include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

    add_executable(MainGui
        gui_main.c
        view/gui/gui_card_view.c
        view/gui/gui_column_view.c
        view/gui/gui_foundation_view.c
        view/gui/gui_board_view.c
    )

    target_link_libraries(MainGui
            SDL2::SDL2main
            SDL2::SDL2
            SDL2_image::SDL2_image
            backend)
ENDIF()