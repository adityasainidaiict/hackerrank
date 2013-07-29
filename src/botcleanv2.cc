#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <fstream>

using namespace std;

int distance(int a, int b, int N) {
    int ai = a / N;
    int aj = a % N;
    int bi = b / N;
    int bj = b % N;
    return abs(bi - ai) + abs(bj - aj);
}

int unknownNeighbours(const string & visited, int cell, int N) {
    static int nNeighbours = 8;
    static int neighbours[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
    int i = cell / N;
    int j = cell % N;
    int neig = 0;
    for (int k = 0; k < nNeighbours; k++) {
        int ni = i + neighbours[k][0];
        int nj = j + neighbours[k][1];
        if (ni >= 0 && ni < N && nj >= 0 && nj < N && visited[ni * N + nj] == 'o')
            neig++;
    }
    return neig;
}

string moveTo(const string & visited, int a, int b, int N) {
    int ai = a / N;
    int aj = a % N;
    int bi = b / N;
    int bj = b % N;
    if (a == b)
        return "CLEAN";
    int best = 0;
    string bestMove = "";
    if (ai > bi) {
        int neig = unknownNeighbours(visited, (ai - 1) * N + aj, N);
        if (neig >= best) {
            bestMove = "UP";
            best = neig;
        }
    }
    if (ai < bi) {
        int neig = unknownNeighbours(visited, (ai + 1) * N + aj, N);
        if (neig >= best) {
            bestMove = "DOWN";
            best = neig;
        }
    }
    if (aj > bj) {
        int neig = unknownNeighbours(visited, ai * N + aj - 1, N);
        if (neig >= best) {
            bestMove = "LEFT";
            best = neig;
        }
    }
    if (aj < bj) {
        int neig = unknownNeighbours(visited, ai * N + aj + 1, N);
        if (neig >= best) {
            bestMove = "RIGHT";
            best = neig;
        }
    }
    return bestMove;
}

string getNextMove(const string & board,
                   const string & visited,
                   int bi,
                   int bj) {
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
    if (C == 0) {
        int curr = bi * N + bj;
        int neig = 0;
        int dist = INF;
        int move = bi * N + bj;
        for (int i = 0; i < N; i++) {
            if (i == 0 || i == 4)
                continue;
            for (int j = 0; j < N; j++) {
                if (j == 0 || j == 4 || (i == 2 && j == 2))
                    continue;
                int s = i * N + j;
                int current = unknownNeighbours(visited, s, N);
                int currentDist = distance(curr, s, N);
                if (current > neig || (current == neig && currentDist < dist)) {
                    move = s;
                    neig = current;
                    dist = currentDist;
                }
            }
        }
        return moveTo(visited, curr, move, N);
    } else {
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
                    if (moves[prevState] + dist < moves[state] ||
                        (moves[prevState] + dist == moves[state] &&
                         prev[state] != -1 &&
                         unknownNeighbours(visited, dirtyCells[j], N) > unknownNeighbours(visited, prev[state], N))) {
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
        return moveTo(visited, prev[0], nextCell, N);
    }
}

int main() {
    int N = 5;
    int bi, bj;
    cin >> bj >> bi;
    string board;
    for (int i = 0; i < 5; i++) {
        string line;
        cin >> line;
        board += line;
    }
    ifstream fin("positions");
    ifstream vfin("visited");
    int a, b;
    while (fin >> a >> b)
        board[a * N + b] = 'd';
    string visited;
    if (!(vfin >> visited))
        visited = string(N * N, 'o');
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i * N + j] != 'o') {
                visited[i * N + j] = '-';
            }
        }
    }
    string move = getNextMove(board, visited, bi, bj);
    cout << move << endl;
    ofstream fout("positions");
    ofstream vfout("visited");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i * N + j] != 'o')
                visited[i * N + j] = '-';
            if (move == "CLEAN" && bi == i && bj == j)
                continue;
            if (board[i * N + j] == 'd') {
                fout << i << " " << j << endl;
            }
        }
    }
    vfout << visited << endl;
    return 0;
}
