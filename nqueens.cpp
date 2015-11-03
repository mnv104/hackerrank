#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

bool isSafe(std::vector<std::vector<int>> &v,
            int N, int row, int column)
{
   for (int i = 0; i < column; i++) {
      if (v[row][i] == 1) {
         return false;
      }
   }

   for (int i = row, j = column; i >= 0 && j >= 0; i--,j--) {
      if (v[i][j] == 1) {
         return false;
      }
   }
   for (int i = row, j = column; i < N && j >= 0; i++, j--) {
      if (v[i][j] == 1) {
         return false;
      }
   }
   return true;
}

bool solveNQueen(std::vector<std::vector<int>> &v,
                 int N,
                 int column)
{
   if (column >= N) {
      return true;
   }
   for (int i = 0; i < N; i++) {
      if (isSafe(v, N, i, column)) {
         v[i][column] = 1;
         if (solveNQueen(v, N, column + 1) == true) {
            return true;
         }
         v[i][column] = 0;
      }
   }
   return false;
}

int main(int argc, char *argv[])
{
   std::vector<std::vector<int>> state;
   int N = 4;
   if (argc > 1) {
      N = atoi(argv[1]);
   }
   state.resize(N);
   for (unsigned int i = 0; i < N; i++) {
      state[i].resize(N);
      for (unsigned int j = 0; j < N; j++) {
         state[i][j] = 0;
      }
   }
   try {
      solveNQueen(state, N, 0);
      for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {
            cout << state[i][j] << " ";
         }
         cout << endl;
      }
      cout << endl;
   } catch (const std::exception &e) {
      cout << "No solution exists" << endl;
   }
   return 0;
}
