add_library(core
    add.c
    subtract.c
        card.c
        deck.c
)

target_include_directories(core PUBLIC include)