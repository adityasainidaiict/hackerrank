#include <iostream>
#include <string>
#include <map>

using namespace std;

int getChangesToAnagram(string s1, string s2) {
    int N1 = s1.size();
    int N2 = s2.size();
    if (N1 != N2)
        return -1;

    map<char, int> charCount;
    for (int i = 0; i < N2; i++)
        charCount[s2[i]]++;

    int total = N1;
    for (int i = 0; i < N1; i++) {
        if (charCount[s1[i]] > 0) {
            total--;
            charCount[s1[i]]--;
        }
    }

    return total;
}

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        cout << getChangesToAnagram(s.substr(0, s.size() / 2),
                                    s.substr(s.size() / 2)) << endl;
    }
}
