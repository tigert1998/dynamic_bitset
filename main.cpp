#include <bits/stdc++.h>
#include "dynamic_bitset.h"

using namespace std;
const int N = 50010;
int n, m, q, a[N], b[N];

dynamic_bitset A, ans;

void pri(const string &s) {
    cout << s << endl;
    fflush(stdout);
}

void deal(int b) {
    static dynamic_bitset tmp, _tmp;
    tmp = dynamic_bitset(b);
    for (int i = 0; i * b <= a[n]; i++) {
        _tmp = dynamic_bitset(A, i * b, min(b, a[n] - i * b + 1));
        tmp ^= _tmp;
    }
    ans ^= tmp;
    cout << ans.to_string() << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> q;
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
        sort(a + 1, a + n + 1);
        A.resize(a[n] + 1);
        A.reset();
        ans.resize(a[n] + 1);
        ans.reset();

        for (int i = 1; i <= n; i++)
            A[a[i]] = 1;
        for (int i = 1; i <= m; i++)
            scanf("%d", b + i);
        for (int i = 1; i <= m; i++)
            deal(b[i]);
        while (q--) {
            int x;
            scanf("%d", &x);
            printf("%d\n", ans.test(x));
        }
    }
}