#include <iostream>
#include <vector>
#include "complex.h"
#include "sorter.h"

int main() {
    std::vector<Complex> numbers = {
        Complex(5, 7),
        Complex(-3, 1),
        Complex(0, -3),
        Complex(1, 2)
    };

    std::cout << "Not sorted:\n";
    for (const auto& num : numbers) {
        std::cout << num << std::endl;
    }

    sortComplexNumbers(numbers);

    std::cout << "\nSorted:\n";
    for (const auto& num : numbers) {
        std::cout << num << std::endl;
    }

    return 0;
}

