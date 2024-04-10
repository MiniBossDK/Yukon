add_library(core
    add.c
    subtract.c
        card.c
        deck.c
        foundation_pile.c
        column.c
        include/core/controller.cpp
        controller.c
        include/core/controller.h
)
target_include_directories(core PUBLIC include)