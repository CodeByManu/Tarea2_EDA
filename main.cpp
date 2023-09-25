#include <iostream>
#include "maze/maze.hpp"
#include "ADT's/stack.hpp"

using namespace std;

int main(int nargs, char** vargs){
	maze::Maze laberinto(21,21);
	eda::Stack stackX;
	eda::Stack stackY;
	bool finished = false;
	int i = 0;
	int j = 0;

	laberinto.print();

//Solucion con Stack
	while (!finished) {
		if (laberinto.getBox(i,j) ){
			stackX.push(i);
			stackY.push(j);
			
		}
	}
	

	return 0;
}