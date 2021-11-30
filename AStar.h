#ifndef ASTAR_H
#define ASTAR_H
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
using namespace std;

#define    MAXO(A, B)    ((A) > (B) ? (A) : (B))

#define    MINO(A, B)    ((A) < (B) ? (A) : (B))

#define    ABSO(A)    ((A) < (0) ? (-A) : (A))

#define GETMAPINDEX(X, Y, XSIZE, YSIZE) ((Y)*XSIZE + (X))

#define NUMOFDIRS 8

class Node
{
public:
    int x, y;
    int g, h, f;
    Node* father;
    Node(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->g = INT_MAX;
        this->h = INT_MAX;
        this->f = 0;
        this->father = NULL;
    }
    ~Node() {};
    bool operator == (const Node& n2) const
    {
        return ((this->x == n2.x) && (this->y == n2.y));
    }
};

struct NodeComparator
{
    bool operator()(const Node& n1, const Node& n2) const
    {
        return n1 == n2;
    }
};

struct NodeHasher
{
    size_t operator()(const Node& n) const
    {
        return n.x + 34245 * n.y;
    }
};

struct cmpF {
    bool operator() (const Node* const& v1, const Node* const& v2) { return v1->f > v2->f; }
};


class AStar {
public:
    

    AStar(double* map, int mapSizeX, int mapSizeY, double v) {
        
        this->map = map;
        this->mapSizeX = mapSizeX;
        this->mapSizeY = mapSizeY;
        this->v = v;
        this->w = 10;
    };

    ~AStar() {};

    void search(double* start, double* goal ) {
        startNode = new Node((int)start[0], (int)start[1]);
        goalNode = new Node((int)goal[0], (int)goal[1]);
        //int OpenList[100000];
        //int CloseList[100000];
        startNode->g = 0;
        startNode->h = distance(startNode, goalNode);
        startNode->f = startNode->g + w * startNode->h;

        unordered_set<Node, NodeHasher, NodeComparator> CloseList;
        unordered_set<Node, NodeHasher, NodeComparator> OpenList;
        priority_queue<Node*, vector<Node*>, cmpF> OPEN;

        OPEN.push(startNode);

        //cout << mapSizeX << endl;
        /*for (int i = 0; i < (mapSizeX * mapSizeY) - 1; ++i) {
            
            OpenList[i] = INT_MAX;
            CloseList[i] = 0;
        }*/
        
        OpenList.insert(*startNode);
        //cout << OpenList.size() << endl;

        //OpenList[GETMAPINDEX(startNode->x, startNode->y, mapSizeX, mapSizeY)] = startNode->g;
        
        while (!OPEN.empty() && CloseList.find(*goalNode) == CloseList.end()) {
            //cout << "HERE3" << endl;
            Node* minNode = OPEN.top();
            
            while (CloseList.find(*minNode) != CloseList.end()) {
                OPEN.pop();
                minNode = OPEN.top();
            }

            CloseList.insert(*minNode);
            if (minNode == goalNode) {
                cout << "GOAL" << endl;
                break;
            }
            OPEN.pop();
            expand(minNode, OpenList, CloseList, OPEN);
            //cout << minNode->g <<' '<< minNode->h <<' '<< minNode->f << endl;
        }

        goalNode->father = (*CloseList.find(*goalNode)).father;
    };

    void expand(Node* minNode, unordered_set<Node, NodeHasher, NodeComparator> &OpenList,
        unordered_set<Node, NodeHasher, NodeComparator> &CloseList, priority_queue<Node*, vector<Node*>, cmpF> &OPEN) {
        int dX[NUMOFDIRS] = { -1, -1, -1,  0,  0,  1, 1, 1 };
        int dY[NUMOFDIRS] = { -1,  0,  1, -1,  1, -1, 0, 1 };
        //cout << "HERE4" << endl;
        for (int dir = 0; dir < 8; ++dir) {
            int curX = dX[dir] + minNode->x;
            int curY = dY[dir] + minNode->y;

            if (curX < 1 || curX > mapSizeX || curY < 1 || curY > mapSizeY) {
                continue;
            }
            double curW = (double)map[GETMAPINDEX(curX, curY, mapSizeX, mapSizeY)];
            if (curW >= 1) {
                continue;
            }

            Node* curNode = new Node(curX, curY);
            curNode->father = minNode;
            curNode->h = distance(curNode, goalNode);
            curNode->g = minNode->g + 1;
            curNode->f = curNode->g + w * curNode->h;
            
            if (CloseList.find(*curNode) != CloseList.end()) {
                continue;
            }
            unordered_set<Node, NodeHasher, NodeComparator>::iterator it = OpenList.find(*curNode);
            if (it != OpenList.end() && (*it).g > curNode->g) {
                continue;
            }
            //cout << "GOAL" << (goalNode->father == NULL) << endl;
            OpenList.insert(*curNode);
            OPEN.push(curNode);
        }
    };

    int distance(Node* Node1, Node* Node2) {
        int dx = Node1->x - Node2->x;
        int dy = Node1->y - Node2->y;
        return  ABSO(dx) + ABSO(dy);
    };

    vector<int> getDirection() {
        vector<int> direction;
        
        while (goalNode->father != startNode) {
            auto father = goalNode->father;
            delete goalNode;
            goalNode = father;
        }
        direction.push_back((int)((goalNode->x - startNode->x)));
        direction.push_back((int)((goalNode->y - startNode->y)));
        delete goalNode;
        delete startNode;

        return direction;
    }
    

private:
    double* map;
    int mapSizeX;
    int mapSizeY;
    double v, w;
    Node* startNode;
    Node* goalNode;

};

#endif



