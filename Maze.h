// Maze.h
// Mark F. Russo, PhD
// The College of New Jersey
#include <iostream>
#include <fstream>
#include <stdexcept>

// Maze class
class Maze {
private:
    int nrows, ncols;           // Maze dimensions
    char** maze;                // . = open, # = wall, O = visited

public:
    // Constructor
    Maze(std::string filename) {
        std::ifstream fin(filename);

        // Check that file is found and throw exception if not.
        if (!fin.is_open()) throw std::runtime_error(filename + " not found");
        
        // Read maze dimensions
        fin >> nrows;
        fin >> ncols;

        // Create dynamic 2D array of arrays
        maze = new char*[nrows];
        for (int r = 0; r < nrows; ++r) maze[r] = new char[ncols];
        
        // Fill maze with ints
        for (int r=0; r<nrows; r++) {
            for (int c=0; c<ncols; c++) {
                fin >> maze[r][c];
            }
        }
    }

    // Destructor to deallocate memory
    ~Maze() {
        // Deallocate row arrays
        for (int r = 0; r < nrows; ++r) delete[] maze[r];

        // Deallocate outer array holding row pointers
        delete[] maze;
    }
    // Getters
    int getNRows() { return nrows; }    // Get the number of Maze rows
    int getNCols() { return ncols; }    // Get the number of Maze columns

    bool isWall(int r, int c) {         // Check if a Maze location is a wall.
        if (!inBounds(r, c)) throw std::runtime_error("Invalid maze coordinates");
        return maze[r][c] == '#';
    }

    bool isVisited(int r, int c) {      // Check if a Maze location has been visited.
        if (!inBounds(r, c)) throw std::runtime_error("Invalid maze coordinates");
        return maze[r][c] == 'O';
    }
    
    void visit(int r, int c) {          // Mark a Maze location as visited.
        if (!inBounds(r, c)) throw std::runtime_error("Invalid maze coordinates");
        if (maze[r][c] == '#') throw std::runtime_error("Cannot visit a maze wall");
        maze[r][c] = 'O';
    }
    
    void unvisit(int r, int c) {        // Unmark a Maze location as not visited
        if (!inBounds(r, c)) throw std::runtime_error("Invalid maze coordinates");
        if (maze[r][c] == '#') throw std::runtime_error("Cannot unvisit a maze wall");
        maze[r][c] = '.';
    }
    
    bool inBounds(int r, int c) {       // Check if Maze location is within bounds
        return (r >= 0 && r < this->nrows && c >= 0 && c < this->ncols);
    }

    // Friend declaration for the overloaded operator<<
    friend std::ostream& operator<<(std::ostream& os, const Maze& m);
};

// Overloaded insertion operator definition
std::ostream& operator<<(std::ostream& os, const Maze& m) {
    for (int r=0; r<m.nrows; r++) {
        for (int c = 0; c<m.ncols; c++) os << m.maze[r][c] << " ";
        os << std::endl;
    }
    return os; // Allow chaining
}
