#ifndef BANK_HPP
#define BANK_HPP

#include <climits>

#define N 100

struct Account {
    int cur_balance;
    int max;
    int min;
    int frozen;
};

struct Bank {
     Account accounts[2 * N];
};

#endif 
