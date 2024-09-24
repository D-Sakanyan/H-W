#include "Sorting.h"
#include <algorithm>

void sortComplexNumbers(std::vector<ComplexNumber>& cnArray) {
    std::sort(cnArray.begin(), cnArray.end(), [](const ComplexNumber& a, const ComplexNumber& b) {
        return a.absolute() < b.absolute();
    });
}
