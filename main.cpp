#include <string>
#include <iostream>

#include "maze/maze.hpp"
#include "ADTs/stack.hpp"

using namespace std;

int main(int argv, char* argc[]){
	int x0 = atoi(argc[1]);
	int xf = atoi(argc[2]) - 1;

	maze::Maze maze(21,21);
	// int init [4] = {0, 0, 20, 20};
	// string coord[4] = {"x0", "x1", "y0", "y1"};
	int** arr = new int*[21];

	maze.print();
	cout << "\nEnter para continuar" << endl;
	cin.get();
	// AGREGAR LOOP PARA VERIFICAR COORDENADA CORRECTA (?)
	// cout << endl << "Ingrese coordenadas de partida (x0, y0), y de destino (x1, y1)" << endl;
	// for (int i = 0; i < 4; i++) {
	// 	cout << coord[i] << ": ";
	// 	cin >> init[i];
	// }
	// cout << endl;

	arr = maze.solveStack(0, x0, 20, xf);
	maze.clean();
	cout << "\nEnter para continuar" << endl;
	cin.get();
	maze.print();
	cout << "\nEnter para continuar" << endl;
	cin.get();
	arr = maze.solveQueue(0, x0, 20, xf);
	// maze.print();
	// cout << "[test main]" << endl;
	// for (int index = 0; index < maze.solLength; index++) {
	// 	cout << arr[index][0] << ", " << arr[index][1] << endl;
	// 	index++;
	// }
	for (int i = 0; i < maze::Maze::YMAX; i ++) delete arr[i];
	delete[] arr;

	return 0;
}