#include <string>
#include <iostream>

#include "maze/maze.hpp"
#include "ADTs/stack.hpp"

using namespace std;

int main(){
	maze::Maze maze(21,21);
	// int xmax = maze.XMAX;
	// int ymax = maze.YMAX;

	int init [4] = {0, 0, 20, 20};
	string coord[4] = {"x0", "x1", "y0", "y1"};
	int** arr = new int*[21];

	maze.print();
	// AGREGAR LOOP PARA VERIFICAR COORDENADA CORRECTA (?)
	// cout << endl << "Ingrese coordenadas de partida (x0, y0), y de destino (x1, y1)" << endl;
	// for (int i = 0; i < 4; i++) {
	// 	cout << coord[i] << ": ";
	// 	cin >> init[i];
	// }
	// cout << endl;

	// arr = maze.solveStack(0,0,20,20);
	arr = maze.solveQueue(0,0,20,20);
	// maze.print();
	// cout << "[test main]" << endl;
	for (int index = 0; index < maze.solLength; index++) {
		cout << arr[index][0] << ", " << arr[index][1] << endl;
		index++;
	}
	for (int i = 0; i < maze::Maze::YMAX; i ++) delete arr[i];
	delete[] arr;

	return 0;
}