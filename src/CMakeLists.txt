add_executable(Main
    main.c
)

add_library(backend
        model/card.c
        model/deck.c
        model/column.c
        model/foundation_pile.c
        view/column_view.c
)

target_link_libraries(Main PUBLIC backend)

target_include_directories(backend
        PUBLIC
        ../include
)