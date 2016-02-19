#include <string>
#include <stdexcept>
#include <stdint.h>
#include <map>
#include <assert.h>
#include <stack>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>

using namespace std;

typedef int topicID;


bool
isPrefix(const std::string &word1, const std::string &word2)
{
   return std::equal(word1.begin(),
                     word1.begin() + std::min(word1.size(), word2.size()),
                     word2.begin());
}

class wordTrie {
   struct wordTrieNode {
      std::map<std::string, wordTrieNode *> child;
   };
   wordTrieNode *root;
public:
   void
   addWordsInSentence(const std::string &question) {
      stringstream ss;
      ss << question;
      string word;
      wordTrieNode *node = root;
      while (ss >> word) {
         try {
            node = node->child.at(word);
         } catch (const std::out_of_range &e) {
            node->child[word] = new wordTrieNode();
            node = node->child.at(word);
         }
      }
   }
   wordTrie() {
      root = new wordTrieNode();
   }
   ~wordTrie() {
   }
   bool
   isWordPresent(wordTrieNode **pnode, const std::string &word, bool doPrefix=false) {
      wordTrieNode *node = *pnode;
      try {
         *pnode = node->child.at(word);
         return true;
      } catch (const std::out_of_range &e) {
         if (doPrefix) {
            std::map<std::string, wordTrieNode *>::iterator mit = node->child.begin();
            while (mit != node->child.end()) {
               if (isPrefix((*mit).first, word)) {
                  *pnode = (*mit).second;
                  return true;
               }
               mit++;
            }
         }
         return false;
      }
   }
   bool
   areWordsPresentInSentence(const std::string &question) {
      stringstream ss;
      ss << question;
      string word;
      bool doPrefix = false;
      wordTrieNode *node = root;
      while (ss >> word) {
         if (doPrefix) {
            return false;
         }
         if (!isWordPresent(&node, word, doPrefix)) {
            doPrefix = true;
            if (!isWordPresent(&node, word, doPrefix)) {
               return false;
            }
         }
      }
      return true;
   }
   void
   showWordsInt(wordTrieNode *node) {
      std::map<std::string, wordTrieNode *>::iterator witer = node->child.begin();
      while (witer != node->child.end()) {
         cout << (*witer).first << " " << endl;
         showWordsInt((*witer).second);
         witer++;
      }
   }
   void
   showWords() {
      showWordsInt(root);
   }
};

struct topics {
   string topicName;
   topicID id;
   std::vector<topicID> subTopics;
   wordTrie wt;
   topics(topicID _id, const std::string &_topicName): topicName(_topicName), id(_id) {
   }
   void
   addSubTopic(topicID subTopicID) {
      subTopics.push_back(subTopicID);
   }
   void
   addQuestion(const std::string &question) {
      wt.addWordsInSentence(question);
   }
   void
   showQuestions() {
      wt.showWords();
   }
   bool
   isQueryMatch(const std::string &question) {
      return wt.areWordsPresentInSentence(question);
   }
};

ostream &operator<<(ostream &os, const topics &r)
{
   os << r.topicName;
   return os;
}


class Topics {
   std::vector<topics> allTopics;
   topicID idCounter;
   topicID startID;
   std::map<string, topicID> m;
public:
   Topics(): idCounter(0), startID(-1) {
   }
   ~Topics() {
   }
   topicID
   addNewTopic(const std::string &topicName) {
      if (startID == -1) {
         startID = idCounter;
      }
      allTopics.push_back(topics(idCounter++, topicName));
      try {
         m.at(topicName);
      } catch (const std::out_of_range &e) {
         m[topicName] = idCounter - 1;
      }
      return idCounter-1;
   }
   topicID
   operator+=(const std::string &topicName) {
      return addNewTopic(topicName);
   }
   topics&
   getTopic(topicID id) {
      return allTopics.at(id);
   }
   topics&
   operator[](topicID id) {
      return getTopic(id);
   }
   void
   clear() {
      if (startID != -1) {
         allTopics.clear();
         m.clear();
         startID = -1;
         idCounter = 0;
      }
   }
   void
   parseTopicInput(const std::string &topicStr)
   {
      clear();
      stringstream ss;
      ss << topicStr;
      std::string t;
      std::stack<topicID> topicStack;
      topicID lastID = -1;
      while (ss >> t) {
         if (t != "(" && t != ")") {
            topicID id;
            id = addNewTopic(t);
            if (topicStack.size() > 0) {
               topicID parentID = topicStack.top();
               topics& parentTopic = getTopic(parentID);
               parentTopic.addSubTopic(id);
            }
            lastID = id;
         } else {
            if (t == "(") {
               assert(lastID != -1);
               topicStack.push(lastID);
               lastID = -1;
            } else {
               topicStack.pop();
            }
         }
      }
   }
   struct qNode {
      int level;
      topicID tid;
      qNode(int _level, topicID _tid): level(_level), tid(_tid) { }
   };

