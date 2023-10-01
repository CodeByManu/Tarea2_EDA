#include <string>
#include <iostream>
#include <chrono>

#include "maze/maze.hpp"
#include "ADTs/stack.hpp"

using namespace std;



int main(int argv, char* argc[]){
	int x0 = atoi(argc[1]);
	int xf = atoi(argc[2]);

	maze::Maze maze(21,21);
	int** arrStack = new int*[21];
	int** arrQueue = new int*[21];

	// maze.print();
	// cout << "\nEnter para continuar" << endl;
	// cin.get();
	chrono::steady_clock::time_point beginStack = chrono::steady_clock::now();
	arrStack = maze.solveStack(0, x0, 20, xf);
	chrono::steady_clock::time_point endStack = chrono::steady_clock::now();
	// system("clear");
	// maze.print();
	maze.clean();
	// system("clear");
	// maze.print();
	chrono::steady_clock::time_point beginQueue = chrono::steady_clock::now();
	arrQueue = maze.solveQueue(0, x0, 20, xf);
	chrono::steady_clock::time_point endQueue = chrono::steady_clock::now();
	// system("clear");
	// maze.print();
	cout << "Stack: " << (chrono::duration_cast<chrono::milliseconds> (endStack - beginStack).count()) << endl;
	cout << "Queue: " << (chrono::duration_cast<chrono::milliseconds> (endQueue - beginQueue).count()) << endl;
	
	for (int i = 0; i < maze::Maze::YMAX; i ++) delete arrQueue[i];
	delete[] arrStack;
	for (int i = 0; i < maze::Maze::YMAX; i ++) delete arrQueue[i];
	delete[] arrQueue;

	return 0;
}