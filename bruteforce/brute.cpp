#include <iostream>
#include <ctime>
#include <getopt.h>
#include "gen.h"
#include "brute.h"
using namespace std;

int complexity2(int n)
{
	if(n == 1) return 1;
	return n * complexity2(n - 1);
}

int complexity(int n)
{
	return n * n * complexity2(n);
}

void printUsage() 
{
   cout << "Usage: brute -t number of tests -r number of repeats -j length of jump -n number of points -g required for autogeneration\n";

}

int main(int argc, char *argv[])
{


	int n = 1;
	int repeat = 1;
	int tests = 1;
	int jump = 1;
	bool consoleInput = true;

	int option = 0;
	// Obsługa parametrów
	while((option = getopt(argc, argv,"hgr:t:j:n:")) != -1)
	{
		if(option == 'h') {printUsage(); return 0;}
		if(option == 'g') consoleInput = false;
		if(option == 'r') repeat = atoi(optarg);
		if(option == 't') tests = atoi(optarg);
		if(option == 'j') jump = atoi(optarg);
		if(option == 'n') n = atoi(optarg);
	}

	if(n + tests > N) 
	{
		cout << "Exceeded the limit of " << N << ".\n";
		return 0;
 	}

	Point whitePoints[N], blackPoints[N];


	if(consoleInput)
	{
		cout << "Specify the number of pairs of points:\n";
		cin >> n;
		cout << "Fill in the black points:\n";
		for(int i = 0; i < n; i++)
		{
			cout << "Specify the x coordinate:\n";
			cin >> blackPoints[i].x;
			cout << "Specify the y coordinate:\n";
			cin >> blackPoints[i].y;
		}
		cout << "Fill in the white points:\n";
		for(int i = 0; i < n; i++)
		{
			cout << "Specify the x coordinate:\n";
			cin >> whitePoints[i].x;
			cout << "Specify the y coordinate:\n";
			cin >> whitePoints[i].y;

		}

		brute(whitePoints, blackPoints, n);

		for(int i = 0; i < n; i++)
			cout << "(" << whitePoints[i].x << ", " << whitePoints[i].y << "), (" << blackPoints[i].x << ", " << blackPoints[i].y << ")\n";

		return 0;
	}

	// Testowanie
	srand(time(NULL));
	double meanTime[N];
	for(int i = 0; i < n; i++) meanTime[i] = 0;
	for(int t = 0; t < tests; t++)
	{
		for(int r = 0; r < repeat; r++)
		{
			generatePoints(whitePoints, blackPoints, n + t * jump);
		
			clock_t start_time = clock();

			brute(whitePoints, blackPoints, n + t * jump);
			clock_t end_time = clock();

			meanTime[t] += ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
		}

		meanTime[t] = meanTime[t] / repeat * 1000;
	}

	// Wyliczanie mediany
	double nMediana;
	double tMediana;
	double cMediana;

	if(tests % 2)
	{
		nMediana = n + tests / 2 * jump;
		tMediana = meanTime[tests / 2];
		cMediana = complexity(nMediana);
	}
	else
	{
		nMediana = n + (tests / 2 + (tests / 2 - 1)) / 2 * jump;
		tMediana = (meanTime[tests / 2] + meanTime[tests / 2 - 1]) / 2;
		cMediana = (complexity(n + tests / 2 * jump) + complexity(n + (tests / 2 - 1) * jump)) / 2;
	}

	cout << "n\t|t(n)\t|q(n)\n";
	for(int t = 0; t < tests; t++)
	{
	   cout << n + t * jump << "\t|" << meanTime[t] << "\t|" << (double)meanTime[t] * cMediana / (tMediana * complexity(n + t * jump)) << "\n";
	}

	return 0;
}

