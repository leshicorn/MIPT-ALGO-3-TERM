#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Checks if a specific bit is set in a given mask.
 * 
 * @param i The index of the bit to check.
 * @param mask The mask to check the bit in.
 * @return true if the bit is set, false otherwise.
 */
bool is_bit_set(unsigned long long i, unsigned long long mask) {
    return ((1 << i) & mask) != 0;
}

/**
 * @brief Checks if two bit masks are similar.
 * 
 * Two bit masks are considered similar if no two adjacent bits are set in both masks.
 * 
 * @param mask1 The first bit mask to compare.
 * @param mask2 The second bit mask to compare.
 * @param m The number of bits in the masks.
 * @return true if the masks are similar, false otherwise.
 */
bool are_masks_similar(size_t mask1, size_t mask2, size_t m) {
    for (size_t i = 1; i < m; ++i) {
        if (is_bit_set(i, mask1) && is_bit_set(i, mask2) && is_bit_set(i - 1, mask1) && is_bit_set(i - 1, mask2)) {
            return false;
        }
        if (!is_bit_set(i, mask1) && !is_bit_set(i, mask2) && !is_bit_set(i - 1, mask1) && !is_bit_set(i - 1, mask2)) {
            return false;
        }
    }
    return true;
}

/**
 * Counts the number of valid profiles given the count of profiles for each mask and the length of the profiles.
 * 
 * @param cnt_profiles A 2D vector containing the count of profiles for each mask and length.
 * @param length The length of the profiles.
 * @param num_of_masks The number of masks.
 * @return The total count of valid profiles.
 */
unsigned long long count_valid_profiles(vector<vector<unsigned long long>>& cnt_profiles, unsigned long long length, unsigned long long num_of_masks) {
    unsigned long long ans = 0;
    for (unsigned long long i = 0; i < num_of_masks; i++) {
        ans += cnt_profiles[length - 1][i];
    }
    return ans;
}

/**
 * @brief Generates a similarity table for a given set of masks.
 * 
 * @param bool_table A 2D vector of booleans representing the similarity table.
 * @param num_of_masks The number of masks to generate the similarity table for.
 * @param width The width of each mask.
 */
void generate_similarity_table(vector<vector<bool>>& bool_table, unsigned long long num_of_masks, unsigned long long width) {
    for (unsigned long long i = 0; i < num_of_masks; i++) {
        for (unsigned long long j = 0; j < num_of_masks; j++) {
            bool_table[i][j] = are_masks_similar(i, j, width);
        }
    }
}

/**
 * Counts the number of profiles of a given length that can be formed from a boolean table.
 * @param bool_table The boolean table used to form the profiles.
 * @param cnt_profiles A 2D vector to store the count of profiles for each mask and length.
 * @param length The length of the profiles to be counted.
 * @param num_of_masks The number of masks in the boolean table.
 */
void count_profiles(const vector<vector<bool>>& bool_table, vector<vector<unsigned long long>>& cnt_profiles, unsigned long long length, unsigned long long num_of_masks) {
    for (unsigned long long i = 1; i < length; i++) {
        for (unsigned long long mask1 = 0; mask1 < num_of_masks; mask1++) {
            for (unsigned long long mask2 = 0; mask2 < num_of_masks; mask2++) {
                cnt_profiles[i][mask1] += cnt_profiles[i - 1][mask2] * (unsigned long long)(bool_table[mask1][mask2]);
            }
        }
    }
}

/**
 * @brief This program counts the number of valid profiles of a rectangular mask.
 * 
 * Given the length and width of a rectangular mask, this program generates all possible profiles of the mask
 * and counts the number of valid profiles. A profile is considered valid if there are no two adjacent rows
 * that are identical. The program uses dynamic programming to count the number of valid profiles.
 * 
 * @return int The number of valid profiles of the rectangular mask.
 */
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    unsigned long long length;
    unsigned long long width;
    cin >> length >> width;
    if (length < width) {
        swap(length, width);
    }
    unsigned long long num_of_masks = (1 << width);
    vector<vector<bool>> bool_table(num_of_masks, vector<bool>(num_of_masks));
    generate_similarity_table(bool_table, num_of_masks, width);
    vector<vector<unsigned long long>> cnt_profiles(length, vector<unsigned long long>(num_of_masks));
    for (unsigned long long i = 0; i < num_of_masks; ++i) {
        cnt_profiles[0][i] = 1;
    }
    count_profiles(bool_table, cnt_profiles, length, num_of_masks);
    cout << count_valid_profiles(cnt_profiles, length, num_of_masks);
}