#include <string>
#include <set>
#include <stdint.h>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

using namespace std;
enum {
   LEFT = 0,
   RIGHT = 1,
};

class Balance {
public:
   static const int weight = 10;
   int id;
   int totalWeight;
   bool leafNode;
   int currentWeight[2];
   int addedWeight[2];
   std::set<int> otherBalances[2];
   Balance() : totalWeight(0), id(-1) {
      for (int i = 0; i < 2; i++) {
         currentWeight[i] = 0;
         addedWeight[i] = 0;
         leafNode = true;
      }
   }
};

uint32_t numBalances = 0;
Balance *allBalances;

void readInput()
{
   {
      std::string line;
      if (getline(cin, line) == 0) {
         throw std::invalid_argument("Bad line");
      }
      std::stringstream ss;
      ss << line;
      ss >> numBalances;
      if (numBalances <= 0) {
         throw std::invalid_argument("Bad number of balances");
      }
   }
   allBalances = new Balance[numBalances]();
   for (int i = 0; i < 2 * numBalances; i++) {
      std::string line;
      if (getline(cin, line) == 0) {
         throw std::invalid_argument("Bad line");
      }
      std::stringstream ss;
      ss << line;
      int weight;
      std::set<int> balances;
      ss >> weight;
      int b;
      while (ss >> b) {
         balances.insert(b);
      }
      Balance *balance = &allBalances[i / 2];
      balance->id = i / 2;
      balance->currentWeight[i % 2] = weight;
      balance->otherBalances[i % 2] = balances;
      if (balances.size() != 0) {
         balance->leafNode = false;
      }
      if ((i % 2) != 0 && balance->leafNode == true) {
         if (balance->currentWeight[LEFT] > balance->currentWeight[RIGHT]) {
            balance->addedWeight[LEFT] = 0;
            balance->addedWeight[RIGHT] = balance->currentWeight[LEFT] -
               balance->currentWeight[RIGHT];
         } else if (balance->currentWeight[LEFT] < balance->currentWeight[RIGHT]) {
            balance->addedWeight[RIGHT] = 0;
            balance->addedWeight[LEFT] = balance->currentWeight[RIGHT] -
               balance->currentWeight[LEFT];
         }
         balance->totalWeight = Balance::weight +
            balance->addedWeight[LEFT] + balance->addedWeight[RIGHT] +
            balance->currentWeight[LEFT] + balance->currentWeight[RIGHT];
      }
   }
   bool needOneMoreLoop;
repeat:
   needOneMoreLoop = false;
   for (int i = 0; i < numBalances; i++) {
      Balance *balance = &allBalances[i];
      if (balance->leafNode == true) {
         for (int j = 0; j < numBalances; j++) {
            Balance *thisBalance = &allBalances[j];
            if (j != i) {
               std::set<int>::iterator it;
               it = thisBalance->otherBalances[LEFT].find(i);
               if (it == thisBalance->otherBalances[LEFT].end()) {
                  it = thisBalance->otherBalances[RIGHT].find(i);
                  if (it == thisBalance->otherBalances[RIGHT].end()) {
                     continue;
                  }
                  thisBalance->currentWeight[RIGHT] += balance->totalWeight;
                  thisBalance->otherBalances[RIGHT].erase(it);
               } else {
                  thisBalance->currentWeight[LEFT] += balance->totalWeight;
                  thisBalance->otherBalances[LEFT].erase(it);
               }
            }
         }
      }
   }
   for (int i = 0; i < numBalances; i++) {
      Balance *balance = &allBalances[i];
      if (balance->leafNode != true) {
         if (balance->otherBalances[LEFT].size() == 0 &&
            balance->otherBalances[RIGHT].size() == 0) {
               balance->leafNode = true;
               if (balance->currentWeight[LEFT] > balance->currentWeight[RIGHT]) {
                  balance->addedWeight[LEFT] = 0;
                  balance->addedWeight[RIGHT] = balance->currentWeight[LEFT] -
                     balance->currentWeight[RIGHT];
               } else if (balance->currentWeight[LEFT] < balance->currentWeight[RIGHT]) {
                  balance->addedWeight[RIGHT] = 0;
                  balance->addedWeight[LEFT] = balance->currentWeight[RIGHT] -
                  balance->currentWeight[LEFT];
               }
               balance->totalWeight = Balance::weight +
                  balance->addedWeight[LEFT] + balance->addedWeight[RIGHT] +
                  balance->currentWeight[LEFT] + balance->currentWeight[RIGHT];
         } else {
            needOneMoreLoop = true;
         }
      }
   }
   if (needOneMoreLoop) {
      goto repeat;
   }
   for (int i = 0; i < numBalances; i++) {
      Balance *balance = &allBalances[i];
      cout << balance->id << ": ";
      if (balance->leafNode) {
         cout << balance->addedWeight[LEFT] << " ";
         cout << balance->addedWeight[RIGHT];
      } else {
      }
      cout << endl;
   }
   delete [] allBalances;
}


int main(int argc, char *argv[])
{
   readInput();
   return 0;
}
