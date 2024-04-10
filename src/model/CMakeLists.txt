add_library(Model
        card.c
        column.c
        deck.c
        foundation_pile.c
)

target_include_directories(
        Model
        PUBLIC
        ../../include/model
)