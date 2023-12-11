#include <iostream>

using namespace std;

int main() {
    long n, j, cnt = 9999999999, tmpcnt = 0, i;
    cin >> n;
    int* a = new int[n];
    int* is_border = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        is_border[i] = 0;
    }

    for (j = 0; j < 31; j++)
    {
        int cx = a[j];
        i = j;

        for (int m = 0; m < n; m++) {
            is_border[m] = 0;
        }

        while (is_border[i % n] == 0) {
            if ((cx & a[(i + 1) % n]) == 0) {
                cx = cx | a[(i + 1) % n];
            }
            else {
                cx = a[(i + 1) % n];
                is_border[i % n] = 1;
                tmpcnt++;
            }
            i++;
        }

        cnt = min(cnt, tmpcnt);
        tmpcnt = 0;
    }
    cout << cnt;
}