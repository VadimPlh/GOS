#pragma once

#include <unordered_map>
#include <string>
#include <vector>

class playing_field {
public:
    playing_field() = default;

    void fill_field(const std::string &answer_) {
        answer = std::string(answer_.length(), '*');
        for (int i = 0; i < answer_.size(); ++i) {
            char_position[answer_[i]].emplace_back(i);
        }
    }

    void open_char(char char_for_open) {
        auto char_it = char_position.find(char_for_open);
        if (char_it != char_position.end()) {
            for (const auto &position : char_it->second) {
                answer[position] = char_it->first;
            }
        }
    }

    std::string get_ans() const {
        return answer;
    }

private:
    std::string answer;
    std::unordered_map<char, std::vector<size_t>> char_position;
};

playing_field world;
