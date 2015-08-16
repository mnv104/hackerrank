#include <stdio.h>
#include <set>
#include <stdlib.h>
#include <iostream>
using namespace std;

void
display(int numRows, int numColumns, int **m)
{
   cout << "Matrix is " << endl;
   for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
         cout << m[i][j] << " ";
      }
      cout << endl;
   }
}

void
rowColZero(int numRows, int numColumns, int **m)
{
   set<int> s;
   for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
         std::set<int>::iterator it;
         it = s.find(j);
         if (it != s.end()) {
            continue;
         }
         if (m[i][j] == 0) {
            for (int k = 0; k < numColumns; k++) {
               m[i][k] = 0;
            }
            for (int k = 0; k < numRows; k++) {
               m[k][j] = 0;
            }
            s.insert(j);
         }
      }
   }
}


int main(void)
{
   int numRows, numColumns;
   cout << "Enter number of rows:";
   cin >> numRows;
   cout << "Enter number of columns:";
   cin >> numColumns;
   int **m;
   m = (int **) calloc(1, numRows * sizeof *m);
   if (m == NULL) {
      return -1;
   }
   for (int i = 0; i < numRows; i++) {
      m[i] = (int *) calloc(1, numColumns * sizeof **m);
      if (m[i] == NULL) {
         return -1;
      }
   }
   for (int i = 0; i < numRows; i++) {
      cout << "Please enter " << numColumns << " elements of row " << i << endl;
      for (int j = 0; j < numColumns; j++) {
         cin >> m[i][j];
      }
   }
   display(numRows, numColumns, m);
   rowColZero(numRows, numColumns, m);
   display(numRows, numColumns, m);
   return 0;
}
