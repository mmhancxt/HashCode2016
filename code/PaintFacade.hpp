//
//  PaintFacade.hpp
//  HashCode2016
//
//  Created by Liang LIU on 06/02/2016.
//  Copyright © 2016 Liang LIU. All rights reserved.
//

#ifndef PaintFacade_hpp
#define PaintFacade_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

const static string path = "/Users/Xavier/Programs/c++/HashCode2016/code/";

enum PrintWay
{
    UNDEF = 0,
    SQUAR,
    V_LINE,
    H_LINE
};

class Node
{
public:
    int x;
    int y;
    char value;
    int up;
    int down;
    int left;
    int right;
    int radius;
    int coveredNb;
    bool printed;
    PrintWay way;
    
    Node(int i, int j, char data) : x(i), y(j), value(data), up(-1), down(-1), left(-1), right(-1), radius(-1), coveredNb(0), printed(false), way(UNDEF)
    {
    }
    
    bool isSharp()
    
    {
        return value == '#';
    }
};

/*
using my_container_t = vector<Node*>;
class my_comp
{
public:
    bool operator() (const Node* e1, const Node* e2) const
    {
        if (e1->way == SQUAR && e2->way == SQUAR)
        {
            return e1->minRadius < e2->minRadius;
        }
        else if (e1->way == SQUAR)
        {
            return false;
        }
        else if (e2->way == SQUAR)
        {
            return true;
        }
        else if (e1->way != UNDEF && e2->way != UNDEF)
        {
            int len1 = max(e1->horizonLength, e1->verticalLength);
            int len2 = max(e2->horizonLength, e2->verticalLength);
            return (len1 < len2);
        }
        else if (e1->way != UNDEF)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};*/

class FacadePrinter
{
private:
    vector<vector<Node>> facade;
    //priority_queue<Node*, my_container_t, my_comp> charpList;
    int row;
    int colomn;
    int count;
    
private:
    void PrintLine(ofstream& output, int startX, int startY, int endX, int endY)
    {
        count++;
        output << "PAINT_LINE " << startX << " " << startY << " " << endX << " " << endY << "\n";
        if (startX == endX)
        {
            for (int j= startY; j <= endY; j++)
            {
                facade[startX][j].printed = true;
            }
        }
        else
        {
            for (int i = startX; i <= endX; i++)
            {
                facade[i][startY].printed = true;
            }
        }
    }
    
    void PrintSquare(ofstream& output, int i, int j, int radius)
    {
        count++;
        output << "PAINT_SQUARE " << i << " " << j << " " << radius << "\n";
    }
    
    void EraseCell(ofstream& output, int i, int j)
    {
        count++;
        output << "ERASE_CELL " << i << " " << j << "\n";
    }
    
    void PrintLine2(ofstream& output, int startX, int startY, int endX, int endY)
    {
        count++;
        output << "PAINT_LINE " << startX << " " << startY << " " << endX << " " << endY << "\n";
    }
    
    void UpdateCountWithNode(Node& node, int& pointNb, int& coveredNb)
    {
        if (node.isSharp())
        {
            if (!node.printed)
            {
                coveredNb++;
            }
        }
        else
        {
            pointNb++;
        }
    }
    
    void CalculateNodeParameters(Node& node, int i, int j)
    {
        // update up, down, left, right
        bool leftIsZero = false;
        if (j != 0)
        {
            Node& leftNode = facade[i][j-1];
            if (!leftNode.isSharp())
            {
                leftIsZero = true;
            }
        }
        else
        {
            leftIsZero = true;
        }
        if (leftIsZero)
        {
            int k = j+1;
            while (k < colomn)
            {
                if (!facade[i][k].isSharp())
                {
                    break;
                }
                k++;
            }
            node.left = 0;
            node.right = k-j-1;
        }
        else
        {
            Node& leftNode = facade[i][j-1];
            node.left = leftNode.left+1;
            node.right = leftNode.right-1;
        }
        
        bool upIsZero = false;
        if (i != 0)
        {
            Node& upNode = facade[i-1][j];
            if (!upNode.isSharp())
            {
                upIsZero = true;
            }
        }
        else
        {
            upIsZero = true;
        }
        if (upIsZero)
        {
            int k = i+1;
            while (k < row)
            {
                if (!facade[k][j].isSharp())
                {
                    break;
                }
                k++;
            }
            node.up = 0;
            node.down = k-i-1;
        }
        else
        {
            Node& upNode = facade[i-1][j];
            node.up = upNode.up+1;
            node.down = upNode.down -1;
        }
    }
    
