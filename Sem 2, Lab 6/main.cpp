// any_of
// is_sorted
// is_palindrome

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include "functions.hpp"

int main() {
    std::vector<int> vector = {0, 1, 2, 3, 4};
    std::vector<int> vector1 = {1, 2, 3, 4, 5, 6, -1};
    std::vector<int> palindrome = {0, 1, 2, 3, 2, 1, 0};
    std::vector<int> palindrome1 = {0, 1, 2, 2, 1, 0};
    std::string stringPalindrome= "qwertyytrewq";
    
    // any_of
    std::cout << std::boolalpha << func::any_of(vector.begin(), vector.end(), [](int i) { return i < 0; }) << std::endl;
    std::cout << std::boolalpha << func::any_of(vector1.begin(), vector1.end(), [](int i) { return i < 0; }) << std::endl;
    std::cout << std::endl;
    
    // is_sorted
    std::cout << std::boolalpha << func::is_sorted(vector.begin(), vector.end(), [](int i, int j) { return i > j; }) << std::endl;
    
    std::sort(vector.begin(), vector.end(), [](int i, int j) { return i > j; });
    
    std::cout << std::boolalpha << func::is_sorted(vector.begin(), vector.end(), [](int i, int j) { return i > j; }) << std::endl;
    std::cout << std::endl;
    
    // is_palindrome
    std::cout << std::boolalpha << func::is_palindrome(palindrome.begin(), palindrome.end()) << std::endl;
    std::cout << std::boolalpha << func::is_palindrome(palindrome1.begin(), palindrome1.end()) << std::endl;
    std::cout << std::boolalpha << func::is_palindrome(stringPalindrome.begin(), stringPalindrome.end()) << std::endl;
}
