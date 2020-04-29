#include "Maze.hpp"
#include <stack>
#include <queue>
#include <list>

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


    std::vector<MazeNode> solveDFS(Maze &a_maze)
    {
        std::vector<MazeNode> path;
        MazeNode node = *(a_maze.getFirstNode());
        path.push_back(node);
        while(!path.empty())
        {
            node = path.back();

            if(node.getStrPos() == a_maze.getLastNode()->getStrPos())
            {
                break;
            }
            if(!canTravel(&node))
            {
                path.pop_back();
                continue;
            }
            node.setVisited();
            if(canTravel(node.getDirectionNode(directions::NORTH)))
            {
                path.push_back(*(node.getDirectionNode(directions::NORTH)));
            }
            else if(canTravel(node.getDirectionNode(directions::EAST)))
            {
                path.push_back(*(node.getDirectionNode(directions::EAST)));
            }
            else if(canTravel(node.getDirectionNode(directions::SOUTH)))
            {
                path.push_back(*(node.getDirectionNode(directions::SOUTH)));
            }
            else if(canTravel(node.getDirectionNode(directions::WEST)))
            {
                path.push_back(*(node.getDirectionNode(directions::WEST)));
            }
        }
        return path;
    }

std::vector<MazeNode> solveBFS(Maze &a_maze)
{
    std::list<MazeNode> l;
    MazeNode *node = a_maze.getFirstNode();
    l.push_back(*node);
    while(node != a_maze.getLastNode())
    {
        node = &(l.front());
        if(canTravel(node))
        {
            node->setVisited();
            for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
            {
                if(canTravel(node->getDirectionNode(dir)))
                {
                    l.push_back(*(node->getDirectionNode(dir)));
                }
            }
        }
        else
        {
            l.pop_front();
        }
    }
    std::vector<MazeNode> path(l.begin(), l.end());
    return path;
}

std::vector<MazeNode> solveDEF(Maze &a_maze)
{
        std::vector<MazeNode> t;
        // t.push_back(*(a_maze.getFirstNode()));
        // t.push_back(*(a_maze.getFirstNode()));

    return t;
}

std::vector<MazeNode> solveCustom(Maze &a_maze)
{
    std::vector<MazeNode> t;
   
    return t;
}
} // namespace solutions

int main()
{
    Maze m{"data/maze_1.csv"};
    solutions::solveDFS(m);
    // for(auto it : solutions::solveDFS(m))
    // {
        // cout<<it.getStrPos()<<endl;
    // }
    return 0;

}