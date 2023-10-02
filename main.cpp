#include <string>
#include <iostream>
#include <chrono>

#include "maze/maze.hpp"
#include "ADTs/stack.hpp"

using namespace std;

int main(int argc, char* argv[]){
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " x0 xf" << endl;
		return 1;
	}

	int x0 = atoi(argv[1]);
	int xf = atoi(argv[2]);
	maze::Maze maze(xf+1, xf+1);
	double tStack = 0;
	double tQueue = 0;
	int count = 0;

	// for (int i = 0; i < 50; i++) {
		int** arrStack = nullptr;
		int** arrQueue = nullptr;
		maze.print();

		// cout << "\nEnter para continuar" << endl;
		// cin.get();

		// chrono::steady_clock::time_point stackBegin = chrono::steady_clock::now();
		arrStack = maze.solveStack(x0, x0, xf, xf);
		// chrono::steady_clock::time_point stackEnd = chrono::steady_clock::now();
		// chrono::duration<float, milli> stackDuration = stackEnd - stackBegin;
		// tStack += stackDuration.count();

		// system("clear");
		// maze.print();
		maze.clean();
		system("clear");
		maze.print();

		// chrono::steady_clock::time_point queueBegin = chrono::steady_clock::now();
		arrQueue = maze.solveQueue(x0, x0, xf, xf);
		// chrono::steady_clock::time_point queueEnd = chrono::steady_clock::now();
		// chrono::duration<float, milli> queueDuration = queueEnd - queueBegin;
		// tQueue += queueDuration.count();

		// system("clear");
		// maze.print();
		// if (arrStack && arrQueue) count++;

		// std::cout << /*i <<*/ ") Stack: " << stackDuration.count() << " [ms]" << endl;
		// std::cout << /*i <<*/ ") Queue: " << queueDuration.count() << " [ms]" << endl;


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

		// while (arrStack[i]) {
		// 	cout << arrStack[i][1] << ", " << arrStack[i][0] << endl;
		// 	i++;
		// }
		
		delete[] arrStack;
		delete[] arrQueue;

		// maze.generate_maze(xf+1, xf+1);
	// }

	// std::cout << "Stack: " << tStack/count << endl;
	// std::cout << "Queue: " << tQueue/count << endl;

	return 0;
}