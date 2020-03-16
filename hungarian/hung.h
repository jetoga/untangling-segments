#ifndef HUNG_H_INCLUDED
#define HUNG_H_INCLUDED

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gen.h"
#ifndef EPSILON
#define EPSILON 0.000001
#endif // EPSILON

void print(double** M, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
        //    printf("%fl ", M[i][j]);
        }
        //printf("\n");
    }
}

/**
 * Metoda wêgierska
 * Algorytm przyporz±dkowuj±cy
 * optymalnie maszyny do zadañ
 * Z³o¿ono¶æ asymptotyczna O(n^3)
 */

/**
 * Funkcja obliczaj±ca dystans w geometri euklidesowej pomiêdzy punktami A i B
 */
double calculateDistance(Point A, Point B)
{
	return sqrt((A.x-B.x) * (A .x-B.x) + (A.y-B.y) * (A.y-B.y));
}

/**
 * Funkcja tworz±ca macierz odleg³o¶ci punktów z pierwszego zbioru w stosunku do punktów z drugiego zbioru
 */

void createDistanceMatrix(Point whitePoints[], Point blackPoints[], double** M, int n)
{
	for(int i = 0; i < n; i++)
		for(int j  = 0; j < n; j++)
			M[i][j] = calculateDistance(whitePoints[i], blackPoints[j]);

}

/**
 * Funkcja odejmuj±ca od ka¿dego elementu w danym wierszu najmniejszy element tego wiersza
 */

void substractRow(double** M, int n)
{
	for(int i = 0; i < n; i++)
	{
		double m = M[i][0];
		for(int j = 1; j < n; j++)
			m = m < M[i][j] ? m : M[i][j];
		for(int j = 0; j < n; j++)
			M[i][j] -= m;
	}
}

/**
 * Funkcja odejmuj±ca od ka¿dego elementu w danej kolumnie najmniejszy element tej kolumny
 */

void substractColumn(double** M, int n)
{
	for(int i = 0; i < n; i++)
	{
		double m = M[0][i];
		for(int j = 1; j < n; j++)
			m = m < M[j][i] ? m : M[j][i];
		for(int j = 0; j < n; j++)
			M[j][i] -= m;
	}
}

/**
 * Funkcja obliczaj±ca ilo¶æ zer w ka¿dym wierszu i w ka¿dej kolumnie macierzy, zwraca sumê zer w macierzy
 */

int calculateZero(double** M, int n, int zeroInRow[], int zeroInCol[])
{
	int totalZero = 0;
	for(int i = 0; i < n; i++)
	{
		zeroInRow[i] = 0;
		for(int j = 0; j < n; j++)
			if(M[i][j] > -EPSILON  && M[i][j] < EPSILON)
				zeroInRow[i]++;
		totalZero += zeroInRow[i];

	}

	for(int i = 0; i < n; i++)
	{
		zeroInCol[i] = 0;
		for(int j = 0; j < n; j++)
			if(M[j][i] > -EPSILON  && M[j][i] < EPSILON) zeroInCol[i]++;
	}

	return totalZero;
}

/**
 * Funkcja wybieraj±ca maksymalnie du¿± ilo¶æ zer niezale¿nych, zwraca ilo¶æ znalezionych zer niezale¿nych
 */


int pickZero(double** M, bool** P, int n, int totalZero, int zeroInRow[], int zeroInCol[])
{
	int s = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            P[i][j] = 0;
	bool markedRow[N];
	bool markedCol[N];
	for(int i = 0; i < n; i++)
        markedRow[i] = markedCol[i] = 0;
	while(totalZero != 0)
	{
		s++;
		//printf("Total zero: %d\n", totalZero);
		int m = totalZero + 1;
		int index_min;
		bool is_row = true;
		int index = -1;
		bool chosen = false;

		for(int i = 0; i < n; i++)
			if(markedRow[i] == 0 && zeroInRow[i] < m && zeroInRow[i] > 0)
			{
				m = zeroInRow[i];
				index_min = i;
			}

		for(int i = 0; i < n; i++)
			if(markedCol[i] == 0 && zeroInCol[i] < m && zeroInCol[i] > 0)
			{
				m = zeroInCol[i];
				index_min = i;
				is_row = false;
			}

		if(is_row)
		{
			markedRow[index_min] = 1;
			zeroInRow[index_min] = 0;

			for(int i = 0; i < n; i++)
			{
				if(M[index_min][i] > -EPSILON  && M[index_min][i] < EPSILON && markedCol[i] == 0)
				{
					totalZero--;
                    zeroInCol[i]--;
					if(!chosen)
					{
						index = i;
						chosen = true;
						//printf("Wiersz znaleziono (%d, %d)\n", index_min, i);
					}

				}
			}


			for(int i = 0; i < n; i++)
				if(M[i][index] > -EPSILON  && M[i][index] < EPSILON && markedRow[i] == 0)
                {
					totalZero--;
					zeroInRow[i]--;
                }

			markedCol[index] = 1;
			zeroInCol[index] = 0;
			P[index_min][index] = 1;

		}
		else
		{
			markedCol[index_min] = 1;
			zeroInCol[index_min] = 0;

			//printf("Poczatek");
			for(int i = 0; i < n; i++)
			{
				if(M[i][index_min] > -EPSILON  &&  M[i][index_min] < EPSILON && markedRow[i] == 0)
				{
					//printf("Dzialam");
					totalZero--;
					zeroInRow[i]--;
					if(!chosen)
					{
						index = i;
						chosen = true;
					}
				}
			}

			for (int i = 0; i < n; i++)
			{
				if(M[index][i] > -EPSILON && M[index][i] < EPSILON && markedCol[i] == 0)
				{
						totalZero--;
						zeroInCol[i]--;
				}
			}

			markedRow[index] = 1;
			zeroInRow[index]= 0;
			P[index][index_min] = 1;
		}
	}
//	printf("Ile zer: %d\n", s);
//	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(P[i][j]) printf("Wybrano: (%d, %d)\n", i, j);

	return s;
}

