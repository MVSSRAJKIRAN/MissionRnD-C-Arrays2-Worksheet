/*
OVERVIEW: You are given 2 bank statements that are ordered by date. 
Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.


ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/
#include <iostream>
#include<stdlib.h>
#include<stdio.h>
struct transaction {
	int amount;
	char date[11];
	char description[20];
};
void conversion(char *date, int **a, int k)
{
	int i = 0, j = 0, add = 0, t;
	while (date[i] != '\0')
	{
		if (date[i] != '-')
		{
			t = date[i] - 48;
			add *= 10;
			add = add + t;
		}
		else if (date[i] == '-')
		{
			printf("%d-", add);
			a[k][j++] = add;
			add = 0;
		}
		i++;
	}
	printf("%d\n", add);
	a[k][j] = add;
}
int forSameDate(int **a, int i, int **b, int j)
{
	int day1, day2, mon1, mon2, year1, year2;
	day1 = a[i][0]; mon1 = a[i][1]; year1 = a[i][2];
	day2 = b[j][0]; mon2 = b[j][1]; year2 = b[j][2];
	if (year1 == year2 && mon1 == mon2 && day1 == day2)
		return 0;
	else if (year1 <= year2)
	{
		if (mon1 <= mon2)
		{
			if (day1 <= day2)
				return 1;
			else
				return 2;
		}
		else
			return 2;
	}
	else
		return 2;
}
int common(int **a, int Alen, int **b, int Blen, int *indexArray)
{
	int i, j, k = 0, value = -1;
	for (i = 0, j = 0; i < Alen && j < Blen;)
	{
		value = forSameDate(a, i, b, j);
		if (value == 0)
		{
			indexArray[k++] = i;
			i++; j++;
		}
		else if (value == 1)
		{
			i++;
		}
		else if (value == 2)
		{
			j++;
		}
	}
	return k;
}
struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	int i, j, *a[10], *b[10], clength = 0, *carray;
	char *input;
	if (A == NULL || B == NULL)
		return NULL;
	else if (ALen == 1 && BLen == 1 && A[0].date == B[0].date)
	{
		for (i = 0; i < 11; i++)
		{
			if (A[0].date[i] != B[0].date[i])
				break;
		}
		if (i == 11)
			return A;
	}
	else
	{
		for (i = 0; i < ALen; i++)
			a[i] = (int *)malloc(3 * sizeof(int));
		for (i = 0; i < BLen; i++)
			b[i] = (int *)malloc(3 * sizeof(int));
		input = (char *)malloc(11 * sizeof(char));
		printf("Tr1\n");
		for (i = 0; i < ALen; i++)
		{
			for (j = 0; j < 11; j++)
				input[j] = A[i].date[j];
			input[j] = '\0';
			conversion(input, a, i);
		}
		printf("Tr2\n");
		for (i = 0; i < BLen; i++)
		{
			for (j = 0; j < 11; j++)
				input[j] = B[i].date[j];
			input[j] = '\0';
			conversion(input, b, i);
		}
		carray = (int *)malloc(20 * sizeof(int));
		clength = common(a, ALen, b, BLen, carray);

		if (clength == 0)
			return NULL;
		else
		{
			carray = (int *)realloc(carray, clength*sizeof(int));
			for (i = 0; i < clength; i++)
			{
				A[i] = A[carray[i]];
			}
			return A;
		}
	}
}