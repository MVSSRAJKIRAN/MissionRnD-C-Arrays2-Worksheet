/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};
int check(int **arrDates, int *date, int len)
{
	//arrDates[i][0]=day..[i][1]=month..[i][2]=year//
	int i = 0, count = 0;
	while (i < len)
	{
		if (arrDates[i][2] >= date[2])
			break;
		i++;
	}
	if (i == len)
		return 0;
	else if (arrDates[i][2]>date[2])
		return len - i;
	else if (arrDates[i][2] == date[2])
	{
		while (i < len && arrDates[i][2] == date[2])
		{
			if (arrDates[i][1] >= date[1])
				break;
			i++;
		}
		if (i == len)
			return 0;
		while (i < len && arrDates[i][1] == date[1])

		{
			if (arrDates[i][0] > date[0])
				break;
			i++;
		}
		if (i == len)
			return 0;
		else
			return len - i;
	}

}
void convert(char *date, int **a, int k)
{	//date[i][0]=day, date[i][1]=month ,date[i][2]=year
	int i = 0, j = 0, sum = 0, t;
	while (date[i] != '\0')
	{
		if (date[i] != '-')
		{
			t = date[i] - 48;
			sum *= 10;
			sum = sum + t;

		}
		else if (date[i] == '-')
		{

			a[k][j++] = sum;
			sum = 0;
		}
		i++;
	}

	a[k][j] = sum;

}

int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	int *a[100], i = 0, j = 0, t, *inputDate;
	char *input;
	inputDate = (int *)malloc(3 * sizeof(int));
	input = (char *)malloc(11 * sizeof(char));
	for (i = 0; i<len; i++)
	{
		a[i] = (int *)malloc(3 * sizeof(int));
	}
	convert(date, a, 0);
	printf("input=%s\n", date);
	inputDate[0] = a[0][0]; inputDate[1] = a[0][1]; inputDate[2] = a[0][2];
	for (i = 0; i < len; i++)
	{

		for (j = 0; j < 11; j++)
		{
			input[j] = Arr[i].date[j];
			printf("%c", input[j]);
		}
		printf("\n");

		input[j] = '\0';
		convert(input, a, i);

	}
	t = check(a, inputDate, len);
	printf("\ncount=%d", t);

	return t;
}