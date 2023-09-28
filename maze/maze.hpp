#include "../ADT's/stack.hpp"
#include <stack>

namespace maze {
	typedef unsigned char uchar;


	class Maze{
	private:
		uchar**  grid;
		int width;
		int height;
		int dir[4];
		void shuffle_dir();
		void delete_maze();
		void visit(int i, int j);
	public:
		static const unsigned char WALL;
		static const unsigned char EMPTY;
		static const int NORTH;
		static const int SOUTH;
		static const int EAST;
		static const int WEST;
		Maze(int h, int  w);
		void generate_maze(int h, int w);
		void reset_maze(int h, int w);
		bool inRange(int i, int j);
		void print();
		//TAREA
		bool getBox(int i, int j);
		void shuffle(int &i, int &j, std::stack<int> &stackX, std::stack<int> &stackY);
		int Split(int i, int j, std::stack<int> &Stack_splitX, std::stack<int> &Stack_splitY);
		void Return(int &i, int &j, std::stack<int> &stackX, std::stack<int> &stackY, int topX, int topY);
		void setWall(int i, int j, int value);
		//TAREA

	};
}