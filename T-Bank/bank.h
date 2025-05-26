#ifndef BANK_H
#define BANK_H

#include <cstddef>
class Cell {
public:
    int cur_b;
    int min;
    int max;
    int is_frozen;
};

class TBank {
public:
    size_t size;
    Cell cells[];
};

int get_balance_curr(TBank* bank, int acc_num);
int get_balance_min(TBank* bank, int acc_num);
int get_balance_max(TBank* bank, int acc_num);
int froze(TBank* bank, int acc_num);
int unfroze(TBank* bank, int acc_num);
int transfer(TBank* bank, int from_acc, int to_acc, int amount);
int add(TBank* bank, int amount);
int withdraw(TBank* bank, int amount);
#endif
