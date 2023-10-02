#include "maze.hpp"
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <iostream>

namespace maze{

const unsigned char Maze::WALL  = '@';
const unsigned char Maze::EMPTY = ' ';
const int Maze::NORTH= 0;
const int Maze::SOUTH= 1;
const int Maze::EAST= 2;
const int Maze::WEST= 3;
// TAREA
int Maze::XMAX = 21;
int Maze::YMAX = 21;
// static int** arr1 = new int*[YMAX];
// TAREA

struct Maze::cell {
	int x;
	int y;

	cell (int xcord, int ycord) : x(xcord), y(ycord) {}
	cell () : x(), y() {}
};

Maze::Maze(int h, int w):
		height(h),
		width(w),
		grid(nullptr){
	dir[0] = NORTH;
	dir[1] = SOUTH;
	dir[2] = EAST;
	dir[3] = WEST;
	std::srand(time(0));
	generate_maze(h, w);
	// TAREA
	XMAX = height;
	YMAX = width;
	// TAREA
}

void Maze::reset_maze(int h, int w){
	delete_maze();
	height = h;
	width = w;
	grid = new uchar*[height];
	for (int i = 0; i < height; i++){
		grid[i] = new uchar[width];
		for (int j = 0; j < width; j++){
			grid[i][j] = 1;
		}
	}
}

void Maze::generate_maze(int h, int w){
	reset_maze(h, w);
	visit(0,0);
}

void Maze::delete_maze(){
	if (grid != nullptr){
		for (int i = 0; i < height; i++){
			delete[] grid[i];
		}
		delete[] grid;
	}
}

void Maze::shuffle_dir(){
	for (int i = 0; i < 4; i++){
		int r = std::rand() & 3;
		int aux = dir[r];
		dir[r] = dir[i];
		dir[i] = aux;
	 }
}

bool Maze::inRange(int i, int j){
	return ((i >= 0) && (i< height) && (j >= 0) && (j< width));
}

void Maze::visit(int i, int j){

	int dx  = 0;
	int dy = 0;
	int i_next = 0;
	int j_next = 0;
	grid[i][j] = 0;
	shuffle_dir();
	//std::cout << dir[0] << " " << dir[1] << " " << dir[2] << " "<< dir[3] << std::endl;
	for(int k = 0; k <  4; k++){
		//std::cout << dir[k] << std::endl;
		if (dir[k] == NORTH){
			dy = -1;
			dx = 0;
		}
		else if (dir[k] == SOUTH){
			dy = 1;
			dx = 0;
		}
		else if (dir[k] == EAST){
			dy = 0;
			dx = 1;
		}
		else if (dir[k] == WEST){
			dy = 0;
			dx = -1;
		}
		i_next = i + (dy<<1);
		j_next = j + (dx<<1);
		if (inRange(i_next, j_next) && grid[i_next][j_next] == 1){
			grid[i_next - dy][j_next - dx] = 0;
			visit(i_next, j_next);
		}
	}
}

void Maze::print(){
	char LIMIT = '=';
	std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
	for (int i = 0; i < height; i++){
		std::cout << "|";
		for (int j = 0; j < width; j++){
			if (grid[i][j] == 0 || grid[i][j] == 4) {
				std::cout << "\x1b[0m";
				std::cout << EMPTY;
			}
			else if (grid[i][j] == 1 || grid[i][j] == 5)
				std::cout << WALL;
			else if (grid[i][j] == 2)
				std::cout << "\x1b[46m\x1b[37m" << " " << "\x1b[0m";
			else if (grid[i][j] == 3)
				std::cout << "\x1b[41m\x1b[37m" << " " << "\x1b[0m";
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
}

//TAREA
bool Maze::getBox(int i, int j){	//Retorna true si la casilla esta vacia, o sea, es accedible
	if (inRange(i, j)){
		return grid[i][j] == 0;
	}
	return false;
}

void Maze::shuffle(int &i, int &j){
	shuffle_dir();
	
	if ((!getBox(i - 1, j) && !getBox(i + 1, j) && !getBox(i, j - 1) && !getBox(i, j + 1))) {
		return;
	}
	if (dir[0] == NORTH && getBox(i - 1, j)) {
		grid[i][j] = 2;
		i--;
	}
	else if (dir[0] == SOUTH && getBox(i + 1, j)) {
		grid[i][j] = 2;
		i++;
	}
	else if (dir[0] == EAST && getBox(i, j + 1)) {
		grid[i][j] = 2;
		j++;
	}
	else if (dir[0] == WEST && getBox(i, j - 1)) {
		grid[i][j] = 2;
		j--;
	} else 
		shuffle(i, j);
}

// BORRAR (?)
void Maze::PossiblePath(int i, int j, eda::Queue &qX, eda::Queue &qY){
	if (getBox(i + 1, j)){
		qX.push(i + 1);
		qY.push(j);
	}
	if (getBox(i - 1, j)){
		qX.push(i - 1);
		qY.push(j);
	}
	if (getBox(i, j + 1)){
		qX.push(i);
		qY.push(j + 1);
	}
	if (getBox(i, j - 1)){
		qX.push(i);
		qY.push(j - 1);
	}
	grid[i][j] = 2;
}

int Maze::Split(int i, int j){
	int counter = 0;
	if (getBox(i + 1, j)) counter ++;
	if (getBox(i - 1, j)) counter ++;
	if (getBox(i, j + 1)) counter ++;
	if (getBox(i, j - 1)) counter ++;

	return counter;
}

void Maze::Return(int &i, int &j, eda::Stack &stackX, eda::Stack &stackY, int topX, int topY){
	i = topX;
	j = topY;
	
	while(stackX.top() -> getData() != topX || stackY.top() -> getData() != topY) {
		stackX.pop();
		stackY.pop();
		grid[stackX.top() -> getData()][stackY.top() -> getData()] = 4;
	}
}

void Maze::setWall(int i, int j, int value){
	grid[i][j] = value;
}

int** Maze::resize(int** &array, int &n, int expand) {
	int** arr = new int*[n*expand];
	for (int i = 0; i < n; i++) {
		arr[i] = array[i];
	}
	delete[] array;
	n *= expand;
	return arr;
}

void Maze::clean() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((grid[i][j] == 2) || (grid[i][j] == 3) || (grid[i][j] == 4)) grid[i][j] = 0;
			else if (grid[i][j] == 5) grid[i][j] = 1;
		}
	}
}

