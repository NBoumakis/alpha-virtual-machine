#include "loader/loader.hpp"
#include <algorithm>
#include <cassert>
#include <unordered_map>

bool is_number(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

static bool magicnumber(std::ifstream &in_file) {
    unsigned number;

    if (in_file >> number) {
        return number == 340200501;
    }

    return false;
}

static std::string string(std::ifstream &in_file) {
    std::string token;

    in_file >> token;

    if (!is_number(token)) {
        throw std::out_of_range("Invalid size, not an integer");
    }

    unsigned long total = std::stoul(token);

    return in_file.read(token, total);
}

static bool strings(std::ifstream &in_file, std::unordered_map<unsigned long, std::string> &buf) {
    unsigned long total;

    if (!(in_file >> total)) {
        return false;
    }

    for (unsigned long i = total; i; --i) {
        buf.insert({total - i, string(in_file)});
    }
}

static bool arrays(std::ifstream &in_file) {
    return strings(in_file, ) && numbers() && userFunctions() && libfunctions();
}

static bool code(std::ifstream &in_file) {
}

bool load_text(std::ifstream &in_file) {
    assert(in_file.is_open());

    return magicnumber(in_file) && arrays(in_file) && code(in_file);
}