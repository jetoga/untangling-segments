#ifndef GEN_H_INCLUDED
#define GEN_H_INCLUDED

#ifndef EPSILON
#define EPSILON 0.00000001
#endif // EPSILON


double refPoint[2];
bool refColour;

struct Point
{
    double x;
    double y;
    bool colour;
    bool operator< (const Point &p) const
    {
        return ((x - refPoint[0]) * (p.y - refPoint[1]) - (y - refPoint[1]) * (p.x - refPoint[0])) > 0;
    }
    bool operator== (const Point &p)
    {
        return (((x - refPoint[0]) * (p.y - refPoint[1]) - (y - refPoint[1]) * (p.x - refPoint[0])) > -EPSILON && ((x - refPoint[0]) * (p.y - refPoint[1]) - (y - refPoint[1]) * (p.x - refPoint[0])) < EPSILON);
    }
};


void setRefPoint(double x, double y, bool colour)
{
    refPoint[0] = x;
    refPoint[1] = y;
    refColour = colour;
}

double randomDouble()
{
    return (double)rand() / RAND_MAX;
}

void generatePoints(Point* points, int n)
{
    Point p;
    int numberOfPoints = 1;
    bool ok;
    points[0].x = randomDouble();
    points[0].y = randomDouble();
    points[0].colour = numberOfPoints % 2;
    numberOfPoints++;
    points[1].x = randomDouble();
    points[1].y = randomDouble();
    points[1].colour = numberOfPoints % 2;
    if(n < 3) return;
    while(numberOfPoints != n)
    {
        ok = true;
        numberOfPoints++;
        p.x = randomDouble();
        p.y = randomDouble();
        p.colour = numberOfPoints % 2;
        setRefPoint(p.x, p.y, p.colour);

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

}

#endif // GEN_H_INCLUDED
