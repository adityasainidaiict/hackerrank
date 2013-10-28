#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

int length(long long n) {
    int l = 0;
    while (n) {
        n /= 10;
        l++;
    }
    return l;
}

long long getPad(int n) {
    static map<int, long long> pads;

    if (pads.find(n) == pads.end()) {
        long long p = 1;
        for (int i = 1; i <= n; i++)
            p *= 10;
        pads[n] = p;
    }

    return pads[n];
}

string multiply(string n1, string n2) {
    int s1 = n1.size();
    int s2 = n2.size();
    string res = string(s1 + s2, '0');

    for (int i = s1 - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = s2 - 1; j >= 0 || carry; j--) {
            int n = (res[s1 - 1 - i + s2 - 1 - j] - '0') +
                (j >= 0 ? (n1[i] - '0') * (n2[j] - '0') : 0) + carry;
            res[s1 - 1 - i + s2 - 1 - j] = (n % 10) + '0';
            carry = n / 10;
        }
    }

    reverse(res.begin(), res.end());

    while (res[0] == '0')
        res.erase(res.begin());
    if (res.size() == 0)
        res = "0";

    return res;
}

string sum(string n1, string n2) {
    int s1 = n1.size();
    int s2 = n2.size();
    string res = string(max(s1, s2) + 1, '0');

    int carry = 0;
    int S = res.size();
    for (int i = 0; i < S - 1 || carry; i++) {
        int digit = carry;
        if (i < s1)
            digit += n1[s1 - 1 - i] - '0';
        if (i < s2)
            digit += n2[s2 - 1 - i] - '0';
        res[S - 1 - i] = (digit % 10) + '0';
        carry = digit / 10;
    }

    while (res.size() > 0 && res[0] == '0')
        res.erase(res.begin());

    if (res == "")
        return "0";
    return res;
}

string toString(long long n) {
    ostringstream ss;
    ss << n;
    return ss.str();
}

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long progressionSum(long long start,
                         long long step,
                         long long len) {
    return len * (start + (start + (len - 1) * step)) / 2;
}

long long progressionIntersection(long long step1, long long step2) {
    if (step1 > step2)
        swap(step1, step2);
    if (step2 % step1 == 0)
        return step2;
    return step1 * step2 / gcd(step1, step2);
}

void removeProgressions(long long xn,
                        long long B,
                        set<long long> progressions,
                        long long & pSum,
                        long long & pCount);

void addProgressions(long long xn,
                     long long B,
                     set<long long> progressions,
                     long long & pSum,
                     long long & pCount);

void removeProgressions(long long xn,
                        long long B,
                        set<long long> progressions,
                        long long & pSum,
                        long long & pCount) {
    for (set<long long>::iterator itr = progressions.begin();
         itr != progressions.end();
         itr++) {
        long long step = *itr;
        long long len = (B * xn) / step;
        long long tot = progressionSum(step, step, len);

        pSum -= tot;
        pCount -= len;
    }

    for (set<long long>::iterator itr1 = progressions.begin();
         itr1 != progressions.end();
         itr1++) {

        set<long long> intersections;

        for (set<long long>::iterator itr2 = progressions.begin();
             *itr2 < *itr1 && itr2 != progressions.end();
             itr2++) {
            long long step = progressionIntersection(*itr2, *itr1);

            if (step <= B * xn) {
                intersections.insert(step);
            }
        }

        if (intersections.size() > 0)
            addProgressions(xn, B, intersections, pSum, pCount);
    }
}

void addProgressions(long long xn,
                     long long B,
                     set<long long> progressions,
                     long long & pSum,
                     long long & pCount) {
    for (set<long long>::iterator itr = progressions.begin();
         itr != progressions.end();
         itr++) {
        long long step = *itr;
        long long len = (B * xn) / step;
        long long tot = progressionSum(step, step, len);

        pSum += tot;
        pCount += len;
    }

    for (set<long long>::iterator itr1 = progressions.begin();
         itr1 != progressions.end();
         itr1++) {
        set<long long> intersections;

        for (set<long long>::iterator itr2 = progressions.begin();
             *itr2 < *itr1 && itr2 != progressions.end();
             itr2++) {
            long long step = progressionIntersection(*itr2, *itr1);
            if (step <= B * xn)
                intersections.insert(step);
        }

        if (intersections.size() > 0)
            removeProgressions(xn, B, intersections, pSum, pCount);
    }
}

string getSumOfHackerrankNumbers(int A, int B) {
    long long leftSum = 0;
    long long leftCount = 0;

    for (long long x = 1; x <= A; x++) {
        leftSum += progressionSum(x, x, B);
        leftCount += B;
    }

    for (long long x1 = 1; x1 <= A; x1++) {
        set<long long> intersections;
        for (long long x2 = x1 + 1; x2 <= A; x2++) {
            long long xi = progressionIntersection(x1, x2);

            if (xi <= B * x1)
                intersections.insert(xi);
        }

        if (intersections.size() > 0)
            removeProgressions(x1, B, intersections, leftSum, leftCount);
    }

    string totalSum = "0";
    int LB = length(B);

    if (B > 30) {
        int rPad = 1;
        while ((1 << rPad) <= A)
            rPad++;

        vector<vector<long long> > possibleXors =
            vector<vector<long long> >(1 << 5, vector<long long>());
        for (long long x = 1; x <= A; x++) {
            for (long long i = 0; i < 1 << rPad; i++) {
                if (i == 0 && B >> rPad == 0)
                    continue;

                for (long long j = i; j < 1 << rPad; j++) {
                    long long v = x ^ i;
                    if (find(possibleXors[j].begin(), possibleXors[j].end(), v) == possibleXors[j].end())
                        possibleXors[j].push_back(v);
                }
            }
        }

        long long limit = B >> rPad;
        long long defaultPad = getPad(LB);
        long long rightSum = 0;
        long long rightCount = 0;

        for (long long y = 0; y <= limit; y++) {
            long long limitX = (1 << rPad) - 1;
            while (limitX > 0 && ((y << rPad) + limitX) > B)
                limitX--;

            for (unsigned int i = 0; i < possibleXors[limitX].size(); i++) {
                long long r = (y << rPad) + possibleXors[limitX][i];

                rightSum += r;
                rightCount++;
            }
        }

        totalSum = sum(totalSum, sum(multiply(multiply(toString(leftSum),
                                                       toString(defaultPad)),
                                              toString(rightCount)),
                                     multiply(toString(rightSum),
                                              toString(leftCount))));
    } else {
        set<long long> visited;

        for (long long x = 1; x <= A; x++) {
            for (long long y = 1; y <= B; y++) {
                long long r = x ^ y;
                if (visited.find(r) == visited.end()) {
                    visited.insert(r);
                    totalSum = sum(totalSum, sum(multiply(toString(leftSum),
                                                          toString(getPad(max(LB, length(r))))),
                                                 multiply(toString(r),
                                                          toString(leftCount))));
                }
            }
        }
    }

    return totalSum;
}

int main() {
    int A, B;
    cin >> A >> B;
    cout << getSumOfHackerrankNumbers(A, B) << endl;
    return 0;
}
