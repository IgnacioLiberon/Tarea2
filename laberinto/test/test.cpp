#include <iostream>
#include "maze/maze.hpp"
int main(int nargs, char** vargs){
	maze::Maze laberinto(21,21);
	laberinto.print();

	laberinto.solve_cola(0,0,20,20);

    laberinto.print_path();

    //laberinto.solve_cola(0,0,20,20);

    //laberinto.print_path();

	return 0;
}
