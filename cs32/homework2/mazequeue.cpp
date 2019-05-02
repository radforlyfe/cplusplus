////
////  mazequeue.cpp
////  homework2

#include<iostream>
#include<queue>

class Coord
{
public:
    Coord(int rr, int cc): m_r(rr), m_c(cc) {}
    Coord() {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

constexpr size_t NUM_ROWS = 10;
constexpr size_t NUM_COLS = 10;

// checks if the maze coordinate is valid to proceed
bool is_valid(char maze[][10], size_t row, size_t col)
{
    if(row < 0 || row >= NUM_ROWS)
        return false;
    if(col < 0 || col >= NUM_COLS)
        return false;
    if(maze[row][col] != '.')
        return false;
    return true;
}

// print grid
void print_grid(char maze[][10])
{
    for(size_t r = 0; r < NUM_ROWS; ++r){
        for(size_t c = 0; c < NUM_COLS; ++c){
            std::cout << maze[r][c] << " ";
        }
        std::cout << std::endl;
    }
}

// print queue:
void print_queue(std::queue<Coord>result){
    for(size_t count = 0; count < 12; ++count){
        std::cout << result.front().r() << ", " << result.front().c() << std::endl;
        result.pop();
    }
}

// Return true if there is a path from (sr,sc) to (er,ec) through the maze;
// return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    std::queue<Coord> coordQueue;
    std::queue<Coord> results;
    coordQueue.push(Coord(sr,sc));
    char visit_count = 'v';
    
    while(!coordQueue.empty()){
        Coord current = coordQueue.front();
        int r = current.r();
        int c = current.c();
        coordQueue.pop();
        results.push(current);
        
        if(maze[r][c] == '.'){                    // mark visited coordinate with count
            maze[r][c] = visit_count;
        }
        if(r == er && c == ec){                   // current = end coordinate
            print_grid(maze);
            print_queue(results);
            return true;
        }
        if(is_valid(maze, r - 1, c)){                   // moving NORTH
            coordQueue.push(Coord(r - 1, c));
        }
        if(is_valid(maze, r + 1, c)){                   // moving SOUTH
            coordQueue.push(Coord(r + 1, c));
        }
        if(is_valid(maze, r, c + 1)){                   // moving EAST
            coordQueue.push( Coord(r, c + 1) );
        }
        if(is_valid(maze, r, c - 1)){                   // moving WEST
            coordQueue.push( Coord(r, c - 1) );
        }
    }
    return false;
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','.','X','X','.','X','X','X','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    
    if (pathExists(maze, 3,5, 8,8)){
        std::cout << "Solvable!" << std::endl;
    }
    else
        std::cout << "Out of luck!" << std::endl;
}
