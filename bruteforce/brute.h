#include <algorithm>
#include "gen.h"

/**
 * Metoda naiwna
 * Algorytm brutalny sprawdzający wszystkie permutacje
 * przyporządkowań punktów w kwestii przecinania się odcinków tak utworzonych
 * Złoźoność asymptotyczna O(n! * n^2)
 */

Point result[N];
int counter = 0;

double vect(Point i, Point j, Point k)
{
	return (i.x - k.x) * (j.y - k.y) - (i.y - k.y) * (j.x - k.x);
}

/*
 * Funkcja przeszukująca permutacje punktów dopóki nie znajdzie poprawnej
 */
void brute(Point whitePoints[N], Point blackPoints[N], int n)
{
	int whitePointsIndex[N];
	for (int i = 0; i < n; i++)
		whitePointsIndex[i] = i;
	bool found = false;

	while (!found)
	{
		std::next_permutation(whitePointsIndex, whitePointsIndex + n);

		found = true;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
			{
				Point w1 = whitePoints[whitePointsIndex[i]];
				Point w2 = whitePoints[whitePointsIndex[j]];
				Point b1 = blackPoints[i];
				Point b2 = blackPoints[j];

				if ((vect(w1, b1, w2) > EPSILON && vect(w1, b1, b2) < -EPSILON) || (vect(w1, b1, w2) < -EPSILON && vect(w1, b1, b2) > EPSILON))
					if ((vect(w2, b2, w1) > EPSILON && vect(w2, b2, b1) < -EPSILON) || (vect(w2, b2, w1) < -EPSILON && vect(w2, b2, b1) > EPSILON))
						found = false;
			}
	}

	Point tempPoints[N];
	for (int i = 0; i < n; i++)
		tempPoints[i] = whitePoints[i];

	for (int i = 0; i < n; i++)
		whitePoints[i] = tempPoints[whitePointsIndex[i]];
}

