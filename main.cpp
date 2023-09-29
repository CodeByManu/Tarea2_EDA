#include "maze/maze.hpp"
#include "ADTs/stack.hpp"

using namespace std;

int main(){
	maze::Maze maze(21,21);

	maze.print();
	maze.solveStack(0,0,20,20);

	return 0;
}