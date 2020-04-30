#include "Maze.hpp"
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

namespace solutions
{

int getNumberOfWalls(MazeNode *a_node)
{
    int wall_counter = 0;
    for (directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
    {
        if (a_node->getDirectionNode(dir) == nullptr || a_node->getDirectionNode(dir)->isWall() || a_node->getDirectionNode(dir)->isVisited())
        {
            std::cout<<a_node->getDirectionNode(dir)->getStrPos()<<std::endl;
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
        if(canTravel(node->getDirectionNode(dir)))
        {
            return true;
        }
    }
    return false;
}

std::vector<MazeNode> backtrace(unordered_map<MazeNode *, MazeNode *> map, MazeNode *start, MazeNode *finish)
{
    std::vector<MazeNode> path;
    MazeNode *node = finish;
    while(node != start)
    {
        path.push_back(*node);
        node = map[node];
    }
    path.push_back(*start);
    reverse(path.begin(), path.end());
    return path;
}
std::vector<MazeNode> solveDFS(Maze &a_maze)
{
    std::vector<MazeNode> path;
    std::stack<MazeNode *> s;
    MazeNode *node = a_maze.getFirstNode();
    path.push_back(*node);
    s.push(node);
    node->setVisited();
    while(!path.empty())
    {
        node = s.top();

        if(node == a_maze.getLastNode())
        {
            break;
        }

        if(canTravel(node->getDirectionNode(directions::NORTH)))
        {
            s.push(node->getDirectionNode(directions::NORTH));
            path.push_back(*(node->getDirectionNode(directions::NORTH)));
            node->getDirectionNode(directions::NORTH)->setVisited();
        }
        else if(canTravel(node->getDirectionNode(directions::EAST)))
        {
            s.push(node->getDirectionNode(directions::EAST));
            path.push_back(*(node->getDirectionNode(directions::EAST)));
            node->getDirectionNode(directions::EAST)->setVisited();
        }
        else if(canTravel(node->getDirectionNode(directions::SOUTH)))
        {
            s.push(node->getDirectionNode(directions::SOUTH));
            path.push_back(*(node->getDirectionNode(directions::SOUTH)));
            node->getDirectionNode(directions::SOUTH)->setVisited();
        }
        else if(canTravel(node->getDirectionNode(directions::WEST)))
        {
            s.push(node->getDirectionNode(directions::WEST));
            path.push_back(*(node->getDirectionNode(directions::WEST)));
            node->getDirectionNode(directions::WEST)->setVisited();
        }
        else
        {
            s.pop();
            path.pop_back();
        }
    }
    return path;
}

std::vector<MazeNode> solveBFS(Maze &a_maze)
{
    std::queue<MazeNode *> q;
    std::unordered_map<MazeNode *, MazeNode *> parents;
    MazeNode *node = a_maze.getFirstNode();
    node->setVisited();
    q.push(node);

    while(!q.empty())
    {
        node = q.front();
        q.pop();

        if(hasUnvisitedNeighbors(node))
        {
            for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
            {
                if(canTravel(node->getDirectionNode(dir)))
                {
                    parents[node->getDirectionNode(dir)] = node;
                    node->getDirectionNode(dir)->setVisited();
                    q.push(node->getDirectionNode(dir));
                }
                if(q.front() == a_maze.getLastNode())
                {
                    break;
                }
            }
        }
    }
    std::vector<MazeNode> path = backtrace(parents, a_maze.getFirstNode(), a_maze.getLastNode());
    return path;
}

std::vector<MazeNode> solveDEF(Maze &a_maze)
{
    std::vector<MazeNode> path;
    std::stack<MazeNode *> deadEnds;
    for(auto &it : a_maze.getNodes())
    {
        // if(!it.isWall() && getNumberOfWalls(&it) >= 3 && it.getStrPos() != a_maze.getLastNode()->getStrPos() && it.getStrPos() != a_maze.getFirstNode()->getStrPos())
        // {
        //     it.setVisited();
        //     deadEnds.push(&it);
        // }
        if(it.getStrPos() == "(15,2)") 
        {
            it.setVisited();
            deadEnds.push(&it);
        }
    }
    MazeNode *node = deadEnds.top();

    std::cout<<node->isVisited()<<std::endl;

    getNumberOfWalls(node->getDirectionNode(directions::SOUTH));

    // std::cout<<node->isVisited()<<std::endl;

    // std::cout<<node->getStrPos()<<std::endl;

    // std::cout<<node->getDirectionNode(directions::SOUTH)->getStrPos()<<std::endl;

    // node->getDirectionNode(directions::SOUTH)->setVisited();
    // node->getDirectionNode(directions::SOUTH)->getDirectionNode(directions::SOUTH)->setVisited();

    // std::cout<<getNumberOfWalls(node->getDirectionNode(directions::SOUTH))<<std::endl;

    // while(!deadEnds.empty())
    // {
    //     node = deadEnds.top();

    //     std::cout<<node->getStrPos()<<std::endl;

    //     deadEnds.pop();

    // }
    // MazeNode *node;
    // while(!deadEnds.empty())
    // {
    //     node = deadEnds.top();

    //     std::cout<<node->isVisited()<<std::endl;

    //     deadEnds.pop();

    // }
    return path;
}

std::vector<MazeNode> solveCustom(Maze &a_maze)
{
    return solveDFS(a_maze);
}
} // namespace solutions

int main()
{
    Maze m{"data/maze_1.csv"};
    solutions::solveDEF(m);
    // for(auto it : solutions::solveDEF(m))
    // {
        // cout<<it.getStrPos()<<endl;
    // }
    return 0;

}