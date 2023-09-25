#include <iostream>
#include <stack>
#include "maze/maze.hpp"
#include "ADT's/stack.hpp"

using namespace std;

int main(int nargs, char** vargs){
	maze::Maze laberinto(21,21);
	stack<int> stackX;
	stack<int> stackY;
	stack<int> stack_splitX;
	stack<int> stack_splitY;
	bool finished = false;
	int i = 0;
	int j = 0;
	laberinto.print();

//Solucion con Stack
	int possibilities;
	while (!finished) {
		if (laberinto.getBox(i,j)){
			stackX.push(i);
			stackY.push(j);
			possibilities = laberinto.Split(i, j, stack_splitX, stack_splitY);
			if (possibilities == 0) laberinto.Return(i, j, stackX, stackY, stack_splitX.top(), stack_splitY.top());
			laberinto.shuffle(i, j, stackX, stackY);
			if(i == 20 && j == 20) finished = true;
		}
	}

	laberinto.print();

	return 0;
}