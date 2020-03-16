#ifndef ASORT_H_INCLUDED
#define ASORT_H_INCLUDED

#include <algorithm>
#include "gen.h"
#ifndef EPSILON
#define EPSILON 0.00000001
#endif
#define N 450

Point result[N];
int counter = 0;

void findSegment(Point* p, int first, int last)
{
    if(first == last) return;
    setRefPoint(p[first].x, p[first].y, p[first].colour);
    int pointIndex = first;

    for(int i = first + 1; i < last; i++)
    {
        if(p[i].y < refPoint[1])
        {
            setRefPoint(p[i].x, p[i].y, p[i].colour);
            pointIndex = i;
        }
        if((p[i].y - refPoint[1]) < EPSILON && (p[i].y - refPoint[1]) > -EPSILON && p[i].x < refPoint[0])
        {
            setRefPoint(p[i].x, p[i].y, p[i].colour);
            pointIndex = i;
        }
    }

    last--;
    p[pointIndex].x = p[last].x;
    p[pointIndex].y = p[last].y;
    p[pointIndex].colour = p[last].colour;

    std::sort(p + first, p + last);

    int deltaColour = refColour ? 1 : -1;
    int resultIndex = -1;

    for(int i = first; i < last; i++)
    {
        if(p[i].colour) deltaColour++;
        else deltaColour--;
        if(deltaColour == 0)
        {
            resultIndex = i;
            break;
        }
    }

    std::cout << "(" << refPoint[0] << ", " << refPoint[1] << ")" << " (" << p[resultIndex].x << ", " << p[resultIndex].y << ")\n";
	result[counter].x = refPoint[0];
	result[counter].y = refPoint[1];
	counter++;
	result[counter]= p[resultIndex];
	counter++;

    findSegment(p, first, resultIndex);
    findSegment(p, resultIndex + 1, last);

}

#endif // ASORT_H_INCLUDED
