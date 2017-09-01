#include <bits/stdc++.h>
#include "dynamic_bitset.h"

// ===============
// dynamic_bitset
//  library demo
//   hdu 6085
// ===============

using namespace std;
const int N = 50010;
int n, m, q, a[N], b[N];

dynamic_bitset A, ans;

void deal(int b)
{
    static dynamic_bitset tmp, _tmp;
    tmp = dynamic_bitset(b);
    for (int i = 0; i * b <= a[n]; i++)
    {
        _tmp = dynamic_bitset(A, i * b, min(b, a[n] - i * b + 1));
        tmp ^= _tmp;
    }
    ans ^= tmp;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m >> q;
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
        for (int i = 1; i <= m; i++)
            scanf("%d", b + i);
        sort(a + 1, a + n + 1);
        sort(b + 1, b + m + 1);

        A.resize(a[n] + 1);
        A.reset();
        ans.resize(b[m]);
        ans.reset();

        for (int i = 1; i <= n; i++)
            A[a[i]] = 1;
        for (int i = 1; i <= m; i++)
            deal(b[i]);
        while (q--)
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", ans.test(x));
        }
    }
    return 0;
}