int** Maze::solveStack(int i0, int j0, int i1, int j1) {		//0 es incio, 1 es fin
	eda::Stack stackX;
	eda::Stack stackY;
	eda::Stack stack_splitX;
	eda::Stack stack_splitY;
	bool finished = false;
	int i = i0;
	int j = j0;
	int iAux;
	int jAux;
	int options;
	int** arr = new int*[YMAX];
	stackSolLength = 0;

	stack_splitX.push(i0);
	stack_splitY.push(j0);

	// NECESARIO?
	if(grid[i0][j0] == 1 || grid[i1][j1] == 1) {
		std::cout << "No hay camino posible..." << std::endl;
		return nullptr;
	}

	while (!finished) {
		if (getBox(i,j)){
			stackX.push(i);
			stackY.push(j);
			options = Split(i, j);

			if (options == 0) {
				Return(i, j, stackX, stackY, stack_splitX.top() -> getData(), stack_splitY.top() -> getData());
				stack_splitX.pop();
				stack_splitY.pop();
				setWall(iAux, jAux, 5);
			}

			if (options > 1) {
				iAux = i;
				jAux = j;
				stack_splitX.push(i);
				stack_splitY.push(j);
			}

			shuffle(i, j);

			if(i == i1 && j == j1) {
				finished = true;
				setWall(i, j, 3);
			}
			system("clear");
			print();
			usleep(50000);
		}
	}

	// NO ES LA MEJOR MANERA PERO POR MIENTRAS
	// NOSE SI SE PUEDEN USAR VECTORES, POR MIENTRAS HACIENDO RESIZE A ARRAY
	while(!stackX.isEmpty()) {
		int xy[2] = {stackX.top()->getData(), stackY.top()->getData()};
		arr[stackSolLength] = new int[2];
		arr[stackSolLength][0] = xy[0];
		arr[stackSolLength][1] = xy[1];
		stackX.pop();
		stackY.pop();
		stackSolLength++;
		if (stackSolLength == YMAX) {
			arr = resize(arr, YMAX, 2);
		}
	}
	return arr;
}

int** Maze::solveQueue(int i0, int j0, int i1, int j1) {
	eda::Queue queueX;
	eda::Queue queueY;
	eda::Queue returnQueueX;
	eda::Queue returnQueueY;
	bool finished = false;
	int i = i0;
	int j = j0;
	int iAux;
	int jAux;
	int options;
	int** arr = new int*[YMAX];
	queueSolLength = 0;

	if(grid[i0][j0] == 1 || grid[i1][j1] == 1) {
		std::cout << "No hay camino posible..." << std::endl;
		return nullptr;
	}

	queueX.push(i); returnQueueX.push(i);
	queueY.push(j); returnQueueY.push(j);

	while (!finished) {
		options = Split(i, j);
		
		if (options > 1) {
			iAux = i; jAux = j;
			queueX.push(i); returnQueueX.push(i);
			queueY.push(j); returnQueueY.push(j);
			shuffle(i, j);
			queueX.push(i); returnQueueX.push(i);
			queueY.push(j); returnQueueY.push(j);
			i = iAux; j = jAux;
		}
		shuffle(i, j);

		queueX.push(i); returnQueueX.push(i);
		queueY.push(j); returnQueueY.push(j);

		queueX.pop();
		queueY.pop();

		i = queueX.top()->getData();
		j = queueY.top()->getData();

		if (i == i1 && j == j1) {
			finished = true;
			setWall(i, j, 3);
		}
		system("clear");
		print();
		usleep(10000);
	}


	while(!returnQueueX.isEmpty()) {
		int xy[2] = {returnQueueX.top()->getData(), returnQueueY.top()->getData()}; // ESTAN DADOS VUELTA
		arr[queueSolLength] = new int[2];
		arr[queueSolLength][0] = xy[0];
		arr[queueSolLength][1] = xy[1];
		returnQueueX.pop();
		returnQueueY.pop();
		queueSolLength++;
		if (queueSolLength == YMAX) {
			arr = resize(arr, YMAX, 2);
		}
	}
	return arr;
}
//TAREA

}