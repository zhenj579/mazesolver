#include "Maze.cpp"
#include <stack>
#include <queue>

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

    void clearDupes(std::vector<MazeNode> &path)
    {
        for(int i = 0; i < path.size()-1; i++)
        {
            for(int j = i+1; j < path.size(); j++)
            {
                if(path[i].getStrPos() == path[j].getStrPos())
                {
                    path.erase(path.begin()+j);
                }
            }
        }
    }


    std::vector<MazeNode> solveDFS(Maze &a_maze)
    {
        std::vector<MazeNode> path;
        std::stack<MazeNode *> s;
        MazeNode *node = a_maze.getFirstNode();
        s.push(node);
        while(node != a_maze.getLastNode())
        {
            node = s.top();
            node->setVisited(); // if node isn't visited then set it to visited

            if(!hasUnvisitedNeighbors(node)) // if at dead end, go back
            {
                s.pop();
                path.pop_back();
                node = s.top();
            }

            for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
            {
                if(canTravel(node->getDirectionNode(dir))) // explore neighbors
                {
                    s.push(node->getDirectionNode(dir));
                    path.push_back(*node);
                }
            }
        }
        clearDupes(path); // remove other valid paths, just leave one.
        return path;
    }

std::vector<MazeNode> solveBFS(Maze &a_maze)
{
    std::vector<MazeNode> path;
    // std::queue<MazeNode *> q;
    // MazeNode *node = a_maze.getFirstNode();
    // q.push(node);
    // while(node != a_maze.getLastNode())
    // {
    //     node = q.front();

    //     cout<<node->getStrPos()<<endl;

    //     if(!hasUnvisitedNeighbors(node))
    //     {
    //         q.pop();
    //     }
    //     for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
    //     {
    //         if(canTravel(node->getDirectionNode(dir))) // explore neighbors
    //         {
    //             q.push(node->getDirectionNode(dir));
    //             path.push_back(*node);
    //         }
    //     }
    // }
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
    // std::queue<MazeNode *> q;
    // MazeNode *node = a_maze.getFirstNode();
    // q.push(node);
    // while(!q.empty())
    // {
    //     node = q.front();

    //     q.pop();

    //     node->setVisited();

    //     t.push_back(*node);

    //     if(node == a_maze.getLastNode())
    //     {
    //         break;
    //     }

    //     if(!hasUnvisitedNeighbors(node))
    //     {
    //         q.pop();
    //         t.pop_back();
    //         node = q.front();
    //     }

    //     for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
    //     {
    //         if(canTravel(node->getDirectionNode(dir))) // explore neighbors
    //         {
    //             q.push(node->getDirectionNode(dir));
    //         }
    //     }
    // }
    // clearDupes(t);
    return t;
}
} // namespace solutions

// int main()
// {
//     Maze m{"data/maze_1.csv"};
//     // solutions::solveCustom(m);
//     for(auto it : solutions::solveDFS(m))
//     {
//         cout<<it.getStrPos()<<endl;
//     }
//     return 0;

// }