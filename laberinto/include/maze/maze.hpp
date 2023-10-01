/**
 * Classe Maze
 */
#include <vector>

namespace maze {
	typedef unsigned char uchar;


	class Maze{
	private:
		uchar**  grid;
		uchar** visited;
    	uchar** path;
    	bool reachedEnd;
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
		void solve_pila(int f1, int c1, int f2, int c2);
		void solve_cola(int f1, int c1, int f2, int c2);
		void print_path();
	};
}
