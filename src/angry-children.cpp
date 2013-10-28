#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int getMinimumUnfairness(vector<int> candies, int K) {
    sort(candies.begin(), candies.end());
    int N = candies.size();
    int best = 1 << 30;

    for (int i = 0; i + K <= N; i++) {
        if (candies[i + K - 1] - candies[i] < best)
            best = candies[i + K - 1] - candies[i];
    }

    return best;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> candies;
    candies.assign(N, -1);

    for (int i = 0; i < N; i++)
        cin >> candies[i];

    cout << getMinimumUnfairness(candies, K) << endl;

    return 0;
}
