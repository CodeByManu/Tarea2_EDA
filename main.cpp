#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "maze/maze.hpp"
#include "ADTs/stack.hpp"

using namespace std;

int main(){
	maze::Maze laberinto(21,21);
	eda::Stack stackX;
	eda::Stack stackY;
	eda::Stack stack_splitX;
	eda::Stack stack_splitY;
	bool finished = false;
	int inicioX = 0;
	int inicioY = 0;
	int i = inicioX;
	int j = inicioY;
	int iAux;
	int jAux;
	laberinto.print();

//Solucion con Stack
	int possibilities;
	while (!finished) {
		if (laberinto.getBox(i,j)){
			stackX.push(i);
			stackY.push(j);
			possibilities = laberinto.Split(i, j, stack_splitX, stack_splitY);
			if (possibilities == 0) {
				laberinto.Return(i, j, stackX, stackY, stack_splitX.top() -> getData(), stack_splitY.top() -> getData());
				stack_splitX.pop();
				stack_splitY.pop();
				laberinto.setWall(iAux, jAux, 1);
			}
			laberinto.shuffle(i, j, stackX, stackY);

			if (possibilities > 1) {
				iAux = i;
				jAux = j;
			}

			system("cls");
			if(i == 20 && j == 20){
				finished = true;
				laberinto.setWall(i, j, 3);
			}
			laberinto.print();
			// usleep(50000);
		}
	}


	return 0;
}