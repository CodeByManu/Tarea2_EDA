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

	// int i = 0;
	// maze::Maze maze1(21,21), maze2(21,21), maze3(21,21), maze4(21,21), maze5(21,21);

	// maze::Maze iter[] = {
	// 	maze1,
	// 	maze2,
	// 	maze3,
	// 	maze4,
	// 	maze5
	// 	};

// maze1.print();
// maze2.print();
	// for (maze::Maze maze: iter) {
		maze.print();
		int** arrStack = nullptr;
		int** arrQueue = nullptr;

		// maze.print();
		// cout << "\nEnter para continuar" << endl;
		// cin.get();
		chrono::steady_clock::time_point stackBegin = chrono::steady_clock::now();
		arrStack = maze.solveStack(x0, x0, xf, xf);
		chrono::steady_clock::time_point stackEnd = chrono::steady_clock::now();
		// system("clear");
		// maze.print();
		maze.clean();
		// system("clear");
		// maze.print();
		chrono::steady_clock::time_point queueBegin = chrono::steady_clock::now();
		arrQueue = maze.solveQueue(x0, x0, xf, xf);
		chrono::steady_clock::time_point queueEnd = chrono::steady_clock::now();
		// system("clear");
		// maze.print();

		// cout << "Stack: " << (chrono::duration_cast<chrono::milliseconds> (stackEnd - stackBegin).count()) << endl;
		// cout << "Queue: " << (chrono::duration_cast<chrono::milliseconds> (queueEnd - queueBegin).count()) << endl;
		
		chrono::duration<float, milli> stackDuration = stackEnd - stackBegin;
		chrono::duration<float, milli> queueDuration = queueEnd - queueBegin;

		std::cout << /*i <<*/ ") Stack: " << stackDuration.count() << " [ms]" << endl;
		std::cout << /*i <<*/ ") Queue: " << queueDuration.count() << " [ms]" << endl;
		
		// for (int i = 0; i < maze::Maze::YMAX; i ++) delete arrQueue[i];
		delete[] arrStack;
		// for (int i = 0; i < maze::Maze::YMAX; i ++) delete arrQueue[i];
		delete[] arrQueue;
		// i++;
	// }

	return 0;
}