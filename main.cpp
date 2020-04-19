#include <iostream>
#include "Maze.hpp"

using namespace std;

namespace solutions
{
    int getNumberOfWalls(MazeNode *a_node)
    {
        int wall_counter = 0;
        for (directions::nesw dir = directions::NORTH; dir < directions::EAST; dir = directions::nesw(dir + 1))
        {
            if (a_node->getDirectionNode(dir) == nullptr || a_node->getDirectionNode(dir)->isWall() || a_node->getDirectionNode(dir)->isVisited())
            {
                wall_counter++;
            }
        }
        return wall_counter;
    }

    bool canTravel(MazeNode *a_node)
    {
        if (a_node->isVisited() || a_node->isWall())
        {
            return false;
        }
        return true;
    }

    void DFS(Maze &a_maze, std::vector<MazeNode> &path)
    {
        if(a_maze.getCurrentNode() != nullptr && a_maze.getCurrentNode() == a_maze.getLastNode())
        {
            path.push_back(*(a_maze.getCurrentNode())); // if path found an end add the last node and return
            return;
        }
        a_maze.getCurrentNode()->setVisited();
        path.push_back(*(a_maze.getCurrentNode()));
        for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1)) // explore neighbors
        {
            if(a_maze.getCurrentNode()->getDirectionNode(dir) != nullptr && canTravel(a_maze.getCurrentNode()->getDirectionNode(dir)))
            {
                a_maze.setCurrentNode(a_maze.getCurrentNode()->getDirectionNode(dir));
                DFS(a_maze, path);
            }
        }
    }

    std::vector<MazeNode> solveDFS(Maze &a_maze)
    {
        std::vector<MazeNode> path;
        DFS(a_maze, path);
        return path;
    }

    std::vector<MazeNode> solveBFS(Maze &a_maze)
    {
    }

    std::vector<MazeNode> solveDEF(Maze &a_maze)
    {
    }

    std::vector<MazeNode> solveCustom(Maze &a_maze)
    {
    }
} // namespace solutions

int main()
{
    Maze m("data/maze_1.csv");
    for(auto it : solutions::solveDFS(m))
    {
        std::cout<<it.getStrPos()<<std::endl;
    }
    return 0;
}


//begin: (12,6)
//end: (18,0)
