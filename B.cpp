#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>


struct Player {
    int64_t efficiency = 0;
    int index = 0;

    Player(int64_t efficiency, int index) : efficiency(efficiency), index(index) {};
};

struct Team {
    std::vector<Player>::const_iterator start;
    std::vector<Player>::const_iterator end;
    int64_t efficiency = 0;
};


bool EfficiencyComparator(const Player &first, const Player &second) {
    return first.efficiency < second.efficiency;
}

bool IndexComparator(const Player &first, const Player &second) {
    return first.index < second.index;
}

template<typename ForwardIterator, typename Comparator>
ForwardIterator Merge(ForwardIterator first_begin, ForwardIterator first_end,
                      ForwardIterator second_begin, ForwardIterator second_end,
                      ForwardIterator out, Comparator comparison) {
    for (; first_begin != first_end; ++out) {
        if (second_begin == second_end) {
            return std::copy(first_begin, first_end, out);
        }

        if (comparison(*second_begin, *first_begin)) {
            *out = *second_begin;
            ++second_begin;
        } else {
            *out = *first_begin;
            ++first_begin;
        }
    }
    return std::copy(second_begin, second_end, out);
}

template<typename ForwardIterator, typename Comparator>
void MergeSort(ForwardIterator buffer_state, ForwardIterator begin, ForwardIterator end,
               Comparator comparator) {
    auto difference = std::distance(begin, end);
    auto mid = difference / 2;

    if (mid == 0) {
        return;
    }

    auto mid_iterator = std::next(begin, mid);
    MergeSort(buffer_state, begin, mid_iterator, comparator);
    MergeSort(buffer_state, mid_iterator, end, comparator);
    Merge(begin, mid_iterator, mid_iterator, end, buffer_state, comparator);

    std::copy(buffer_state, buffer_state + difference, begin);
}

template<typename ForwardIterator, typename Comparator>
void Sort(ForwardIterator begin, ForwardIterator end, Comparator comparator) {
    typedef typename std::iterator_traits<ForwardIterator>::value_type IterTrait;
    std::vector<IterTrait> buffer(begin, end);
    MergeSort(buffer.begin(), begin, end, comparator);
}

bool IsTeamUnited(const Team &current_team) {
    return current_team.end->efficiency >
            (current_team.start->efficiency + std::next(current_team.start)->efficiency);
}

std::vector<Player> FindBestTeam(std::vector<Player> players) {
    if (players.size() < 3) {
        return players;
    }

    Sort(players.begin(), players.end(), EfficiencyComparator);

    Team best_team = {players.begin(), players.begin() + 2,
                      players[0].efficiency + players[1].efficiency};
    auto current_team = best_team;

    while (current_team.end < players.end()) {
        while (IsTeamUnited(current_team)) {
            current_team.start++;
            current_team.efficiency -= current_team.start->efficiency;
        }

        current_team.efficiency += current_team.end->efficiency;
        current_team.end++;

        if (current_team.efficiency > best_team.efficiency) {
            best_team = current_team;
        }
    }
    return {best_team.start, best_team.end};
}

int64_t SumEfficiency(const std::vector<Player> &team) {
    int64_t full_efficiency = 0;
    for (const auto &player : team) {
        full_efficiency += player.efficiency;
    }
    return full_efficiency;
}

std::vector<Player> ReadTeam(std::istream &in = std::cin) {
    std::vector<Player> players;
    int team_size;
    in >> team_size;
    players.reserve(team_size);
    
    for (int index = 0; index < team_size; ++index) {
        int64_t efficiency;
        in >> efficiency;
        players.emplace_back(efficiency, index);
    }
    
    return players;
}

void PrintBestTeam(std::vector<Player> result_team, std::ostream &out = std::cout) {
    auto max_sum = SumEfficiency(result_team);
    out << max_sum << "\n";

    Sort(result_team.begin(), result_team.end(), IndexComparator);
    for (const auto &player : result_team) {
        out << player.index + 1 << " ";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto players = ReadTeam();
    auto best_team = FindBestTeam(players);
    PrintBestTeam(best_team);

    return 0;
}
