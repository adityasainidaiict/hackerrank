#include <iostream>
#include <vector>

using namespace std;

#define MOD 10007

int getWaysAux(int i, int j, int N) {
    static vector<vector<int> > w =
        vector<vector<int> >(N, vector<int>(N, 0));

    if (i >= N || j >= N)
        return 0;
    if (i == N - 1 && j == N - 1)
        return 1;

    if (w[i][j] == 0)
        w[i][j] = (getWaysAux(i, j + 1, N) +
                   (i != j ? getWaysAux(i + 1, j, N) : 0)) % MOD;

    return w[i][j];
}

int getWays(int N) {
    if (N == 1)
        return 1;
    return (getWaysAux(0, 0, N) * 2) % MOD;
}

int main() {
    int N;
    cin >> N;

    cout << getWays(N) << endl;

    return 0;
}
