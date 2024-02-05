#include <string>
#include <vector>
#include <iostream>


int main() {
    std::string bracket_line;
    std::cin >> bracket_line;

    std::vector<char> closing_sign;

    int round_index = 0;
    int square_index = 0;
    int figure_index = 0;
    int max_prefics = 0;


    for (auto bracket : bracket_line) {
        if (bracket == '(') {
            closing_sign.push_back(')');
            ++round_index;
            ++max_prefics;
        } else if (bracket == '[') {
            closing_sign.push_back(']');
            ++square_index;
            ++max_prefics;
        } else if (bracket == '{') {
            closing_sign.push_back('}');
            ++figure_index;
            ++max_prefics;
        } else if (closing_sign.size() == 0) {
            if ((bracket == ')') || (bracket == ']') || (bracket == '}')) {
                std::cout << max_prefics;
                max_prefics = -1;
                break;
            }
        } else if (bracket == closing_sign.back() && bracket == ')') {
            closing_sign.pop_back();
            --round_index;
            ++max_prefics;
        } else if (bracket == closing_sign.back() && bracket == ']') {
            closing_sign.pop_back();
            --square_index;
            ++max_prefics;
        } else if (bracket == closing_sign.back() && bracket == '}') {
            closing_sign.pop_back();
            --figure_index;
            ++max_prefics;
        } else {
            std::cout << max_prefics;
            max_prefics = -1;
            break;
        }
    }

    if (max_prefics != -1) {
        if (round_index == 0 && square_index == 0 && figure_index == 0) {
            std::cout << "CORRECT";
        } else {
            std::cout << bracket_line.size();
        }
    }

    return 0;
}
