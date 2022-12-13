#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>
#include<set>

using namespace std;

class Point {
    public:
        int x, y;
        int id;

        Point(int a, int b, int id): x(a), y(b), id(id){}

        bool operator==(const Point &p) 
        {
            return (this->x == p.x) && (this->y == p.y);
        }

        friend ostream& operator<<(ostream& out, const Point& p);
};

ostream& operator<<(ostream& out, const Point& p)
{
    out<<"id "<<p.id<<" x: "<<p.x<<" y: "<<p.y;
    return out;
}

void MoveHead(Point* knot, string direction)
{
    if (direction == "R")
    {
        knot->x += 1;
    }
    else if (direction == "U")
    {
        knot->y += 1;
    }
    else if (direction == "L")
    {
        knot->x -= 1;
    }
    else if (direction == "D")
    {
        knot->y -= 1;
    }
    else
    {
        cout<<"invalid direction!";
    }
}

void MoveTail(Point* head, Point* tail, string direction)
{
    if (head->x == tail->x && head->y == tail->y)
    {
        return;
    }
    
    // Moving tail vertically
    if (head->x == tail->x)
    {
        (head->y > tail->y) ? (tail->y += 1) : (tail->y -= 1);
        return;
    }

    // Moving tail horizontally
    if (head->y == tail->y)
    {
        (head->x > tail->x) ? (tail->x += 1) : (tail->x -= 1);
        return;
    }
    
    // Moving tail diagonally 
    (head->x > tail->x) ? (tail->x += 1) : (tail->x -= 1);
    (head->y > tail->y) ? (tail->y += 1) : (tail->y -= 1);
    return;
}

int distanceBtwPoints(int x1, int y1, int x2, int y2)
{
    return max(abs(x1 - x2), abs(y1 - y2));
}

void MoveKnots(vector<Point*> points, string direction, int distance, set<pair<int, int>> &uniqueVisits)
{
    while (distance != 0)
    {
        auto head = points[0];
        MoveHead(head, direction);
        Point* prevKnot = nullptr;
        for (size_t i = 1; i <= points.size() - 1; i++)
        {
            auto tail = points[i];
            
            int distanceBtwHandT = distanceBtwPoints(head->x, head->y, tail->x, tail->y);
            if (distanceBtwHandT > 1)
            {   
                MoveTail(head, tail, direction); 
            }
            
            head = points[i];
            prevKnot = tail;
        }
        
        auto tail = points.back();
        if (prevKnot != nullptr)
        {
            int distanceBtwHandT = distanceBtwPoints(prevKnot->x, prevKnot->y, tail->x, tail->y);
            if (distanceBtwHandT > 1)
            {   
                MoveTail(prevKnot, tail, direction); 
            }
        }

        auto curPos = make_pair(tail->x, tail->y);
        uniqueVisits.insert(curPos);
        distance -= 1;
    }
}

void Move(vector<string> &inputs, vector<Point*> points, set<pair<int, int>> &uniqueVisits)
{
    if (inputs.size() != 2)
    {
        cout<<"Invalid input";
        return;
    }
    string direction  = inputs[0];
    int distance = stoi(inputs[1]);
    MoveKnots(points, direction, distance, uniqueVisits);
}

void splitLine(vector<string> &inputs, string curLine)
{
    char* curSplit = strtok(const_cast<char*>(curLine.c_str()), " ");
    while(curSplit != nullptr)
    {
        inputs.push_back(std::string(curSplit));
        curSplit = strtok(nullptr, " ");
    }
}

void Runnnnnnnnn(vector<Point*>  points, string curLine, set<pair<int, int>> &uniqueVisits)
{
    vector<string> inputs;
    splitLine(inputs, curLine);
    Move(inputs, points, uniqueVisits);
}

int main(){
    std::vector<Point*> points;
    int numOfPoints = 10; // Change this to 2 for Part 1's solution.
    for (size_t i = 0; i < numOfPoints; i++)
    {
        points.push_back(new Point{0, 0, (int)(i + 1)});
    }
    
    string curLine;
    ifstream mInput("input.txt");
    set<pair<int, int>> uniqueVisits;

    while(getline(mInput, curLine))
    {
        Runnnnnnnnn(points, curLine, uniqueVisits);
    }

    cout<<"Distance traveled by tail: "<<uniqueVisits.size()<<endl;

    for (size_t i = 0; i < points.size(); i++)
    {
        delete points[i];
    }
    
    mInput.close();
    return 0;
}
