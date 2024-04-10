add_executable(Main
    main.c
)

add_subdirectory(model)
add_subdirectory(controller)

target_link_libraries(Main PRIVATE Model)
target_link_libraries(Main PRIVATE Controller)