#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    std::vector<int> a {1, 2, 3, 4, 5};
    std::reverse(a.begin(), a.end());
    for (auto x: a) {
        std::cout << x << std::endl;
    }
    
    return 0;
}