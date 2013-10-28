#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> getMoves(vector<string> board) {
    int mi, mj, pi, pj;
    int N = board.size();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 'm') {
                mi = i;
                mj = j;
            } else if (board[i][j] == 'p') {
                pi = i;
                pj = j;
            }
        }
    }
    vector<string> res;
    while (mi > pi) {
        res.push_back("UP");
        mi--;
    }
    while (mi < pi) {
        res.push_back("DOWN");
        mi++;
    }
    while (mj > pj) {
        res.push_back("LEFT");
        mj--;
    }
    while (mj < pj) {
        res.push_back("RIGHT");
        mj++;
    }
    return res;
}

int main() {
    int N;
    vector<string> board;
    cin >> N;
    for (int i = 0; i < N; i++) {
        string line;
        cin >> line;
        board.push_back(line);
    }
    vector<string> moves = getMoves(board);
    for (unsigned int i = 0; i < moves.size(); i++)
        cout << moves[i] << endl;
    return 0;
}
