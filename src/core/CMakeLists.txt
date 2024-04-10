add_library(core
    add.c
    subtract.c
        card.c
        deck.c
        foundation_pile.c
        column.c
)
target_include_directories(core PUBLIC include)