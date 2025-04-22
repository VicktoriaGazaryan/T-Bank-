#include "bank.hpp"
#include <iostream>

void init_bank(Bank* bank) {
    for (int i = 0; i < 2 * N; ++i) {
        bank->accounts[i].cur_balance = 0;
        bank->accounts[i].max = INT_MAX;
        bank->accounts[i].min = INT_MIN;
        bank->accounts[i].frozen = 0;
    }
}

void print_bank(Bank* bank) {
    for (int i = 0; i < 2 * N; ++i) {
        std::cout << "Account[" << i << "]: balance = "
                  << bank->accounts[i].cur_balance << ", max = "
                  << bank->accounts[i].max << ", min = "
                  << bank->accounts[i].min << ", frozen = "
                  << bank->accounts[i].frozen << "\n";
    }
}