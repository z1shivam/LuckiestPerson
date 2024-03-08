#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Globals
int tossCount = 0;
int stepCount = 0;

// Function to create an array
int *createArray(int length)
{
  int *newArray = (int *)malloc(length * sizeof(int));
  for (int i = 0; i < length; i++)
    newArray[i] = i + 1;
  return newArray;
}

// Function to split the array into two
void splitTheArray(int *inputArr, int length, int **subArr1, int **subArr2)
{
  int subArrLen = length / 2;
  *subArr1 = (int *)malloc(subArrLen * sizeof(int));
  *subArr2 = (int *)malloc(subArrLen * sizeof(int));

  for (int i = 0; i < subArrLen; i++)
  {
    (*subArr1)[i] = inputArr[i];
    (*subArr2)[i] = inputArr[i + subArrLen];
  }
}

// Function to remove tails
int *removeTails(int *inputArr, int length)
{
  int *newArray = (int *)malloc(length * sizeof(int));
  int index = 0;
  for (int i = 0; i < length; i++)
  {
    if (inputArr[i] != 0)
    {
      newArray[index] = inputArr[i];
      index++;
    }
  }
  return newArray;
}

// Function to simulate a toss
char toss()
{
  tossCount++;
  return rand() % 2 == 1 ? 'H' : 'T';
}

// Function to divide and toss
int *divideAndToss(int *inputArr, int length)
{
  int *wonPeople = (int *)malloc(length * sizeof(int));
  int *subArr1;
  int *subArr2;

  splitTheArray(inputArr, length, &subArr1, &subArr2);

  for (int i = 0; i < length / 2; i++)
  {
    char tossResult = toss();
    tossResult == 'H' ? (wonPeople[i] = subArr1[i]) : (wonPeople[i] = subArr2[i]);
  }

  free(subArr1);
  free(subArr2);
  return wonPeople;
}

int main()
{
  srand((unsigned)time(NULL));
  int numberOfPeople = 1000;
  int *peopleArray = createArray(numberOfPeople);

  // The step loop
  while (numberOfPeople > 1)
  {
    stepCount++;

    if (numberOfPeople % 2 != 0)
    {
      int lastEl = peopleArray[numberOfPeople - 1];
      peopleArray[numberOfPeople - 1] = 0;
      int *newPeopleArray = divideAndToss(peopleArray, numberOfPeople - 1);

      if (toss() == 'H')
      {
        newPeopleArray[numberOfPeople - 1] = lastEl;
      }

      free(peopleArray);
      peopleArray = newPeopleArray;
    }
    else
    {
      int *newPeopleArray = divideAndToss(peopleArray, numberOfPeople);

      free(peopleArray);
      peopleArray = newPeopleArray;
    }

    numberOfPeople = numberOfPeople / 2 + numberOfPeople % 2;
  }

  printf("The Winner: %d\nTotal Heads: %d\nTotal Toss: %d\n", peopleArray[0], stepCount, tossCount);

  free(peopleArray);

  return 0;
}
