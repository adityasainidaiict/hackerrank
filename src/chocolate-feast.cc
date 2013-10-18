#include <iostream>

using namespace std;

int getChocolates(int N, int C, int M) {
    int chocolates = N / C;
    int wrappers = N / C;

    while (wrappers >= M) {
        int n = wrappers / M;
        wrappers = (wrappers % M) + n;
        chocolates += n;
    }

    return chocolates;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, C, M;
        cin >> N >> C >> M;
        cout << getChocolates(N, C, M) << endl;
    }
    return 0;
}
