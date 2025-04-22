#include "bank.hpp"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <climits>

extern void init_bank(Bank* bank);

int main() {
    int fd = shm_open("/bank_shm", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }

    size_t size = sizeof(Bank) + 2 * N * sizeof(Account);
    if (ftruncate(fd, size) == -1) {
        perror("ftruncate");
        return 1;
    }

    void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    Bank* bank = static_cast<Bank*>(ptr);
    bank->accounts = reinterpret_cast<Account*>(reinterpret_cast<char*>(ptr) + sizeof(Bank));

    init_bank(bank);

    std::cout << "Bank initialized with 2*N accounts.\n";

    munmap(ptr, size);
    close(fd);
    return 0;
}