#include <iostream>
#include <algorithm>

using namespace std;

int T, l, b;

int getMaxSquares() {
    int best = 0;
    int maxValue = min(l, b);

    for (int i = 1; i <= maxValue; i++) {
        if (l % i == 0 && b % i == 0)
            best = (l / i) * (b / i);
    }

    return best;
}

int main() {
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> l >> b;
        cout << getMaxSquares() << endl;
    }
    return 0;
}
