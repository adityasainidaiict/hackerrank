#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 10000

int T, N;
int chocolates[MAX];
int increments[MAX];
int offers[] = {5, 2, 1};
int nOffers = 3;

int getMinOperations() {
    sort(chocolates, chocolates + N);
    int ops = -1;
    int nFirstOps = 5;
    int firstOp[] = {0, 1, 1, 2, 2};

    for (int k = 0; k < nFirstOps; k++) {
        increments[0] = 0;
        int tempOps = 0;
        for (int i = 1; i < N; i++) {
            int diff = chocolates[i] - chocolates[i - 1] + increments[i - 1];

            if (i == 1) {
                tempOps += firstOp[k];
                diff += k;
            }

            increments[i] = 0;
            for (int j = 0; j < nOffers; j++) {
                int p = diff / offers[j];
                tempOps += p;
                increments[i] += p * offers[j];
                diff -= p * offers[j];
            }
        }
        if (ops == -1 || tempOps < ops)
            ops = tempOps;
    }

    return ops;
}

int main() {
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N;
        for (int j = 0; j < N; j++) {
            cin >> chocolates[j];
        }
        cout << getMinOperations() << endl;
    }
    return 0;
}
