/*  Dustin Wolf
	September 5, 2013
	Assignment 1 
	Computer Graphics

	This program takes in img 3d points and puts them into an array.
	it prints out the array and finds the mean of x y and z
	each method description is below
*/
#include <stdio.h>
#include "Vector.h"
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/*  mean double ( vector pointer, size integer, character char)
 *  pass in the vector array and the character that you want to get the mean of
 *  adds all of them up and then divides by the size and returns the mean */
double mean(Vector * v, int size, char character)
{
	double mean = 0;
	for(int i = 0; i < size; i ++)
	{
		// if character is an x
		if(character == 'x')
			mean += v[i].x;
		// if character is a y
		else if(character == 'y')
			mean += v[i].y;
		// if character is a z
		else if(character == 'z')
			mean += v[i].z;
	}
	// returns mean
	return mean / size;
}

/*  main method, creates an ifstream, asks user for the name of the file
 *  finds the size of the file, then reads its line by line
 *  tokenizes by a space and puts the values into the vector struct
 *  a file pointer then prints out the values in reverse order.
 *  followed by the mean function called for each of the x, y, z coordinates
 */
int main()
{
	// local variable declaration
	int count = 0;
	char data[100];

	// creates ifstream
	ifstream infile;

	// prompts user for filename
	cout << "Enter the file name: ";
	cin >> data;
	// opens the file
	infile.open(data);

	// if the file is good
	if(infile.good())
	{
		string line;
		while (infile)
		{
			// read line
			getline(infile, line);
			// if the character is not a j J or an empty line
			if(!(line[0] == 'J' || line[0] == 'j' || line == ""))
				// add to a counter
				count++;
		}
	}
	else
	{
		// if the file is broken or 404 
		cout << "Error loading file..." << endl;
		system("pause");
		exit(0);
	}

	// creates vector array at the size of the file
	Vector* v = new Vector[count];

	// clears the progress of the read
	infile.clear();
	// reverts the pointer back to begining of file
	infile.seekg(0, ios::beg);

	// if file is still good
	if(infile.good())
	{
		string line;
		char * pch;
		int counter = 0;
		while (infile)
		{
			// read line
			getline(infile, line);
			if(!(line[0] == 'J' || line[0] == 'j' || line == ""))
			{
				// convert to char *
				char *dup = strdup(line.c_str());
				// split by " " and add to x, y , z
				pch = strtok(dup, " ");
				v[counter].x = atof(pch);
				pch = strtok (NULL, " ");
				v[counter].y = atof(pch);
				pch = strtok (NULL, " ");
				v[counter].z = atof(pch);

				counter++;
			}
		}
	}

	// creates the name for the output file
	char * out = strtok(data, ".");
	FILE *fp;

	// open an output file
	fp = fopen(strcat(out, ".out"), "w");

	// loop through the vector array and print it out from last to first
	for(int i = count-1; i >= 0; i--)
		fprintf(fp, "%.1f %.1f %.1f \n", v[i].x, v[i].y, v[i].z);

	// find the mean for x y z
	fprintf(fp, "Mean X-Coordinate =  %.1f\n", mean(v, count, 'x'));
	fprintf(fp, "Mean Y-Coordinate =  %.1f\n", mean(v, count, 'y'));
	fprintf(fp, "Mean Z-Coordinate =  %.1f\n" ,mean(v, count, 'z'));

	// flush and close
	fflush(fp);
	fclose(fp);

	system("pause");
}