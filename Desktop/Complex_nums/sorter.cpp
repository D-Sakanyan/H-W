#include "sorter.h"
#include <algorithm>

void sortComplexNumbers(std::vector<Complex>& numbers) {
    std::sort(numbers.begin(), numbers.end(), [](const Complex& a, const Complex& b) {
        return a.absolute() < b.absolute();
    });
}