   void
   display() {
      if (startID == -1) {
         cout << "No topics added " << endl;
         return;
      }
      std::deque<qNode> q;
      int level = 0;
      q.push_back(qNode(startID, 0));
      while (!q.empty()) {
         qNode qN = q.front();
         topics &tp = getTopic(qN.tid);
         if (level != qN.level) {
            cout << endl;
            level = qN.level;
         }
         cout << tp << " ";
         q.pop_front();
         std::vector<topicID>::iterator it = tp.subTopics.begin();
         while (it != tp.subTopics.end()) {
            q.push_back(qNode(qN.level + 1, *it));
            it++;
         }
      }
      cout << endl;
   }

   void bfsInt(topics &tpStart, void (*cb)(topics &tp, void *cbArgs), void *cbArgs) {
      std::deque<topicID> q;
      q.push_back(tpStart.id);
      while (!q.empty()) {
         topicID id = q.front();
         topics &tp = getTopic(id);
         cb(tp, cbArgs);
         q.pop_front();
         std::vector<topicID>::iterator it = tp.subTopics.begin();
         while (it != tp.subTopics.end()) {
            q.push_back(*it);
            it++;
         }
      }
   }

   topics&
   lookupTopicByName(const std::string &topicName) {
      try {
         topicID tid;
         tid = m.at(topicName);
         return getTopic(tid);
      } catch (const std::out_of_range &e) {
         throw;
      }
   }

   void
   addTopicQuestion(const std::string &questionText) {
      stringstream ss;
      ss << questionText;
      string topic, question;
      ss >> topic;
      topic = topic.substr(0, topic.length() - 1);
      getline(ss, question);
      topics &tp = lookupTopicByName(topic);
      tp.addQuestion(question);
   }

   struct query {
      uint32_t numMatch;
      string   question;
   };

   static void countQueryMatch(topics &tp, void *cbArgs) {
      query *q = static_cast<query *>(cbArgs);
      if (tp.isQueryMatch(q->question)) {
         q->numMatch++;
      }
   }

   uint32_t
   countNumQueries(const std::string &queryText) {
      stringstream ss;
      ss << queryText;
      string topic;
      ss >> topic;
      struct query q;
      q.numMatch = 0;
      getline(ss, q.question);

      topics &tp = lookupTopicByName(topic);
      bfsInt(tp, countQueryMatch, static_cast<void *>(&q));
      return q.numMatch;
   }
};

static void
readInput(Topics &tp)
{
   std::stringstream ss;
   std::string line;
   if (getline(cin, line) == 0) {
      throw std::invalid_argument("Bad line");
   }
   if (getline(cin, line) == 0) {
      throw std::invalid_argument("Bad line");
   }
   tp.parseTopicInput(line);
   if (getline(cin, line) == 0) {
      throw std::invalid_argument("Bad line");
   }
   ss << line;
   int numQuestions;
   ss >> numQuestions;
   for (int i = 0; i < numQuestions; i++) {
      if (getline(cin, line) == 0) {
         throw std::invalid_argument("Bad line");
      }
      tp.addTopicQuestion(line);
   }
   ss.clear();
   ss.str("");
   if (getline(cin, line) == 0) {
      throw std::invalid_argument("Bad line");
   }
   ss << line;
   int numQueries;
   ss >> numQueries;
   for (int i = 0; i < numQueries; i++) {
      if (getline(cin, line) == 0) {
         throw std::invalid_argument("Bad line");
      }
      cout << tp.countNumQueries(line) << endl;
   }
}

int main()
{
   Topics tp;
   readInput(tp);
#if 0
   wordTrie wt;
   wt.addWordsInSentence("Why are many reptiles green?");
   wt.addWordsInSentence("How do birds fly?");
   wt.addWordsInSentence("How endangered are eagles?");
   wt.addWordsInSentence("Where in the world are pigeons most densely populated?");
   wt.addWordsInSentence("Where do most eagles live?");

   std::string st;
   st.assign("How en");
   cout << st << ":" << wt.areWordsPresentInSentence(st) << endl;
   st.assign("Where");
   cout << st << ":" << wt.areWordsPresentInSentence(st) << endl;
   st.assign("Ho");
   cout << st << ":" << wt.areWordsPresentInSentence(st) << endl;
   st.assign("How d");
   cout << st << ":" << wt.areWordsPresentInSentence(st) << endl;
#endif
   return 0;
}
