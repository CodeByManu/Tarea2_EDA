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
			else if (grid[i][j] == 1)
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

void Maze::queueShuffle(int &i, int &j) {
	shuffle_dir();


}

int Maze::Split(int i, int j/* , eda::Stack &stack_splitX, eda::Stack &stack_splitY */){
	int counter = 0;
	if (getBox(i + 1, j)) counter ++;
	if (getBox(i - 1, j)) counter ++;
	if (getBox(i, j + 1)) counter ++;
	if (getBox(i, j - 1)) counter ++;

	// if (counter > 1){
	// 	stack_splitX.push(i);
	// 	stack_splitY.push(j);
	// }
	return counter;
}

// ESTETICA
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

void Maze::solveStack(int i0, int j0, int i1, int j1) {		//0 es incio, 1 es fin
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

	stack_splitX.push(i0);
	stack_splitY.push(j0);

	// NECESARIO?
	if(grid[i0][j0] == 1 || grid[i1][j1] == 1) {
		std::cout << "No hay camino posible..." << std::endl;
		exit(0);
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
				setWall(iAux, jAux, 1);
			}

			if (options > 1) {
				iAux = i;
				jAux = j;
				stack_splitX.push(i);
				stack_splitY.push(j);
			}

			shuffle(i, j);

			// system("clear");
			system("cls");
			if(i == i1 && j == j1) {
				finished = true;
				setWall(i, j, 3);
			}
			print();
		}
	}
}

// void Maze::solveQueue(int i0, int j0, int i1, int j1) {
// 	eda::Queue queueX;
// 	eda::Queue queueY;
// 	bool finished = false;
// 	int i = i0;
// 	int j = j0;
// 	int iAux;
// 	int jAux;
// 	int options;

// 	if(grid[i0][j0] == 1 || grid[i1][j1] == 1) {
// 		std::cout << "No hay camino posible..." << std::endl;
// 		exit(0);
// 	}

// 	while (!finished) {
// 		queueX.push(i);
// 		queueY.push(j);
// 		iAux = i;
// 		jAux = j;
// 		// shuffle(i, j);
// 		PossiblePath(i, j, queueX, queueY);
// 		i = queueX.top() -> getData();
// 		j = queueY.top() -> getData();
// 		queueX.pop();
// 		queueY.pop();
// 		if (i1 == i && j1 == j){
// 			finished = true;
// 			setWall(i, j, 3);
// 		}
// 		print();
// 	}
// }

void Maze::solveQueue(int i0, int j0, int i1, int j1) {
	eda::Queue queueX;
	eda::Queue queueY;
	eda::Queue queue_splitX;
	eda::Queue queue_splitY;
	bool finished = false;
	int i = i0;
	int j = j0;
	int iAux;
	int jAux;
	int options;

	int is;
	int js;

	if(grid[i0][j0] == 1 || grid[i1][j1] == 1) {
		std::cout << "No hay camino posible..." << std::endl;
		exit(0);
	}

	queueX.push(i);
	queueY.push(j);

	while (!finished) {
		options = Split(i, j);
		iAux = i; jAux = j;

		// if (options == 0) {
			// setWall(is, js, 1);
			// i = queue_splitX.top()->getData();
			// j = queue_splitY.top()->getData();
			// i = is;
			// j = js;
			// queueX.pop();
			// queueY.pop();
		// }

		if (options > 1) {
			// queue_splitX.push(i);
			// queue_splitY.push(j);

			// setWall(i, j, 1);
			shuffle(i, j);
			// is = i;
			// js = j;
			queueX.push(i);
			queueY.push(j);
			i = iAux; j = jAux;
		}

		shuffle(i, j);

		queueX.push(i);
		queueY.push(j);

		queueX.pop();
		queueY.pop();

		i = queueX.top()->getData();
		j = queueY.top()->getData();

		system("cls");
		if (i == i1 && j == j1) {
			finished = true;
			setWall(i, j, 3);
		}
		print();
		// usleep(50000);
	}

}
//TAREA

}