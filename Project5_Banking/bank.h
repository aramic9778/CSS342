#ifndef BANK_H
#define BANK_H
#include "bstree.h"

using namespace std;
// print all the fund
// friend ostream &operator<<(ostream&out, const Account& target);
class Bank {

public:
  // decode the text to chose the function
  void processTransactionFile(const string &fileName);

  // open a client account with the appropriate funds
  bool openAccount(string name, int id);

  // Deposit asset into a fund
  bool deposit(int id, int amount, int fundType);

  // withdraw asset from a fund
  bool withdraw(int id, int amount, int fundType);

  // transfer assets between fund (can be funds owned by a single client or
  // transfers between clients)
  bool transfer(int sourceID, int targetID, int amount, int fundType,
                int fundType2);

  // display a single fund history or all types of funds' transaction histories.
  bool history(int id, int fundType);

private:
  // the Binary Tree will store all the account.
  BSTree accounts;
};
#endif