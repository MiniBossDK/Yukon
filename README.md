# Yukon

# 

# How to run the project
1. Clone the repository
2. Open the terminal and navigate to the project directory
3. Run the following command in the terminal
```
cmake -S . -B Build
cmake --build Build
```

# Testing
This project uses the Google Test framework for unit testing. The tests are located in the `test` directory.

## How to run the tests
1. Build the project using the instructions above
2. Go to the build directory, ``Build/``, and run the following commands
```
cmake --build .
ctest
```




