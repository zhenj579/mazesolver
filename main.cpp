#include <iostream>
#include <stack>
#include <queue>
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
        if (a_node == nullptr || a_node->isVisited() || a_node->isWall())
        {
            return false;
        }
        return true;
    }

    bool hasUnvisitedNeighbors(MazeNode *node)
    {
        for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
        {
            if(node != nullptr && canTravel(node->getDirectionNode(dir)))
                return true;
        }
        return false;
    }

    void DFS(MazeNode *curr, MazeNode *last, std::vector<MazeNode> &path)
    {

    }

    void printStack(stack<MazeNode *> &s)
    {
        if(s.empty())
            return;
        
        MazeNode *n = s.top();
        s.pop();

        printStack(s);

        cout<<n->getStrPos()<<endl;

        s.push(n);
    }

    std::vector<MazeNode> solveDFS(Maze &a_maze)
    {
        std::vector<MazeNode> path;
        // DFS(a_maze.getFirstNode(), a_maze.getLastNode(), path);
        std::stack<MazeNode *> s;
        MazeNode *node = a_maze.getFirstNode();
        s.push(node);
        while(!s.empty())
        {
            node = s.top();
            node->setVisited(); // if node isn't visited then set it to visited
            if(node == a_maze.getLastNode())
            {
                break;
            }

            if(!hasUnvisitedNeighbors(node))
            {
                s.pop();
                node = s.top();
            }

            for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
            {
                if(canTravel(node->getDirectionNode(dir)))
                {
                    s.push(node->getDirectionNode(dir));
                }
            }

        }
        printStack(s);
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
    // solutions::solveDFS(m);
    for(auto it : solutions::solveDFS(m))
    {
        std::cout<<it.getStrPos()<<std::endl;
    }
    return 0;
}


//begin: (12,6)
//end: (18,0)
