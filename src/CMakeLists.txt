if (NOT USER_INTERFACE)
    set(MAIN_TARGET Main)
    add_executable(Main
        main.c
    )

    add_library(view_terminal
        view/terminal/column_view.c
        view/terminal/terminal_style.c
    )
    target_link_libraries(${MAIN_TARGET} PUBLIC backend)
ENDIF()

IF (USER_INTERFACE)
    set(MAIN_TARGET MainGui)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

    find_package(SDL2_image REQUIRED CONFIG COMPONENTS SDL2_image)


    add_executable(MainGui
        gui_main.c
            lib/SDL2_rotozoom.c
    )

    target_link_libraries(MainGui
            SDL2::SDL2main
            SDL2::SDL2
            SDL2_image::SDL2_image
            backend)
ENDIF()

add_library(backend
        model/card.c
        model/deck.c
        model/column.c
        model/foundation_pile.c
)

target_include_directories(backend
        PUBLIC
        ../include
)