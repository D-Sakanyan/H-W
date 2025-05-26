#include "bank.h"
#include <iostream>

int get_balance_curr(TBank* bank, int acc_num){
	if(acc_num < 0 || acc_num >= static_cast<int>(bank->size))
		return -1;
	return bank->cells[acc_num].cur_b;
}

int get_balance_min(TBank* bank, int acc_num){
	if(acc_num < 0 || acc_num >= static_cast<int>(bank->size))
		return -1;
	return bank->cells[acc_num].min;
}

int get_balance_max(TBank* bank, int acc_num){
	if(acc_num < 0 || acc_num >= static_cast<int>(bank->size))
		return -1;
	return bank->cells[acc_num].max;
}

int froze(TBank* bank, int acc_num){
	if(acc_num < 0 || acc_num >= static_cast<int>(bank->size))
		return -1;
	return bank->cells[acc_num].is_frozen;
}

int unfroze(TBank* bank, int acc_num){
	if(acc_num < 0 || acc_num >= static_cast<int>(bank->size))
		return -1;
	return bank->cells[acc_num].is_frozen;
}

int transfer(TBank* bank, int from_acc, int to_acc, int amount){
	if(from_acc < 0 || from_acc >= static_cast<int>(bank->size) || to_acc < 0 || to_acc >= static_cast<int>(bank->size))
		return -1;
	if(from_acc == to_acc)
		return -2;
	
	Cell* from = &bank->cells[from_acc];
	Cell* to = &bank->cells[to_acc];
	
	if(from->is_frozen == 1)
		return -3;

	if(to->is_frozen == 1)
                return -4;

	if(from->cur_b < amount)		
		return -5;

	from->cur_b -= amount;
	to->cur_b += amount;

	return 0;
}

int add(TBank* bank, int amount){
	if(amount > 20000)
		return -1;
	else if(amount <= 0)
		return -2;
	return 0;
}

int withdraw(TBank* bank, int amount){
	if(amount > 20000)
		return -1;
	else if(amount <= 0)
		return -2;
	return 0;
}
