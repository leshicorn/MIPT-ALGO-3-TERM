#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>

const ssize_t RIGHT = 0;
const ssize_t LEFT = 1;
const ssize_t DOWN = 2;
const ssize_t UP = 3;

ssize_t x_shifts[4] = {0, 0, 1, -1};
ssize_t y_shifts[4] = {1, -1, 0, 0};

template <size_t rows>
class PuzzleState {
   public:
    std::vector<ssize_t> state;
    bool is_empty = true;

    PuzzleState() {
        is_empty = true;
        state = std::vector<ssize_t>(rows * rows);
    }

    ~PuzzleState() = default;

    PuzzleState(const PuzzleState<rows>& other) {
        this->is_empty = other.is_empty;

        if (state.size() != rows * rows) {
            state = std::vector<ssize_t>(rows * rows);
        }
        for (size_t idx = 0; idx < rows * rows; ++idx) {
            state[idx] = other.state[idx];
        }
    }

    PuzzleState& operator=(const PuzzleState<rows>& other) {
        this->is_empty = other.is_empty;

        for (size_t idx = 0; idx < rows * rows; ++idx) {
            state[idx] = other.state[idx];
        }

        return *this;
    }

    bool operator==(const PuzzleState<rows>& other) const {
        for (size_t idx = 0; idx < rows * rows; ++idx) {
            if (state[idx] != other.state[idx]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const PuzzleState<rows>& other) const {
        return (*this == other) == false;
    }

    bool operator<(const PuzzleState<rows>& other) const {
        for (size_t idx = 0; idx < rows * rows; ++idx) {
            if (state[idx] < other.state[idx]) {
                return true;
            } else if (state[idx] > other.state[idx]) {
                return false;
            } else {
                continue;
            }
        }

        return false;
    }

    friend std::ostream& operator<<(std::ostream& stream,
                                    const PuzzleState<rows>& current_state) {
        if (current_state.state.empty() == true) {
            return stream;
        }

        for (size_t row = 0; row < rows; ++row) {
            for (size_t column = 0; column < rows; ++column) {
                if (current_state.state[rows * row + column]) {
                    stream << std::setw(3)
                           << static_cast<ssize_t>(
                                  current_state.state[rows * row + column])
                           << " ";
                } else {
                    stream << std::setw(3) << "  "
                           << " ";
                }
            }
            stream << std::endl;
        }

        return stream;
    }

    bool is_solveable() {
        ssize_t default_row = -1;

        std::vector<ssize_t> sol_state;
        for (size_t idx = 0; idx < rows * rows; ++idx) {
            if (state[idx] != 0) {
                sol_state.push_back(state[idx]);
            } else {
                default_row = idx / rows;
            }
        }

        size_t inversions = get_inversions_count(sol_state);
        bool is_odd_board_size = static_cast<bool>(rows & 1);

        if (is_odd_board_size && !(inversions & 1)) {
            return true;
        } else if (is_odd_board_size == 0 && ((default_row + inversions) & 1)) {
            return true;
        }

        return false;
    }

    static size_t get_inversions_count(const std::vector<ssize_t>& cur_state) {
        size_t inv_count = 0;
        for (size_t first = 0; first < cur_state.size() - 1; ++first)
            for (size_t second = first + 1; second < cur_state.size(); ++second)
                if (cur_state[first] > cur_state[second]) {
                    ++inv_count;
                }

        return inv_count;
    }

    PuzzleState get_state(ssize_t direction,
                          ssize_t x_pos = -1,
                          ssize_t y_pos = -1) {
        if (state.empty() || direction > 3) {
            return *this;
        }

        if (x_pos == -1 || y_pos == -1) {
            if (get_zero_position(*this, x_pos, y_pos) == false) {
                return PuzzleState<rows>();
            }
        }

        ssize_t new_x_pos = x_pos + x_shifts[direction];
        ssize_t new_y_pos = y_pos + y_shifts[direction];

        if (new_x_pos < 0 || new_y_pos < 0 || new_x_pos >= rows ||
            new_y_pos >= rows)
            return PuzzleState<rows>();

        PuzzleState<rows> v = *this;

        std::swap(v.state[rows * x_pos + y_pos],
                  v.state[rows * new_x_pos + new_y_pos]);
        return v;
    }

    static bool get_zero_position(const PuzzleState<rows>& node,
                                  ssize_t& x_pos,
                                  ssize_t& y_pos) {
        x_pos = y_pos = -1;

        for (size_t row = 0; row < rows; ++row) {
            for (size_t column = 0; column < rows; ++column) {
                if (node.state[rows * row + column] == false) {
                    x_pos = row;
                    y_pos = column;
                    return true;
                }
            }
        }

        return false;
    }

    static ssize_t get_opposite(ssize_t direction) {
        switch (direction) {
            case LEFT: {
                return RIGHT;
            }

            case RIGHT: {
                return LEFT;
            }

            case UP: {
                return DOWN;
            }

            case DOWN: {
                return UP;
            }

            default: {
                return EOF;
            }
        }
    }

    bool isEmpty() const { return is_empty; }
};

struct StateContent {
    bool is_closed;
    ssize_t cost;
    ssize_t parent;

    bool operator==(const StateContent& rhs) const {
        return parent == rhs.parent && cost == rhs.cost;
    }

    bool operator!=(const StateContent& rhs) const {
        return (rhs == *this) == false;
    }
};

template <size_t rows>
class A_star {
   public:
    std::map<PuzzleState<rows>, StateContent> passed;

    bool is_valid(ssize_t x, ssize_t y) {
        return x >= 0 && y >= 0 && x < rows && y < rows;
    }

    static double HammingDistance(const PuzzleState<rows>& first,
                                  const PuzzleState<rows>& second) {
        int conflicts = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < rows; j++)
                if (first.state[4 * i + j] &&
                    first.state[4 * i + j] != second.state[4 * i + j])
                    conflicts++;
        return conflicts;
    }

    static ssize_t ManHattan(const PuzzleState<rows>& first,
                             const PuzzleState<rows>& second) {
        ssize_t total = 0;

        ssize_t pR[rows * rows + 1];
        ssize_t pC[rows * rows + 1];

        for (size_t row = 0; row < rows; ++row) {
            for (size_t column = 0; column < rows; ++column) {
                pR[first.state[rows * row + column]] = row;
                pC[first.state[rows * row + column]] = column;
            }
        }

        for (size_t row = 0; row < rows; ++row)
            for (size_t column = 0; column < rows; ++column)
                if (second.state[rows * row + column] != false) {
                    total +=
                        abs(pR[second.state[rows * row + column]] - row) +
                        abs(pC[second.state[rows * row + column]] - column);
                }

        return total;
    }

    static double nLinearConflicts(const PuzzleState<rows>& first,
                                   const PuzzleState<rows>& second) {
        size_t conflicts = 0;
        int8_t pR[(rows * rows) + 1];
        int8_t pC[(rows * rows) + 1];
        for (size_t row = 0; row < rows; ++row) {
            for (int column = 0; column < rows; ++column) {
                pR[first.state[4 * row + column]] = static_cast<int8_t>(row);
                pC[first.state[4 * row + column]] = static_cast<int8_t>(column);
            }
        }

        for (size_t row = 0; row < rows; ++row) {
            for (size_t column = 0; column < rows; ++column) {
                for (size_t col_r = column + 1; col_r < rows; ++col_r) {
                    if (second.state[4 * row + column] &&
                        second.state[4 * row + col_r] &&
                        row == pR[second.state[4 * row + column]] &&
                        pR[second.state[4 * row + column]] ==
                            pR[second.state[4 * row + col_r]] &&
                        pC[second.state[4 * row + column]] >
                            pC[second.state[4 * row + col_r]]) {
                        ++conflicts;
                    }
                }
            }
        }

        for (int column = 0; column < rows; column++) {
            for (int rU = 0; rU < rows; rU++) {
                for (int rD = rU + 1; rD < rows; rD++) {
                    if (second.state[4 * rU + column] &&
                        second.state[4 * rD + column] &&
                        column == pC[second.state[4 * rU + column]] &&
                        pC[second.state[4 * rU + column]] ==
                            pC[second.state[4 * rD + column]] &&
                        pR[second.state[4 * rU + column]] >
                            pR[second.state[4 * rD + column]]) {
                        ++conflicts;
                    }
                }
            }
        }

        return conflicts;
    }

    ssize_t Heuristic(const PuzzleState<rows>& first,
                      const PuzzleState<rows>& second) {
        return 3.7f *
               (ManHattan(first, second) + HammingDistance(first, second) +
                nLinearConflicts(first, second));
    }

    void search(const PuzzleState<rows>& beg_state,
                const PuzzleState<rows>& wanted_state) {
        std::priority_queue<std::pair<double, PuzzleState<rows>>> path;
        path.push({0, beg_state});

        passed[beg_state] = {false, 0, EOF};

        while (path.empty() == false) {
            PuzzleState<rows> cur_state = path.top().second;
            path.pop();

            StateContent& content = passed[cur_state];
            content.is_closed = true;

            if (cur_state == wanted_state) {
                break;
            }

            ssize_t x_pos = -1, y_pos = -1;
            PuzzleState<rows>::get_zero_position(cur_state, x_pos, y_pos);

            for (size_t dir_idx = 0; dir_idx < rows; ++dir_idx) {
                ssize_t new_x_pos = x_pos + x_shifts[dir_idx];
                ssize_t new_y_pos = y_pos + y_shifts[dir_idx];

                if (is_valid(new_x_pos, new_y_pos) == true) {
                    PuzzleState<rows> vertex = cur_state;
                    std::swap(vertex.state[rows * x_pos + y_pos],
                              vertex.state[rows * new_x_pos + new_y_pos]);

                    bool is_passed = passed.find(vertex) != passed.end();
                    if (is_passed == true && passed[vertex].is_closed == true) {
                        continue;
                    }

                    double new_cost = static_cast<double>(content.cost) + 1.0f;
                    if (is_passed == false || new_cost < passed[vertex].cost) {
                        passed[vertex] = {
                            false, static_cast<ssize_t>(new_cost),
                            PuzzleState<rows>::get_opposite(dir_idx)};

                        double new_priority =
                            new_cost + static_cast<double>(
                                           Heuristic(vertex, wanted_state));
                        path.push({-new_priority, vertex});
                    }
                }
            }
        }
    }

    virtual ~A_star() { passed.clear(); }
};

template <size_t rows>
void print_path(A_star<rows>& a_star,
                const PuzzleState<rows>& beg,
                const PuzzleState<rows>& wanted) {
    auto current = wanted;
    std::vector<PuzzleState<rows>> path;

    while (a_star.passed[current].parent != EOF) {
        path.push_back(current);
        current = current.get_state(a_star.passed[current].parent);
    }

    path.push_back(beg);
    reverse(path.begin(), path.end());

    ssize_t x_pos = 0, y_pos = 0;
    if (PuzzleState<rows>::get_zero_position(path[0], x_pos, y_pos) == false) {
        return;
    }
    for (size_t idx = 1; idx < path.size(); ++idx) {
        ssize_t new_x_pos = 0, new_y_pos = 0;
        if (PuzzleState<rows>::get_zero_position(path[idx], new_x_pos,
                                                 new_y_pos) == false) {
            return;
        }

        if (x_pos != new_x_pos) {
            if (x_pos > new_x_pos) {
                std::cout << "D";
            } else if (x_pos < new_x_pos) {
                std::cout << "U";
            }
        } else {
            if (y_pos > new_y_pos) {
                std::cout << "R";
            } else if (y_pos < new_y_pos) {
                std::cout << "L";
            }
        }

        x_pos = new_x_pos;
        y_pos = new_y_pos;
    }

    std::cout << std::endl;
}

template <size_t rows>
void get_steps(const PuzzleState<rows>& beg_state,
               const PuzzleState<rows>& wanter_state) {
    auto* a_star_search = new A_star<rows>();

    a_star_search->search(beg_state, wanter_state);
    std::cout << a_star_search->passed[wanter_state].cost << std::endl;

    print_path(*a_star_search, beg_state, wanter_state);
    delete a_star_search;
}

int main() {
    const size_t rows = 4;
    PuzzleState<rows> wanted;

    for (size_t row = 0; row < rows; ++row) {
        for (ssize_t column = 0; column < rows; ++column) {
            wanted.state[rows * row + column] =
                static_cast<ssize_t>(row * rows + column + 1);
        }
    }
    wanted.state[rows * (rows - 1) + rows - 1] = 0;

    PuzzleState<rows> beg_state;
    ssize_t cur_num = 0;

    for (size_t row = 0; row < rows; ++row) {
        for (ssize_t column = 0; column < rows; ++column) {
            std::cin >> cur_num;
            beg_state.state[rows * row + column] =
                static_cast<ssize_t>(cur_num);
        }
    }

    if (beg_state.is_solveable() == false) {
        std::cout << -1 << std::endl;
    } else {
        get_steps<rows>(beg_state, wanted);
    }
}