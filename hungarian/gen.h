#ifndef GEN_H_INCLUDED
#define GEN_H_INCLUDED

#include <algorithm>
#ifndef EPSILON
#define EPSILON 0.000000000001
#endif // EPSILON
#define N 1000

double refPoint[2];

struct Point
{
    double x;
    double y;
    bool operator< (const Point &p) const
    {
        return (((x - refPoint[0]) * (p.y - refPoint[1]) - (y - refPoint[1]) * (p.x - refPoint[0])) > 0);
    }
    bool operator== (const Point &p)
    {
        return (((x - refPoint[0]) * (p.y - refPoint[1]) - (y - refPoint[1]) * (p.x - refPoint[0])) > -EPSILON && ((x - refPoint[0]) * (p.y - refPoint[1]) - (y - refPoint[1]) * (p.x - refPoint[0])) < EPSILON);
    }
};


void setRefPoint(double x, double y)
{
    refPoint[0] = x;
    refPoint[1] = y;
}

double randomDouble()
{
    return (double)rand() / RAND_MAX;
}

void generatePoints(Point* whitePoints, Point* blackPoints, int n)
{
    Point points[2 * N];
    Point p;
    int numberOfPoints = 1;
    bool ok;
    points[0].x = randomDouble();
    points[0].y = randomDouble();
    numberOfPoints++;
    points[1].x = randomDouble();
    points[1].y = randomDouble();
    if(n < 3) return;
    while(numberOfPoints != n)
    {
        ok = true;
        numberOfPoints++;
        p.x = randomDouble();
        p.y = randomDouble();
        setRefPoint(p.x, p.y);

        std::sort(points, points + numberOfPoints - 1);

        for(int i = 0; i < numberOfPoints - 2; i++)
        {
            if(points[i] == points[i + 1]) ok = false;
        }
        if(points[0] == points[numberOfPoints - 2]) ok = false;

        if(!ok)
        {
            numberOfPoints--;
            continue;
        }
        else points[numberOfPoints - 1] = p;

    }

    for(int i = 0; i < numberOfPoints; i++)
    {

        if(i % 2) whitePoints[i/2] = points[i];
        else blackPoints[i/2] = points[i];
    }
}


#endif // GEN_H_INCLUDED
