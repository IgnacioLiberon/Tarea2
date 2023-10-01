#include "maze/maze.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

namespace maze{

const unsigned char Maze::WALL  = '@';
const unsigned char Maze::EMPTY = '-';
const int Maze::NORTH= 0;
const int Maze::SOUTH= 1;
const int Maze::EAST= 2;
const int Maze::WEST= 3;
Maze::Maze(int h, int w):
		height(h),
		width(w),
		grid(nullptr){
	dir[0] = NORTH;
	dir[1] = SOUTH;
	dir[2] = EAST;
	dir[3] = WEST;
	std::srand(time(0));
	generate_maze(h, w);

}

void Maze::reset_maze(int h, int w){
	delete_maze();
	height = h;
	width= w;
	grid = new uchar*[height];
	for (int i = 0; i < height; i++){
		grid[i] = new uchar[width];
		for (int j = 0; j < width; j++){
			grid[i][j] = 1;
		}
	}
}

void Maze::generate_maze(int h, int w){
	reset_maze(h, w);
	visit(0,0);
}

void Maze::delete_maze(){
	if (grid != nullptr){
		for (int i = 0; i < height; i++){
			delete[] grid[i];
		}
		delete[] grid;
	}
}

void Maze::shuffle_dir(){
	for (int i = 0; i < 4; i++){
		int r = std::rand() & 3;
		int aux = dir[r];
		dir[r] = dir[i];
		dir[i] = aux;
	 }
}
bool Maze::inRange(int i, int j){
	return ((i >= 0) && (i< height) && (j >= 0) && (j< width));
}

void Maze::visit(int i, int j){

	int dx  = 0;
	int dy = 0;
	int i_next = 0;
	int j_next = 0;
	grid[i][j] = 0;
	shuffle_dir();
	//std::cout << dir[0] << " " << dir[1] << " " << dir[2] << " "<< dir[3] << std::endl;
	for(int k = 0; k <  4; k++){
		//std::cout << dir[k] << std::endl;
		if (dir[k] == NORTH){
			dy = -1;
			dx = 0;
		}
		else if (dir[k] == SOUTH){
			dy = 1;
			dx = 0;
		}
		else if (dir[k] == EAST){
			dy = 0;
			dx = 1;
		}
		else if (dir[k] == WEST){
			dy = 0;
			dx = -1;
		}
		i_next = i + (dy<<1);
		j_next = j + (dx<<1);
		if (inRange(i_next, j_next) && grid[i_next][j_next] == 1){
			grid[i_next - dy][j_next - dx] = 0;
			visit(i_next, j_next);

		}
	}
}

void Maze::print(){
	char LIMIT = '=';
	std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
	for (int i = 0; i < height; i++){
		std::cout << "|";
		for (int j = 0; j < width; j++){
			if (grid[i][j] == 0) {
				std::cout << EMPTY;
			}
			else {
				std::cout << WALL;
			}
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
}

void Maze::solve_pila(int f1, int c1, int f2, int c2){
	visited = new uchar*[height];
	path = new uchar*[height];
	int dx[4] = {0, 0, 1, -1};
	int dy[4] = {-1, 1, 0, 0};


	for (int i = 0; i < height; i++) {
		visited[i] = new uchar[width];
		path[i] = new uchar[width];
		for (int j = 0; j < width; j++) {
			visited[i][j] = 0;
			path[i][j] = grid[i][j];
		}
	}

	std::stack<std::pair<int, int>> stack;
    stack.push({f1, c1});
    reachedEnd = false;

    while (!stack.empty()) {
        int i = stack.top().first;
        int j = stack.top().second;
        stack.pop();

        if (i == f2 && j == c2) {
            reachedEnd = true;
            break;
        }

        if (!visited[i][j]) {
            visited[i][j] = 1;
            if (path[i][j] != 'X') {
                path[i][j] = 'X';
            }

            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (inRange(ni, nj) && grid[ni][nj] == 0 && !visited[ni][nj]) {
                    stack.push({ni, nj});
                }
            }
        }
    }

	if (!reachedEnd) {
        std::cout << "No hay solución." << std::endl;
    }
}

void Maze::solve_cola(int f1, int c1, int f2, int c2){
	visited = new uchar*[height];
	path = new uchar*[height];
	int dx[4] = {0, 0, 1, -1};
	int dy[4] = {-1, 1, 0, 0};


	for (int i = 0; i < height; i++) {
		visited[i] = new uchar[width];
		path[i] = new uchar[width];
		for (int j = 0; j < width; j++) {
			visited[i][j] = 0;
			path[i][j] = grid[i][j];
		}
	}

	std::queue<std::pair<int, int>> queue;
    queue.push({f1, c1});
    reachedEnd = false;

	while (!queue.empty()) {
        int i = queue.front().first;
        int j = queue.front().second;
        queue.pop();

        if (i == f2 && j == c2) {
            reachedEnd = true;
            break;
        }

        if (!visited[i][j]) {
            visited[i][j] = 1;
            if (path[i][j] != 'X') {
                path[i][j] = 'X';
            }

            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (inRange(ni, nj) && grid[ni][nj] == 0 && !visited[ni][nj]) {
                    queue.push({ni, nj});
                }
            }
        }
    }

	if (!reachedEnd) {
        std::cout << "No hay solución." << std::endl;
    }
}

void Maze::print_path() {
    char LIMIT = '=';
    std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
    std::cout << " ";
    for (int j = 0; j < width; j++) {
        std::cout << LIMIT;
    }
    std::cout << " ";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        std::cout << "|";
        for (int j = 0; j < width; j++) {
            if (path[i][j] == 'X') {
                std::cout << 'X';
            } else {
                std::cout << (grid[i][j] == 0 ? EMPTY : WALL);
            }
        }
        std::cout << "|";
        std::cout << std::endl;
    }

    std::cout << " ";
    for (int j = 0; j < width; j++) {
        std::cout << LIMIT;
    }
    std::cout << " ";
    std::cout << std::endl;
}

}
