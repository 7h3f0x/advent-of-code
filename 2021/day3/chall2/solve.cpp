#include <fstream>
#include <iostream>
#include <vector>

template <char c1, char c2> int get_rating(std::vector<std::string> numbers) {
    int idx = 0;
    while (numbers.size() > 1) {
        size_t N = numbers.size();
        size_t count = 0;
        for (auto line : numbers) {
            count += (line[idx] == '1');
        }

        char ch;
        if ((N & 1) != 0) {
            if (count > N / 2)
                ch = c1;
            else
                ch = c2;
        } else {
            if (count < N / 2)
                ch = c2;
            else
                ch = c1;
        }

        std::vector<std::string> new_nums;
        for (auto line : numbers) {
            if (line[idx] == ch) {
                new_nums.push_back(line);
            }
        }
        numbers = new_nums;
        idx += 1;
    }
    return std::stoi(numbers[0], 0, 2);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << (argc < 1 ? "./solve" : argv[0])
                  << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream inp;
    inp.open(argv[1]);
    if (!inp.is_open()) {
        std::cerr << "Unable to open file: " << argv[1] << std::endl;
        return 2;
    }

    std::string line;
    std::vector<std::string> numbers;
    while (getline(inp, line)) {
        numbers.push_back(line);
    }

    // use some template metaprogramming as only the char to be used for
    // comparison needs to be swapped in the two cases
    size_t oxygen = get_rating<'1', '0'>(numbers);
    size_t co2 = get_rating<'0', '1'>(numbers);

    std::cout << oxygen * co2 << std::endl;

    inp.close();
    return 0;
}
