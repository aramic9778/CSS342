#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <sstream>
#include <string>
using namespace std;
class Account {
  friend class BSTree;

public:
  Account(int id, string name);         // constructor for creating an account
  int getID();                          // get Account ID
  string getName();                     // get Account name
  int getFund(int fundID);              // get a amount from a fund
  bool addFund(int fundID, int amount); // add a fund for a fundtype
  string getFundName(int fundID);       // get fund name
  void addHistory(const string &his,
                  int fundID); // This function should append new history log
                               // in to the fundType.history
  bool ifEnough(int money, int fT);
  void getHistory(int fundID);

  // method to handle an exception

private:
  struct FundType {
    string name = "";
    int amount = 0;
    stringstream history; // variable to store history
  };

  int ID;      // int variable for ID
  string name; // string variable for name
  FundType fundtype[10];
};

#endif // ACCOUNT_H
