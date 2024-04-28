add_executable(Main
    main.c
)

add_library(backend
        model/card.c
        model/deck.c
        model/column.c
        model/foundation_pile.c
        view/terminal/column_view.c
        view/terminal/terminal_style.c
        view/terminal/command_parser.c
        controller/handle_commands.c
        controller/handle_game_moves.c
        controller/game_state.c
        controller/string_utils.c
)

target_link_libraries(Main PUBLIC backend)

target_include_directories(backend
        PUBLIC
        ../include
)