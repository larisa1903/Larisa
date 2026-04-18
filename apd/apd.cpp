#include <algorithm>
#include <chrono>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using WordFrequency = std::unordered_map<std::string, std::size_t>;

std::string normalize_word(const std::string& token)
{
    std::string word;
    word.reserve(token.size());

    for (unsigned char ch : token) {
        if (std::isalnum(ch)) {
            word.push_back(static_cast<char>(std::tolower(ch)));
        }
    }

    return word;
}

WordFrequency count_words_sequential(const std::string& input_path)
{
    std::ifstream input(input_path);
    if (!input.is_open()) {
        throw std::runtime_error("Nu s-a putut deschide fisierul de intrare: " + input_path);
    }

    WordFrequency frequencies;
    std::string token;

    while (input >> token) {
        const std::string word = normalize_word(token);
        if (!word.empty()) {
            ++frequencies[word];
        }
    }

    return frequencies;
}

std::vector<std::pair<std::string, std::size_t>> sort_frequencies(const WordFrequency& frequencies)
{
    std::vector<std::pair<std::string, std::size_t>> sorted(frequencies.begin(), frequencies.end());

    std::sort(sorted.begin(), sorted.end(), [](const auto& left, const auto& right) {
        if (left.second != right.second) {
            return left.second > right.second;
        }
        return left.first < right.first;
    });

    return sorted;
}

void write_results(const std::vector<std::pair<std::string, std::size_t>>& frequencies,
    const std::string& output_path)
{
    std::ofstream output(output_path);
    if (!output.is_open()) {
        throw std::runtime_error("Nu s-a putut deschide fisierul de iesire: " + output_path);
    }

    output << "cuvant,frecventa\n";
    for (const auto& [word, count] : frequencies) {
        output << word << ',' << count << '\n';
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3) {
        std::cerr << "Utilizare: apd.exe <fisier_intrare> [fisier_iesire.csv]\n";
        return 1;
    }

    const std::string input_path = argv[1];
    const std::string output_path = argc == 3 ? argv[2] : "word_frequencies.csv";

    try {
        const auto start = std::chrono::high_resolution_clock::now();

        const WordFrequency frequencies = count_words_sequential(input_path);
        const auto sorted = sort_frequencies(frequencies);
        write_results(sorted, output_path);

        const auto stop = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = stop - start;

        std::cout << "Fisier intrare: " << input_path << '\n';
        std::cout << "Fisier iesire: " << output_path << '\n';
        std::cout << "Cuvinte distincte: " << frequencies.size() << '\n';
        std::cout << "Timp executie secventiala: " << std::fixed << std::setprecision(3)
                  << elapsed.count() << " ms\n";

        const std::size_t preview_count = std::min<std::size_t>(10, sorted.size());
        std::cout << "Top " << preview_count << " cuvinte:\n";
        for (std::size_t i = 0; i < preview_count; ++i) {
            std::cout << std::setw(2) << i + 1 << ". " << sorted[i].first << " -> "
                      << sorted[i].second << '\n';
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Eroare: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
