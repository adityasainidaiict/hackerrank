#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX 51

int N, K;
int parent[MAX];
int nConnections[MAX];
int connections[MAX][MAX];
int nChildren[MAX];
int children[MAX][MAX];
bool visited[MAX];
long long subtrees[MAX][MAX];

void buildTreeAux(int node) {
    for (int i = 0; i < nConnections[node]; i++) {
        int c = connections[node][i];
        if (c != parent[node]) {
            children[node][nChildren[node]++] = c;
            parent[c] = node;
            buildTreeAux(c);
        }
    }
}

void buildTree() {
    memset(nChildren, 0, sizeof(nChildren));
    memset(parent, -1, sizeof(parent));
    buildTreeAux(1);
}

void calcSubtrees(int node) {
    if (!visited[node]) {
        visited[node] = true;
        if (nChildren[node] == 0)
            subtrees[node][1] = parent[node] != -1;
        else {
            long long tempSubtrees[nChildren[node] + 1][MAX];
            for (int i = 0; i <= nChildren[node]; i++) {
                for (int j = 0; j <= N; j++) {
                    tempSubtrees[i][j] = 0;
                }
            }
            tempSubtrees[0][0] = 1;

            for (int i = 1; i <= nChildren[node]; i++) {
                int c = children[node][i - 1];

                calcSubtrees(c);

                for (int j = 0; j <= N; j++) {
                    tempSubtrees[i][j + 1] += tempSubtrees[i - 1][j];
                }

                for (int j = 0; j <= N; j++) {
                    for (int k = 1; (j + k - 1) <= N; k++) {
                        tempSubtrees[i][j + k - 1] +=
                            (tempSubtrees[i - 1][j] * subtrees[c][k]);
                    }
                }
            }

            for (int i = 0; i <= N; i++) {
                if (((parent[node] != -1) + i) <= N)
                    subtrees[node][(parent[node] != -1) + i] =
                        tempSubtrees[nChildren[node]][i];
            }
        }
    }
}

long long getPossibleSubtrees() {
    memset(visited, false, sizeof(visited));
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j++)
            subtrees[i][j] = 0;

    for (int i = 1; i <= N; i++)
        if (!visited[i])
            calcSubtrees(i);

    long long total = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            total += subtrees[i][j];
        }
    }

    return total;
}

int main() {
    memset(nConnections, 0, sizeof(nConnections));

    cin >> N >> K;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        connections[a][nConnections[a]++] = b;
        connections[b][nConnections[b]++] = a;
    }

    buildTree();

    cout << getPossibleSubtrees() << endl;

    return 0;
}
