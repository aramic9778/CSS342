#include "bank.h"
#include <fstream>
#include <queue>
using namespace std;

void Bank::processTransactionFile(const string &fileName) {
  ifstream inFile;
  queue<string> tran; // queue to store transactions
  string arg;
  string fname, lname;
  int fT = -1;
  inFile.open(fileName); // opening file
  if (!inFile) {
    cerr << "Unable to open file: " << fileName << endl;
    return;
  }
  while (!inFile.eof()) { // while not end of file add each transaction in queue
    getline(inFile, arg);
    tran.push(arg);
  }
  int uid, amount, tuid;
  while (
      !tran.empty()) { // while queue is not empty take by one each transaction
    stringstream ss(tran.front());
    tran.pop();
    ss >> arg;
    switch (arg[0]) {
    case 'O': // open account function
      ss >> fname >> lname >> uid;
      openAccount(fname += " " + lname, uid);
      break;
    case 'D':
      ss >> uid >> amount; // deposit function
      deposit(uid / 10, amount, uid % 10);
      break;
    case 'W': // withdraw function
      ss >> uid >> amount;
      withdraw(uid / 10, amount, uid % 10);
      break;
    case 'H': // history function
      ss >> uid;
      if (uid > 9999) {
        uid = uid / 10;
        fT = uid % 10;
      }
      history(uid, fT);
      fT = -1;
      break;
    case 'T': // transfer function
      ss >> uid >> amount >> tuid;
      transfer(uid / 10, tuid / 10, amount, uid % 10, tuid % 10);
      break;
    }
  }
  cout << endl;
  cout << "Processing Done. Final Balances." << endl;
  accounts.display(); // display information about all accounts at the end
}

bool Bank::openAccount(string name, int id) {
  if (id > 9999 || id < 1000) { // if id number not sufficient return a false
    cout << "Wrong ID pattern. Suppose to be 4 digit" << endl;
    return false;
  }
  Account *acc = new Account(id, move(name)); // create new account
  if (!accounts.insert(acc)) {
    cout << "ERROR: Account " << id << " is already open. Transaction refused."
         << endl; // if account exist print a error message
    delete acc;   // get rid of memory leak
    return false;
  }
  return true;
}

bool Bank::deposit(int id, int amount, int fundType) {
  Account *acc = nullptr;
  string h = "D " + to_string(id * 10 + fundType) + " " + to_string(amount);
  if (!accounts.retrieve(id, acc)) { // edge case if account not found
    cout << "Account " + to_string(id) + " not found!" << endl;
    return false;
  }
  acc->addFund(fundType, amount); // process a transaction
  acc->addHistory(h, fundType);   // add transaction to history
  return true;
}

// withdaw asset from a fund
bool Bank::withdraw(int id, int amount, int fundType) {
  Account *acc = nullptr;
  if (!accounts.retrieve(id, acc)) { // edge case if account not found
    cout << "Account " + to_string(id) + " not found!" << endl;
    return false;
  }
  string h = "W " + to_string(id * 10 + fundType) + " " +
             to_string(amount); // string pattern for history

  if (!acc->ifEnough(amount, fundType) && (fundType > 3)) {
    acc->addHistory(
        h + " (Failed)",
        fundType); // add (Failed) if fundtype from 4 to 9 and not enough money
    return false;
  }

  if (!acc->ifEnough(amount, fundType) &&
      (fundType == 1 || fundType == 0)) { // if not enough money and fundtype
                                          // money market or prime money market
    int cover = (fundType == 0) ? 1 : 0;  // variable for cover fundtype
    int remainder = amount - acc->getFund(fundType); // how much left to cover
    if (acc->ifEnough(remainder, cover)) {           // if Enough to cover
      int removed = acc->getFund(fundType);
      acc->addFund(fundType, -removed); // remove from main fundtype
      acc->addFund(cover, -remainder);  // remove from cover fundtype
      acc->addHistory("W " + to_string(id * 10 + fundType) + " " +
                          to_string(amount) + " Covered",
                      fundType);
      acc->addHistory("D " + to_string(id * 10 + fundType) + " " +
                          to_string(remainder) + " Cover",
                      fundType);
      acc->addHistory(
          "T " + to_string(id * 10 + cover) + " " + to_string(remainder) + " " +
              to_string(id * 10 + fundType), // transfer hisotry from cover
          cover);
      return true;
    }
    acc->addHistory(h + " (Failed)",
                    fundType); // if not Enough even in cover fundtype
    return false;
  }
  if (!acc->ifEnough(amount, fundType) &&
      (fundType == 2 || fundType == 3)) { // the same case for Bonds
    int cover = (fundType == 2) ? 3 : 2;
    int remainder = amount - acc->getFund(fundType);
    if (acc->ifEnough(remainder, cover)) {
      int removed = acc->getFund(fundType);
      acc->addFund(fundType, -removed);
      acc->addFund(cover, -remainder);
      acc->addHistory("W " + to_string(id * 10 + fundType) + " " +
                          to_string(amount) + " Covered",
                      fundType);
      acc->addHistory("D " + to_string(id * 10 + fundType) + " " +
                          to_string(remainder) + " Cover",
                      fundType);
      acc->addHistory("T " + to_string(id * 10 + cover) + " " +
                          to_string(remainder) + " " +
                          to_string(id * 10 + fundType),
                      cover);
      return true;
    }
    acc->addHistory(h + " (Failed)", fundType);
    return false;
  }
  acc->addFund(fundType, -amount);
  acc->addHistory(h, fundType);
  return true;
}

// transfer assets between fund (can be funds owned by a single client or
// transfers between clients)
bool Bank::transfer(int sourceID, int targetID, int amount, int fundType,
                    int fundType2) {
  Account *acc = nullptr;  // source account
  Account *acc2 = nullptr; // target account
  if (!accounts.retrieve(sourceID,
                         acc)) { // edge case if source account not found
    cout << "ERROR: Could not find Account " + to_string(sourceID) +
                " Transfer cancelled."
         << endl;
    return false;
  }
  if (!accounts.retrieve(targetID,
                         acc2)) { // edge case if target account not found
    cout << "ERROR: Could not find Account " + to_string(targetID) +
                " Transfer cancelled."
         << endl;
    return false;
  }
  if (!acc->ifEnough(amount, fundType)) { // case if not enough money
    string h = "T " + to_string(sourceID * 10 + fundType) + " " +
               to_string(amount) + " " + to_string(targetID * 10 + fundType2) +
               " (Failed)";
    acc->addHistory(h, fundType); // add history
    return false;
  }
  string h = "T " + to_string(sourceID * 10 + fundType) + " " +
             to_string(amount) + " " + to_string(targetID * 10 + fundType2); //
  acc->addFund(fundType, -amount);  // remove fund
  acc2->addFund(fundType2, amount); // add fund
  acc->addHistory(h, fundType);     // add transfer history
  h = "D " + to_string(targetID * 10 + fundType2) + " " + to_string(amount);
  acc->addHistory(h, fundType2); // add deposit history for the target

  return true;
}

// diplay a single fund history or all types of funds' transiation histories.
bool Bank::history(int id, int fundType) {
  Account *acc = nullptr;
  if (!accounts.retrieve(id, acc)) { // edge case if account not found
    cout << "Account " + to_string(id) + " not found!" << endl;
    return false;
  }

  acc->getHistory(fundType); // get history either for particular fund or for
                             // the whole account
  return true;
}
