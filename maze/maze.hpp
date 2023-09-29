#include "../ADTs/stack.hpp"
#include "../ADTs/queue.hpp"

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
		void shuffle(int &i, int &j);
		void queueShuffle(int &i, int &j);
		int Split(int i, int j/* , eda::Stack &Stack_splitX, eda::Stack &Stack_splitY */);
		void Return(int &i, int &j, eda::Stack &stackX, eda::Stack &stackY, int topX, int topY);
		void setWall(int i, int j, int value);
		void solveStack(int i0, int j0, int i1, int j1);
		void solveQueue(int i0, int j0, int i1, int j1);
		//TAREA
	};
}