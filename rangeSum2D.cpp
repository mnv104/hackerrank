#include <vector>
#include <stdexcept>
#include <list>
#include <iostream>

using namespace std;

class NumMatrix {
public:
    vector<vector<int>> v;
    vector<vector<int>> cumSum;
    NumMatrix(vector<vector<int>> &matrix) : v(matrix) {
        cumSum.resize(matrix.size());
        for (unsigned int i = 0; i < matrix.size(); i++) {
            cumSum[i].resize(matrix[i].size());
        }
        for (int i = 0; i < matrix.size(); i++) {
          int total = 0;
          for (unsigned int j = 0; j < matrix[i].size(); j++) {
              total += v[i][j];
              cumSum[i][j] = total;
          }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int total = 0;
        for (int j = row1; j <= row2; j++) {
            total += cumSum[j][col2] - cumSum[j][col1] + v[j][col1];
        }
        return total;
    }
};

void func1()
{
#define ROW 5
#define COL 5
   int a[ROW][COL] = {{3,0,1,4,2},{5,6,3,2,1},
                  {1,2,0,1,5},{4,1,0,1,7},
                  {1,0,3,0,5}};
   vector<vector<int>> v;
   v.resize(ROW);
   for (int i = 0; i < ROW; i++) {
      v[i].resize(COL);
   }
   for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
         v[i][j] = a[i][j];
      }
   }
   NumMatrix num1(v);
   cout << num1.sumRegion(2,1,4,3) << endl;
   cout << num1.sumRegion(1,1,2,2) << endl;
   cout << num1.sumRegion(1,2,2,4) << endl;
   return;
}


int main()
{
   func1();
   return 0;
}
