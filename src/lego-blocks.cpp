#include <cstring>
#include <iostream>

using namespace std;

#define MOD 1000000007
#define MAX 1001

int nPieces = 4;
int pieces[] = {1, 2, 3, 4};
int T;
int N, M;
long long possibleRowCombinations[MAX];
long long possibleColumnCombinations[MAX];
long long possibleColumnCombinationsWithNoHoles[MAX];

long long modAdd(long long a, long long b) {
    return (a + b) % MOD;
}

long long modMult(long long a, long long b) {
    return (a * b) % MOD;
}

long long modSub(long long a, long long b) {
    return (MOD + a - b) % MOD;
}

long long getNumberOfWays() {
    memset(possibleRowCombinations, 0, sizeof(possibleRowCombinations));
    possibleRowCombinations[0] = 1;
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < nPieces; j++) {
            if (i - pieces[j] >= 0)
                possibleRowCombinations[i] =
                    modAdd(possibleRowCombinations[i],
                           possibleRowCombinations[i - pieces[j]]);
        }
    }

    for (int i = 1; i <= M; i++) {
        long long res = 1;
        for (int j = 1; j <= N; j++) {
            res = modMult(res, possibleRowCombinations[i]);
        }
        possibleColumnCombinations[i] = res;
    }

    possibleColumnCombinationsWithNoHoles[1] = possibleColumnCombinations[1];
    for (int i = 2; i <= M; i++) {
        possibleColumnCombinationsWithNoHoles[i] =
            possibleColumnCombinations[i];
        for (int j = 1; j < i; j++) {
            possibleColumnCombinationsWithNoHoles[i] =
                modSub(possibleColumnCombinationsWithNoHoles[i],
                       modMult(possibleColumnCombinationsWithNoHoles[j],
                               possibleColumnCombinations[i - j]));
        }
    }

    return possibleColumnCombinationsWithNoHoles[M];
}

int main() {
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N >> M;
        cout << getNumberOfWays() << endl;
    }
    return 0;
}
