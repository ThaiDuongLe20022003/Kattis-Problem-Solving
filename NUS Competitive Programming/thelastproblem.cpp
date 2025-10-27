#include <iostream>
#include <string>

int main() {
    // We don't need fast I/O for such a small input,
    // but it's good practice.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string S;
    
    // Read the entire line of input,
    // in case the name S contains spaces.
    std::getline(std::cin, S);

    // Print the formatted output string
    std::cout << "Thank you, " << S << ", and farewell!" << std::endl;

    return 0;
}