    int UpdateSharpNodeCoveredNb(Node& node, int i, int j)
    {
        if (node.left == -1)
        {
            CalculateNodeParameters(node, i, j);
        }
        
        int horizonCovered = 0;
        for (int y = j-node.left; y <= j+node.right;y++)
        {
            if (!facade[i][y].printed)
            {
                horizonCovered++;
            }
        }
        
        int verticalCovered = 0;
        for (int x = i-node.up; x <= i+node.down;x++)
        {
            if (!facade[x][j].printed)
            {
                verticalCovered++;
            }
        }
        
        // update min radius
        int boards[] = { i, j, row-i, colomn-j, node.left, node.right, node.up, node.down};
        int minRadius = *min_element(boards, boards+8);
        
        int radiusCovered = 0;
        if (minRadius != 0)
        {
            int pointNb = 0;
            int coveredNb = 0;
            int maxCoveredRadius = 0;
            if (!node.printed)
            {
                coveredNb = 1;
            }
            for (int r = 1; r <= minRadius; r++)
            {
                for (int y = j-r; y <= j+r; y++)
                {
                    // north
                    Node& northNode = facade[i-r][y];
                    UpdateCountWithNode(northNode, pointNb, coveredNb);
                    // north
                    Node& southNode = facade[i+r][y];
                    UpdateCountWithNode(southNode, pointNb, coveredNb);
                }
                for (int x = i-r+1; x < i+r; x++)
                {
                    // west
                    Node& westNode = facade[x][j-r];
                    UpdateCountWithNode(westNode, pointNb, coveredNb);
                    // east
                    Node& eastNode = facade[x][j+r];
                    UpdateCountWithNode(eastNode, pointNb, coveredNb);
                }
                
                if (pointNb <= r)
                {
                    maxCoveredRadius = r;
                    radiusCovered = coveredNb;
                }
            }
            node.radius = maxCoveredRadius;
        }
        
        if (radiusCovered > horizonCovered && radiusCovered > verticalCovered)
        {
            node.way = SQUAR;
            node.coveredNb = radiusCovered;
        }
        else if (horizonCovered > verticalCovered)
        {
            node.way = H_LINE;
            node.coveredNb = horizonCovered;
        }
        else
        {
            node.way = V_LINE;
            node.coveredNb = verticalCovered;
        }
        return node.coveredNb;
    }
    
public:
    FacadePrinter() : count(0), row(0), colomn(0)
    {
    };
    
    Node* GetMatrixMaximumCoveredNode()
    {
        int max_covered = 0;
        Node* target = nullptr;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0 ; j < colomn; j++)
            {
                Node& node = facade[i][j];
                if (node.isSharp())
                {
                    int covered = UpdateSharpNodeCoveredNb(node, i, j);
                    if (covered > max_covered)
                    {
                        max_covered = covered;
                        target = &node;
                    }
                }
            }
        }
        return target;
    }
    
    void PrintImage()
    {
        ofstream output;
        output.open(path + "output.txt");
        set<Node*> eraseList;
        
        Node* node = GetMatrixMaximumCoveredNode();
        while (node != nullptr)
        {
            if (node->way == SQUAR)
            {
                PrintSquare(output, node->x, node->y, node->radius);
                for (int x = node->x-node->radius; x <= node->x+node->radius; x++)
                {
                    for (int y = node->y-node->radius; y <= node->y+node->radius; y++)
                    {
                        if (!facade[x][y].isSharp())
                        {
                            eraseList.insert(&facade[x][y]);
                        }
                        else
                        {
                            facade[x][y].printed = true;
                        }
                    }
                }
                
            }
            else if (node->way == H_LINE)
            {
                
                PrintLine(output, node->x, node->y-node->left, node->x, node->y+node->right);
                
            }
            else if (node->way == V_LINE)
            {
                
                PrintLine(output, node->x-node->up, node->y, node->x+node->down, node->y);
            }
            else
            {
                cout << "Error" << endl;
            }
            node = GetMatrixMaximumCoveredNode();
        }
        
        cout << "EraseList size is " << eraseList.size() << endl;
        for (Node* node : eraseList)
        {
            EraseCell(output, node->x, node->y);
        }
        output.close();
        cout << "count = " << count << endl;
    }
    
    void ReadData(string fileName)
    {
        ifstream input;
        input.open(path + fileName);
        string line;
        
        if (input.is_open())
        {
            input >> row >> colomn;
            cout << "row = " << row << endl;
            cout << "colomn = " << colomn << endl;
            getline(input, line);
            for (int i = 0 ;i < row; i++)
            {
                getline(input, line);
                vector<Node> newLine;
                for (int j = 0; j < colomn; j++)
                {
                    char c = line[j];
                    Node node(i, j, c);
                    newLine.push_back(node);
                }
                facade.push_back(newLine);
            }
            input.close();
        }
        else
        {
            cout << "File not found." << endl;
        }
    }
    
    void PrintWithHorizon()
    {
        ifstream input;
        input.open(path + "right_angle.in");
        string line;
        ofstream output;
        output.open(path + "output.txt");
        if (input.is_open() && output.is_open())
        {
            int row= 0, colomn = 0;
            input >> row >> colomn;
            cout << "row = " << row << endl;
            cout << "colomn = " << colomn << endl;
            getline(input, line);
            for (int i = 0 ;i < row; i++)
            {
                getline(input, line);
                bool painting = false;
                int startY=0;
                for (int j=0; j< colomn; j++)
                {
                    char c = line[j];
                    if (c == '#')
                    {
                        if (painting)
                        {
                            if (j == colomn-1)
                            {
                                PrintLine2(output, i, startY, i, j);
                                painting = false;
                            }
                        }
                        else
                        {
                            if (j == colomn-1)
                            {
                                PrintLine2(output, i,j,i,j);
                            }
                            else
                            {
                                startY = j;
                                painting = true;
                            }
                        }
                    }
                    else
                    {
                        if (painting)
                        {
                            PrintLine2(output, i, startY, i, j-1);
                            painting = false;
                        }
                    }
                }
            }
            input.close();
            output.close();
            cout << count << endl;
        }
        else
        {
            cout << "No file found" << endl;
        }
    }
};



#endif /* PaintFacade_hpp */
