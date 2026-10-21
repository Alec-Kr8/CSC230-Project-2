// Name: Alec Krishnakumar
// Date: 10/09/1025
// Filename: Project2.cpp
// Description: This program uses a class file and methods to create a maze solver that can solve provided mazes.
#include <iostream>
#include "Maze.h"
using namespace std;

// Recrusive depth-first search for a path through a 2D array
bool search(Maze& maze, int r, int c, int targetR, int targetC) {

    // 1. Cannot proceed if (r, c) is out of bounds, a wall, or has already been visited.
    if (!maze.inBounds(r, c) || maze.isWall(r, c) || maze.isVisited(r, c)) {
        // return false
        return false;
    }


    // 2. If we get this far, we can proceed. Mark location as visited.
        maze.visit(r,c);
    // 3. If we've reached our destination. Return true.
        if (r == targetR && c == targetC) {
            return true;
        }
    // 4. Try to search in all four directions. 
    //    Return true if a direction finds the target location. 
    //    Continue searching in next direction if no path found from previous direction.
        if (search(maze, r, c+1, targetR, targetC)) return true; // looks right
        if (search(maze, r, c-1, targetR, targetC)) return true; // looks left
        if (search(maze, r+1, c, targetR, targetC)) return true; // looks up
        if (search(maze, r-1, c, targetR, targetC)) return true; // looks down
    // 5. If we get this far, then there is no path found. 
    //    Unvisit this location and return false.
        maze.unvisit(r, c);
        return false;

}

// Helper method that sets default start search to upper left and default taget to lower right.
bool search(Maze& maze) {
    return search(maze, 0, 0, maze.getNRows()-1, maze.getNCols()-1);
}

// > c++ Project2.cpp -o search
// > .\search maze1.txt
int main(int argc, char* argv[]) {
    string filename(argv[1]);

    // Create a Maze from the given file
    Maze* m = new Maze(filename);

    cout << "Initial Maze config" << endl;
    cout << *m << endl;
    bool found = search(*m);

    if (!found) {
        cout << "Cannot find a path through " << filename << endl;
    } else {
        cout << "Found a path through " << filename << endl;
        cout << *m << endl;
    }
}

// (1.) Indicate the exact number of base cases and exact number of recursive cases you implemented in your
    // search(...) function. Briefly describe the purpose each in code comments.

//  There are 3 base cases, which are out of bounds(inBounds), a wall (iswall), and a place already visited (isVisited) 
// The recursive case is the search method with it calling itself again and again to find the direction.


// (2.) Your solution found a path through maze1.txt, which is illustrated above. But your classmate’s solution
//found a different valid path through maze1.txt, illustrated below. In one sentence, as a comment in the
//header comments of your code, explain what causes your two solutions to find different initial paths through
//the Maze

// The way the maze is solved is diffrenciated by how the recursive method works, its programmed in a way that for every mark it reaches 
// it loads through different directions, depending on what comes first, if going down comes first and theres and open path , it will go through that path to solve it