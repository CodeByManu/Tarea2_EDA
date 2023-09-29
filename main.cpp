#include <string>
#include <iostream>

#include "maze/maze.hpp"
#include "ADTs/stack.hpp"

using namespace std;

int main(){
	maze::Maze maze(21,21);
	int init [4] = {0, 0, 20, 20};
	string coord[4] = {"x0", "x1", "y0", "y1"};

	maze.print();

	// AGREGAR LOOP PARA VERIFICAR COORDENADA CORRECTA (?)
	// cout << endl << "Ingrese coordenadas de partida (x0, y0), y de destino (x1, y1)" << endl;
	// for (int i = 0; i < 4; i++) {
	// 	cout << coord[i] << ": ";
	// 	cin >> init[i];
	// }
	// cout << endl;

	// maze.solveStack(0,0,20,20);
	maze.solveQueue(0,0,20,20);

	return 0;
}