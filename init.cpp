#include "bank.hpp"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

extern void init_bank(Bank* bank);

int main() {
    int fd = shm_open("/bank_shm", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }

    size_t size = sizeof(Bank);
    if (ftruncate(fd, size) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    Bank* bank = static_cast<Bank*>(ptr);
    init_bank(bank);
    std::cout << "Банк инициализирован.\n";

    munmap(ptr, size);
    close(fd);
    return 0;
}
