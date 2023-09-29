#include "maze/maze.hpp"
#include "ADTs/stack.hpp"

using namespace std;

int main(){
	maze::Maze maze(21,21);

	maze.print();
	maze.solveStack();

	return 0;
}