
// TODO(student)

Design group name: p5-design2

Implementation group name: p5-implementation1

Design programmers: Aram Antonyan, Qingran Shao, Eric Dang, Hao Duc Duong

Implementation programmers: Aram Antonyan

# Contribution by each person
Designing: 
Aram Antonyan - designing account.h
Qingran Shao - designing bank.h
Eric Dang - designing bank.h 
Hao Duc Duong - designing a BStree.h (adding new and helper functions)

Implementation:
The entire implementation part and textfile.txt was done by Aram Antonyan.

# Data structures used
Queue, BSTree, FundType structure.

On stage of designing we decided to use FundType structure which consist of three variables: name(Name of fundType),
amount(how much money particular fundtype has) and stringstream history(consist the history for each fundtype).

For storing all account we got BSTree.h by default to sort all accounts by ID number to retrieve, insert and display them faster.

In ProcessTransactionFile function I used queue to store all transaction in line and the process them by one. 
