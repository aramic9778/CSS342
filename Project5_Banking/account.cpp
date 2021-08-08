#include "account.h"
#include <iostream>
#include <string>
Account::Account(int id, string name) { // account construcitr
  this->ID = id;
  this->name = std::move(name);
  for (int i = 0; i < 10; i++) {
    fundtype->amount = 0; // set amount to 0 for all funds
  }
  fundtype[0].name = "Money Market";
  fundtype[1].name = "Prime Money Market";
  fundtype[2].name = "Long-Term Bond";
  fundtype[3].name = "Short-Term Bond";
  fundtype[4].name = "500 Index Fund";
  fundtype[5].name = "Capital Value Fund";
  fundtype[6].name = "Growth Equlty Fund";
  fundtype[7].name = "Growth Index Fund";
  fundtype[8].name = "Value Fund";
  fundtype[9].name = "Value Stock Index"; // all fund names
}
int Account::getID() { return ID; }        // get account ID
string Account::getName() { return name; } // get Name
int Account::getFund(int fundID) {
  return fundtype[fundID].amount;
} // get Fund amount
string Account::getFundName(int fundID) {
  return fundtype[fundID].name;
} // get fund name
bool Account::addFund(int fundID, int amount) { // add fund
  fundtype[fundID].amount += amount;
  return true;
}
void Account::addHistory(const string &his, int fundID) { // add history to fund
  fundtype[fundID].history << "       " << his << endl;
}
bool Account::ifEnough(int money, int fT) { // check if Enough money
  return fundtype[fT].amount >= money;
}
void Account::getHistory(int fundID) { // get history
  if (fundID == -1) {                  // for all funds
    cout << "Displaying Transaction History for " << getName() << " by fund."
         << endl;
    for (int i = 0; i < 10; i++) {
      cout << " " << getFundName(i) << ": $" << getFund(i) << endl;
      cout << fundtype[i].history.str();
    }
  } else { // for one particular fund
    cout << "Displaying Transaction History for " << getName() << "'s "
         << getFundName(fundID) << ": $" << getFund(fundID) << endl;
    cout << fundtype[fundID].history.str();
  }
}
