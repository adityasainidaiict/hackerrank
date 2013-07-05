#include <iostream>
#include <string>
#include <map>

using namespace std;

bool hasAnagramPalindrome(string s) {
    map<char, int> charCount;
    for (unsigned int i = 0; i < s.size(); i++)
        charCount[s[i]]++;

    int oddCount = 0;
    for (map<char, int>::iterator itr = charCount.begin();
         itr != charCount.end();
         itr++) {
        if (itr->second % 2)
            oddCount++;
    }

    return oddCount <= 1;
}

int main() {
    string s;
    cin >> s;
    cout << (hasAnagramPalindrome(s) ? "YES" : "NO") << endl;
    return 0;
}
