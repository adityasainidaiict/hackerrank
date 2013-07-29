#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>

using namespace std;

int distance(int a, int b, int N) {
    int ai = a / N;
    int aj = a % N;
    int bi = b / N;
    int bj = b % N;
    return abs(bi - ai) + abs(bj - aj);
}

string moveTo(int a, int b, int N) {
    int ai = a / N;
    int aj = a % N;
    int bi = b / N;
    int bj = b % N;
    if (ai > bi) {
        return "UP";
    } else if (ai < bi) {
        return "DOWN";
    } else if (aj > bj) {
        return "LEFT";
    } else if (aj < bj) {
        return "RIGHT";
    } else {
        return "CLEAN";
    }
}

string getNextMove(const string & board, int bi, int bj) {
    static int N = 5;
    static int INF = 999999999;
    static int M = 1 << (N * N);
    vector<int> moves = vector<int>(M, INF);
    vector<int> prev = vector<int>(M, -1);
    vector<int> dirtyCells;
    vector<int> interestingStates;
    set<int> interestingStatesS;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int cell = i * N + j;
            if (board[cell] == 'd')
                dirtyCells.push_back(cell);
        }
    }
    int C = dirtyCells.size();
    moves[0] = 0;
    prev[0] = bi * N + bj;
    interestingStatesS.insert(0);
    interestingStates.push_back(0);
    for (unsigned int i = 0; i < interestingStates.size(); i++) {
        int state = interestingStates[i];
        for (int j = 0; j < C; j++) {
            int nextState = state | (1 << dirtyCells[j]);
            if (interestingStatesS.find(nextState) == interestingStatesS.end()) {
                interestingStates.push_back(nextState);
                interestingStatesS.insert(nextState);
            }
        }
    }
    int S = interestingStates.size();
    for (int i = 1; i < S; i++) {
        int state = interestingStates[i];
        for (int j = 0; j < C; j++) {
            if (state & (1 << dirtyCells[j])) {
                int prevState = state ^ (1 << dirtyCells[j]);
                int prevCell = prev[prevState];
                int dist = distance(prevCell, dirtyCells[j], N);
                if (moves[prevState] + dist < moves[state]) {
                    moves[state] = moves[prevState] + dist;
                    prev[state] = dirtyCells[j];
                }
            }
        }
    }
    int targetState = 0;
    for (int j = 0; j < C; j++)
        targetState |= (1 << dirtyCells[j]);
    int nextCell = 0;
    while (targetState) {
        nextCell = prev[targetState];
        targetState ^= (1 << nextCell);
    }
    return moveTo(prev[0], nextCell, N);
}

int main() {
    int bi, bj;
    cin >> bj >> bi;
    string board;
    for (int i = 0; i < 5; i++) {
        string line;
        cin >> line;
        board += line;
    }
    cout << getNextMove(board, bi, bj) << endl;
    return 0;
}
