#include <iostream>
#include <vector>
#include "complex.h"
#include "sorter.h"

int main() {
    std::vector<Complex> numbers = {
        Complex(6, 3),   
        Complex(3, -2),  
        Complex(0, 2),   
        Complex(-4, -7), 
        Complex(5, -8)    
    };

    std::cout << "Not sorted:\n";
    for (const auto& num : numbers) {
        std::cout << num << "\n";
    }

    sortComplexNumbers(numbers);

    std::cout << "\nSorted:\n";
    for (const auto& num : numbers) {
        std::cout << num << "\n";
    }

    return 0;
}

