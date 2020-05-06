/*
    File Title: Solutions.cpp
    Student: John Zhen
    Date of Creation: 5/1/2020
    Description: Implementation of DFS, BFS, and DEF on a maze.
*/
#include "Maze.cpp"
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

namespace solutions
{

int getNumberOfWalls(MazeNode *a_node) // get the number of walls on a node
{
    int wall_counter = 0;
    for (directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
    {
        if (a_node->getDirectionNode(dir) == nullptr || a_node->getDirectionNode(dir)->isWall() || a_node->getDirectionNode(dir)->isVisited())
        {
            wall_counter++;
        }
    }
    return wall_counter;
}

bool canTravel(MazeNode *a_node) // test if a node can travel
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
        if(canTravel(node->getDirectionNode(dir))) // if a node can travel in one direction then they have an univistited neighbor
        {
            return true;
        }
    }
    return false;
}

    
//backtrace the parents of the end node up until the start, this will give us the proper and shortest path from end to finish

std::vector<MazeNode> backtrace(unordered_map<MazeNode *, MazeNode *> &map, MazeNode *start, MazeNode *finish)
{
    std::vector<MazeNode> path; // a mazenode vector to keep store the path
    MazeNode *node = finish; // start from the end of the maze
    while(node != start) // loop until the node reaches the beginning
    {
        path.push_back(*node); //push the node 
        node = map[node]; // set the node to the parent of the current node
    }
    path.push_back(*start); // since we stopped at the start, we also have to push the start into the path
    reverse(path.begin(), path.end()); //since our path is backwards from end to start, reverse the vector to get a path from start to finish.
    return path;
}
std::vector<MazeNode> solveDFS(Maze &a_maze)
{
    std::vector<MazeNode> path;
    std::stack<MazeNode *> s;
    MazeNode *node = a_maze.getFirstNode(); 
    path.push_back(*node); // push the first node onto the stack
    s.push(node);
    node->setVisited(); // visit it
    while(!path.empty())
    {
        node = s.top();

        if(node == a_maze.getLastNode()) // if exit found DFS has finished.
        {
            break;
        }

        if(canTravel(node->getDirectionNode(directions::NORTH))) // try going continuously in one path until exit is found
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
            path.pop_back(); // if one path doesnt work backtrack to previous node with neighbors and try another path
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
    q.push(node); // push the first node onto the queue

    while(!q.empty())
    {
        node = q.front(); // pop the first node off
        q.pop();

        if(hasUnvisitedNeighbors(node)) // if there are no unvisited neighbors
        {
            for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir + 1))
            {
                if(canTravel(node->getDirectionNode(dir))) // explore the neighbors and push it onto the queue
                {
                    parents[node->getDirectionNode(dir)] = node; // keep track of the parents of every child node, so we can get the path back out from end to start
                    node->getDirectionNode(dir)->setVisited();
                    q.push(node->getDirectionNode(dir));
                }
                if(q.front() == a_maze.getLastNode())
                {
                    break; // if you reach the end of the maze, BFS has completed
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
    std::stack<MazeNode *> deadEnds; // holds all the dead ends and the neighbors its explored
    for(auto &it : a_maze.getNodes())
    {
        if(!it.isWall() && getNumberOfWalls(&it) >= 3 && it.getStrPos() != a_maze.getLastNode()->getStrPos() && it.getStrPos() != a_maze.getFirstNode()->getStrPos())
        {
            a_maze.contains(it.getPos())->setVisited(); // find the dead ends and mark them as visited
            deadEnds.push(a_maze.contains(it.getPos())); // push them onto the deadEnd stack
        }
    }

    MazeNode *node = deadEnds.top();
    while(!deadEnds.empty()) // loops until there are no more dead ends to process
    {
        node = deadEnds.top(); //process the dead ends

        deadEnds.pop();

        for(directions::nesw dir = directions::NORTH; dir <= directions::WEST; dir = directions::nesw(dir+1))
        {
            if(canTravel(node->getDirectionNode(dir)) && getNumberOfWalls(node->getDirectionNode(dir)) >= 3)
            {
                node->getDirectionNode(dir)->setWall(); // if there are 3 walls then we are at a dead end so mark the current node as a wall
                deadEnds.push(node->getDirectionNode(dir)); // push any other explorable neighbors onto the stack and check if they qualify as dead ends
            }
        }
    }
    path = solveDFS(a_maze); // get the remaining path that is not a wall, which will be the path to the end.
    return path;
}


std::vector<MazeNode> solveCustom(Maze &a_maze)
{
    return solveDEF(a_maze);
}
} // namespace solutions