/**
 * Funkcja zakrywaj±ca zera niezale¿ne i dostosowuj±ca pozosta³± czê¶æ macierzy do powtórnego przej¶cia przez kolejn± iteracjê algorytmu
 */

void coverZero(double** M, bool** P, int n, int s)
{
    if(s == n) return;
    bool markedRow[N];
    bool markedCol[N];
    bool rowZeroPicked[N];
    bool onList[N];
    int toDoList[N];




    int first = 0, last = 0;

    for(int i = 0; i < n; i++)
        markedRow[i] = markedCol[i] = rowZeroPicked[i] = onList[i] = 0;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
         //   printf("%d - (%d, %d)\n", P[i][j], i, j);
            if(P[i][j] == 1)
            {
             //   printf("picked\n");
                rowZeroPicked[i] = 1;
            }
            //break;
        }

    for(int i = 0; i < n; i++)
        if(rowZeroPicked[i] == 0)
        {
            markedRow[i] = 1;
            toDoList[last++] = i;
        }


   // printf("Element: %d\nFirst: %d, last: %d\n", toDoList[first], first, last);
    while(first != last)
    {
    //    printf("Element: %d\nFirst: %d, last: %d\n", toDoList[first], first, last);
        for(int i = 0; i < n; i++)
        {
            if(M[toDoList[first]][i] > -EPSILON && M[toDoList[first]][i] < EPSILON && !P[toDoList[first]][i])
            {
                markedCol[i] = 1;
                for(int j = 0; j < n; j++)
                    if(M[j][i] > -EPSILON && M[j][i] < EPSILON && P[j][i] == 1)
                    {
                       // print(M, n);
                        if(!onList[j])
                        {
                            toDoList[last++] = j;
                          //  printf("Dodaje wiersz nr. %d vs toDoList[%d] = %d\n", j, last - 1, toDoList[last - 1]);
                            markedRow[j] = 1;
                            onList[j] = 1;
                        }
                    }
            }
        }
        first++;
    }

    for(int j = 0; j < n; j++)
            markedRow[j] = !markedRow[j];

    double m = -1;
    for(int i = 0; i < n; i++)
        for(int j = 1; j < n; j++)
        {
            if(m == -1 && !markedRow[i] && !markedCol[j])
                m = M[i][j];
            if(m != -1 && !markedRow[i] && !markedCol[j] && M[i][j] < m)
                m = M[i][j];
        }

    for(int i = 0; i < n; i++)
            if(!markedRow[i])
                for(int j = 0; j < n; j++)
                    M[i][j] -= m;

    for(int i = 0; i < n; i++)
            if(markedCol[i])
                for(int j = 0; j < n; j++)
                    M[j][i] += m;

    print(M, n);
}

/**
 * Funkcja wykonuj±ca algorytm wêgierski dla zbioru n par punktów w celu minimalizacji odleg³o¶ci pomiêdzy po³±czonymi punktami
 */

bool** doHungarianMatch(Point whitePoints[], Point blackPoints[], int n)
{
//    printf("Doing hung\n");
    int s = 0;
    int totalZero = 0;
    int zeroInRow[N];
    int zeroInCol[N];
    for(int i = 0; i < n; i++)
        zeroInCol[i] = zeroInRow[i] = 0;
    double** M = (double**)malloc(n * sizeof *M);
//    printf("Allocating\n");
    for (int i = 0; i < n; i++)
    {
        M[i] = (double*)malloc(n * sizeof(double));
    }

    bool** P = (bool**)malloc(n * sizeof *P);
    for (int i = 0; i < n; i++)
        P[i] = (bool*)malloc(n * sizeof(bool));

//    printf("Distance matrix\n");
    createDistanceMatrix(whitePoints, blackPoints, M, n);

//    printf(" %lf %lf %lf %lf\n %lf %lf %lf %lf\n %lf %lf %lf %lf\n %lf %lf %lf %lf\n", M[0][0], M[0][1], M[0][2], M[0][3], M[1][0], M[1][1], M[1][2], M[1][3], M[2][0], M[2][1], M[2][2], M[2][3], M[3][0], M[3][1], M[3][2], M[3][3]);

    substractRow(M, n);
    substractColumn(M, n);
    while(s != n)
    {
//        printf("Obieg while'a\n");
        totalZero = calculateZero(M, n, zeroInRow, zeroInCol);
        s = pickZero(M, P, n, totalZero, zeroInRow, zeroInCol);
        coverZero(M, P, n, s);
    }

    for(int i = 0; i < n; i++)
        free(M[i]);
    free(M);

    return P;
}

/**
 * Wypisywanie odpowiedzi
 */

void printAnswer(bool** P, Point whitePoints[], Point blackPoints[], int n)
{
/*    printf("Po³±czone punkty to:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(P[i][j] == 1)
                printf("Po³±czone punkty to: W[%d] oraz B[%d] (%lf, %lf) (%lf, %lf) \n", i, j, whitePoints[i].x, whitePoints[i].y, blackPoints[j].x, blackPoints[j].y);
*/
    for(int i = 0; i < n; i++)
        free(P[i]);
    free(P);

}

/**
 *
 */

 void matchPoints(Point whitePoints[], Point blackPoints[], int n)
 {
    bool** P = doHungarianMatch(whitePoints, blackPoints, n);
    printAnswer(P, whitePoints, blackPoints, n);

 }




#endif // HUNG_H_INCLUDED
