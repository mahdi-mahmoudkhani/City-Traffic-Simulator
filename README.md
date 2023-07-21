# City Traffic Simulator

This C++ program simulates the movement of cars in a city with user-defined parameters.

## Usage

1. Compile the code using a C++ compiler.
2. Run the program.
3. Enter the number of cars in the city.
4. Enter the number of squares in the city.
5. Enter the number of four-way intersections in the city.
6. Enter the duration (in seconds) for which you want to see the movement of cars.

The program will then simulate and display the movement of cars in the city for the specified duration.

## Game Rules

The allowed direction for cars to move is from bottom to top in odd columns and from top to bottom in even columns. Similarly, in odd rows from left to right and in even rows from right to left. Cars continue moving in their initial direction unless they reach an intersection or square. Upon reaching an intersection, they must choose one of two possible exit paths. Upon reaching a square, they start rotating clockwise around it and then exit through one of the allowed exit paths.

To prevent cars from getting stuck around edges of map, each end row or column is considered as a four-way intersection where cars can choose one of two possible exit paths based on their row or column number.
To prevent cars from getting stuck around squares, placing one square next to another square is not allowed and this condition is checked by program.
The rows and columns around edges do not contain any squares or four-way intersections (represented by `#`).
Cars never overlap during their movement unless they are going around a square to prevent getting stuck.

## Limitations

- The number of four-way intersections must be less than 50 if there are any squares in the city.
- The number of squares must be less than 50 if there are any four-way intersections in the city.
- The number of cars must be less than 100.

If any of these conditions are not met, the program will ask you to enter the parameters again.

## Dependencies

This program requires the following C++ libraries:
- iostream
- cstdlib
- ctime
- string
- chrono
- thread

## Functions

### mapInitializer

This function takes as input a 2D character array representing the map, an integer representing the number of cars, an integer representing the number of squares, an integer representing the number of four-way intersections, and a pointer to an array of `carsInfo` structures representing information about each car.

It initializes the map by randomly placing squares (represented by `@`) and four-way intersections (represented by `#`) on it. It also initializes each car's position and direction on the map. The size of the generated map is 20x20 cells.

### boardDraw

This function takes as input a 2D character array representing the map, an integer representing the number of cars, and a pointer to an array of `carsInfo` structures representing information about each car.

It clears the screen and displays an updated view of the city map with cars represented by asterisks (`*`).

### gameLogic

This function takes as input a 2D character array representing the map, an integer representing the number of cars, and a pointer to an array of `carsInfo` structures representing information about each car.

It updates each car's position and direction based on its current state and surroundings. It checks if a car is at a square or four-way intersection and updates its direction accordingly. It also checks if a car is at an edge of the map and updates its direction accordingly.

### isAroundSquare

This function takes as input a 2D character array representing the map, an integer representing a car's index in the `carsInfo` array, and a pointer to an array of `carsInfo` structures representing information about each car.

It checks if a car is around a square (represented by `@`) on the map and updates its state accordingly. If it is around a square, it sets its `aroundSquare` flag to true and updates its direction to go around it.

### carsDirection

This function takes as input an integer representing a car's index in the `carsInfo` array and a pointer to an array of `carsInfo` structures representing information about each car.

It randomly sets a car's initial direction based on its position on the map.