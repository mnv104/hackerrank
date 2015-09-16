#include <string>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <getopt.h>
#include <cstdio>
#include <vector>
#include <set>
#include <memory>
#include <utility>
#include <functional>

using namespace std;

class State {
public:
   typedef std::shared_ptr<State> ptr;
   struct Character {
      char ch;
      int  count;
      Character(char _ch, int _count) : ch(_ch), count(_count) { }
   };
   struct Transition {
      typedef std::shared_ptr<Transition> ptr;
      std::pair<Character, int> t;
      Transition(char ch, int count, int nextState) : t(std::make_pair(Character(ch, count), nextState)) { }
   };
   std::vector<Transition::ptr> transitions;
   void addTransition(char a, int count, int nextState) {
      Transition::ptr transition = std::make_shared<Transition>(a, count, nextState);
      std::vector<Transition::ptr>::iterator it =
         transitions.begin();
      bool insertBack = true;
      while (it != transitions.end()) {
         Transition::ptr tn = *it;
         if (tn->t.first.ch == a) {
            assert(count != tn->t.first.count);
            if (count == 1) {
               insertBack = false;
            }
            break;
         }
         it++;
      }
      if (insertBack) {
         transitions.push_back(transition);
      } else {
         transitions.insert(transitions.begin(), transition);
      }
   }
   int lookupNextState(char a, int &count) {
      std::vector<Transition::ptr>::const_iterator it = transitions.cbegin();
      while (it != transitions.cend()) {
         Transition::ptr tn = *it;
         if (tn->t.first.ch == a) {
            if (count == 1 || tn->t.first.count == 0) {
               return tn->t.second;
            }
            count = 1;
            return tn->t.second;
         }
         it++;
      }
      return -1;
   }
   bool terminalState;
   State(bool _terminalState = false) : terminalState(_terminalState) { }
};

ostream &
operator <<(ostream &s, const State &st)
{
   for (auto tn: st.transitions) {
      s << " ->" << tn->t.first.ch << "(" << tn->t.first.count << ")->" <<
         tn->t.second << endl;
   }
   return s;

}

class StateMachine {
public:
   bool matchAll;
   typedef std::shared_ptr<StateMachine> ptr;
   std::vector<State::ptr> states;
   State::ptr initState;
   struct Tokens {
      char ch;
      int count;
      Tokens(char _ch, int _count) : ch(_ch), count(_count) { }
   };
   static std::vector<Tokens> tokenizeRegex(const std::string &regex,
                                            std::string::size_type &pos,
                                            int &numStars);
   static void
   gobbleCharacters(const std::string &s, const std::string::size_type &pos,
                    int &numMatches);

   static StateMachine::ptr compileRegex(const std::string &regex);
   bool matchString(const std::string &s);
   StateMachine(bool _matchAll): matchAll(_matchAll) { }
};

ostream &
operator <<(ostream &s, const StateMachine &sm)
{
   unsigned int i = 0;
   for (auto st: sm.states) {
      s << "State " << i;
      if (st->terminalState) {
         s << " (Terminal)";
      }
      s << endl;
      s << *st << endl;
      i++;
   }
   return s;
}

std::vector<StateMachine::Tokens>
StateMachine::tokenizeRegex(const std::string &regex,
                            std::string::size_type &pos,
                            int &numStars)
{
   unsigned int l = regex.size();
   vector<StateMachine::Tokens> v;
   if (pos >= l) {
      return v;
   }
   int count = 0;
   unsigned int i = pos;
   while (i < l) {
      if ((i+1) >= l || regex[i+1] != '*') {
         StateMachine::Tokens t(regex[i], 1);
         v.push_back(t);
         i++;
         break;
      } else {
         StateMachine::Tokens t(regex[i], 0);
         v.push_back(t);
         i += 2;
         count++;
      }
   }
   pos = i;
   numStars = count;
   return v;
}


StateMachine::ptr
StateMachine::compileRegex(const std::string &r)
{
   bool matchAll;
   matchAll = (r.length() == 1 && r[0] == '*');
   StateMachine::ptr sm = std::make_shared<StateMachine>(matchAll);
   unsigned int numStates = 0;
   std::vector<StateMachine::Tokens> v;
   std::string::size_type pos = 0;
   State::ptr s;
   s = std::make_shared<State>();
   sm->states.push_back(s);
   numStates++;
   do {
      int numStars = 0;
      bool finalStates;
      v = tokenizeRegex(r, pos, numStars);
      finalStates = (numStars == v.size());
      size_t l = v.size();
      for (unsigned int i = 0; i < l; i++) {
         s->addTransition(v[i].ch, v[i].count, numStates + i);
         State::ptr next = std::make_shared<State>(finalStates);
         if (i < numStars) {
            for (unsigned int j = i + 1; j < l; j++) {
               next->addTransition(v[j].ch, v[j].count, numStates + j);
            }
         }
         sm->states.push_back(next);
      }
      s = sm->states.back();
      numStates = sm->states.size();
   } while (v.size() != 0);
   sm->initState = sm->states[0];
   sm->states.back()->terminalState = true;
   return sm;
}

void
StateMachine::gobbleCharacters(const std::string &s,
                               const std::string::size_type &pos,
                               int &numSame)
{
   unsigned int l = s.length();
   int count = 1;
   if (pos >= l) {
      numSame = 0;
      return;
   }
   unsigned int i = pos + 1;
   char c = s[pos];

   while (i < l) {
      if (s[i] == c) {
         count++;
      } else {
         break;
      }
      i++;
   }
   numSame = count;
}

bool
StateMachine::matchString(const std::string &s)
{
   if (matchAll) {
      return true;
   }
   State::ptr state = initState;
   if (state == nullptr) {
      return false;
   }
   std::string::size_type pos = 0;
   unsigned int l = s.length();
   int countSimilar;
   while (pos < l) {
      gobbleCharacters(s, pos, countSimilar);
      if (countSimilar == 0) {
         break;
      }
      int nextState;
      nextState = state->lookupNextState(s[pos], countSimilar);
      pos += countSimilar;
      cout << s[pos-1] << "(" << countSimilar << ") " << nextState << endl;
      if (nextState == -1) {
         return false;
      }
      if (nextState >= states.size()) {
         return false;
      }
      state = states[nextState];
   }
   return state->terminalState;
}


int main(int argc, char *argv[])
{
   int c;
   std::string regEx, str;
   while ((c = getopt(argc, argv, "r:s:")) != EOF) {
      switch (c) {
         case 'r':
            regEx = optarg;
            break;
         case 's':
            str = optarg;
            break;
         default:
            cerr << "Usage: " << argv[0] << " -r <regex> " << " -s <string to match" << endl;
            exit(1);
      }
   }
   if (regEx.length() == 0 || str.length() == 0) {
      cerr << "Usage: " << argv[0] << " -r <regex> " << " -s <string to match" << endl;
      exit(1);
   }
   StateMachine::ptr sm = StateMachine::compileRegex(regEx);
   cout << *sm << endl;
   cout << sm->matchString(str) << endl;
   return 0;
}
