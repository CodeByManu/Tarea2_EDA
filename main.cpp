#include <string>
#include <iostream>
#include <chrono>

#include "maze/maze.hpp"

using namespace std;

int main(int argc, char* argv[]){
	if (argc != 4) {
		cerr << "Usage: " << argv[0] << " n x0 xf" << endl;
		return 1;
	}

	int n = atoi(argv[1]);
	int x0 = atoi(argv[2]);
	int xf = atoi(argv[3]);
	maze::Maze maze(xf+1, xf+1);

	int** arrStack = nullptr;
	int** arrQueue = nullptr;
	maze.print();

	arrStack = maze.solveStack(x0, x0, xf, xf);

	maze.clean();
	system("clear");
	maze.print();

	arrQueue = maze.solveQueue(x0, x0, xf, xf);

	cout << "Solucion posible con stack: " << endl;
	for (int i = maze.stackSolLength - 1; i >=0 ; i--) {
		if (!arrStack[i]) continue;
		cout << " (" << arrStack[i][1] << ", " << arrStack[i][0] << "), \t";
	}

	cout << "\n\nSolucion posible con queue: " << endl;
	for (int i = 0; i < maze.queueSolLength ; i++) {
		if (!arrQueue[i]) continue;
		cout << " (" << arrQueue[i][1] << ", " << arrQueue[i][0] << "), \t";
	}
	cout << endl;

	delete[] arrStack;
	delete[] arrQueue;

	return 0;
}