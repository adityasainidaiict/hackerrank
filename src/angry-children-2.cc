#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long getMinimumUnfairness(vector<long long> candies, int K) {
    sort(candies.begin(), candies.end());
    int N = candies.size();
    vector<long long> sum;
    sum.assign(N, 0);

    sum[0] = candies[0];
    for (int i = 1; i < N; i++)
        sum[i] = sum[i - 1] + candies[i];

    long long cSum = 0;
    for (int i = 0; i < K; i++)
        cSum += (sum[K - 1] - sum[i]) - (K - i - 1) * candies[i];

    long long best = cSum;

    for (int i = 1; i + K <= N; i++) {
        cSum -= ((sum[i - 1 + K - 1] - sum[i - 1]) - (K - 1) * candies[i - 1]);
        cSum += candies[i + K - 1] * (K - 1) - (sum[i + K - 2] - sum[i - 1]);

        if (cSum < best)
            best = cSum;
    }

    return best;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<long long> candies;
    candies.assign(N, -1);

    for (int i = 0; i < N; i++)
        cin >> candies[i];

    cout << getMinimumUnfairness(candies, K) << endl;

    return 0;
}
