#include <iostream>
#include <stdio.h>
#include <random>
#include <math.h>

using namespace std;

#define xmax 8057
#define divider 1686
#define t 1.5455
#define c 0.3197
#define r 0.3868

int *array_constructor(int *&intPtr, int &size, int a, int b)
{
    if (size <= 0)
    {
        intPtr = nullptr;
        return intPtr;
    }
    else
    {
        default_random_engine generator;
        uniform_int_distribution<int> distribution(a, b);
        intPtr = new int[size];
        for (int i = 0; i < size; i++)
        {
            intPtr[i] = distribution(generator); //uniform distribution of a random number
        }
        distribution.reset();
        return intPtr;
    }
}

double seekTime(int position)
{
    double result;
    if (position < divider && position >= 1)
    {
        result = t + c * pow((position - 1), r);
    }
    else if (position >= divider)
    {
        result = (c * r * (position - divider)) / pow((divider - 1), (1 - r)) + t + c * pow((divider - 1), r);
    }
    else
    {
      return result;
    }
    return result;
}

int findNext(int *&intPtr, int currentPosition, int size)
{
    int minimum = 9000, index, difference;
    for (int i = 0; i < size; i++)
    {
        difference = abs(currentPosition - intPtr[i]);
        if (minimum > difference)
        {
            minimum = difference;
            index = i;
        }
    }
    return index;
}

int *arrayResize(int *&intPtr, int difference, int index, int size)
{
  if (size == 0)
  {
    return intPtr;
  }
  else if (difference == -1)
  {
    if (index == size)
    {
      size = size - 1;
      int *intPtrr = new int[size];
      for (int i = 0; i < size; i++)
      {
        intPtrr[i] = intPtr[i];
      }
      return intPtrr;
    }
    else
    {
      size = size - 1;
      for (int i = index; i < size; i++)
      {
        intPtr[i] = intPtr[i + 1];
      }
      int *intPtrr = new int[size];
      for (int i = 0; i < size; i++)
      {
        intPtrr[i] = intPtr[i];
      }
      return intPtrr;
    }
  }
  else
  {
    int *intPtrr = new int[size];
    for (int i = 0; i < index; i++)//index is the old array size
    {
      intPtrr[i] = intPtr[i];
    }
    return intPtrr;
  }

}

bool newArrival()
{
  int a = rand() % 3;
  if (a == 0)
    return true;
  return false;
}

int main()
{
    int *intPtr = nullptr;
    int oldSize = 20, currentIndex;
    int mincyl = 1;
    int runTimes = 10000;
    int x = (rand() % (xmax - mincyl + 1)) + mincyl; //random initial position
    array_constructor(intPtr, oldSize, mincyl, xmax);
    double totalTime = 0.0;
    long long totalDistance = 0;
    for (int i = 0; i < runTimes; i++)
    {

      if (newArrival())
      {
        int arrival = rand() % 4 + 1;
        int newSize = oldSize + arrival;
        arrayResize(intPtr, 1, oldSize, oldSize + arrival);
        default_random_engine generator;
        uniform_int_distribution<int> distribution(mincyl, xmax);
        for (int i = oldSize - 1; i < newSize; i++)
        {
          intPtr[i] = distribution(generator);
        }
        oldSize = newSize;
      }
      else
      {
        currentIndex = findNext(intPtr, x, oldSize);
        totalTime = totalTime + seekTime(abs(x - intPtr[currentIndex]));;
        totalDistance = totalDistance + abs(x - intPtr[currentIndex]);
        x = intPtr[currentIndex];
        arrayResize(intPtr, -1, currentIndex, oldSize);
        oldSize--;
      }
    }
    cout << "Average seek time is " << totalTime / runTimes << "ms for a initial Q value of: " << oldSize << endl;
    cout << "Average seek distance is " << totalDistance / runTimes << "cyl for a initial Q value of: " << oldSize << endl;

    //push into queue
    //new element flag up
    //pop everything into array
    //new element flag down
    //findNext()
    //push into queue
    //new element flag up
    //append into existing array
    //findNext()
}