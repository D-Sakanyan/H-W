#include <iostream>
#include <vector>
#include "Complex.h"
#include "Sorting.h"

int main() {
    std::vector<ComplexNumber> numbers = {
        ComplexNumber(3, 4),
        ComplexNumber(1, 2),
        ComplexNumber(5, -5),
        ComplexNumber(0, 1)
    };

    std::cout << "Complex numbers:\n";
    for (const auto& num : numbers) {
        std::cout << num << "\n";
    }

    sortComplexNumbers(numbers);

    std::cout << "\nSorting numbers:\n";
    for (const auto& num : numbers) {
        std::cout << num << "\n";
    }

    return 0;
}
