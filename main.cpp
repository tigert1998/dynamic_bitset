#include <bits/stdc++.h>
#include "dynamic_bitset.h"
using namespace std;
const int N = 50010;
int n, m, q, a[N];

dynamic_bitset A;

void deal(int b)
{
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int x;
        scanf("%d", &x);
        A[x] = 1;
    }
}