#include <bits/stdc++.h>
#define int long long
using namespace std;
struct SegmentTree {
    vector<int> sgt;
    vector<int> a;
    int n;
    SegmentTree(int N) {
        this->n = N;
        a.assign(N + 1, 0);
        sgt.assign(N * 4 + 1, 0);
    }
    int combine(int a, int b) {
        return a + b;        // ➜ sum
    }
    void build (int node, int l, int r) {
        if (l == r) {
            sgt[node] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        sgt[node] = combine(sgt[2 * node], sgt[2 * node + 1]);
    }
    void update(int node, int l, int r, int idx, int value) {
        if (l == r) {
            sgt[node] = value;
            return;
        }
        int mid = l + (r - l) / 2;
        if(idx <= mid) {
            update(node * 2, l, mid, idx, value);
        } else {
            update(node * 2 + 1, mid + 1, r, idx, value);
        }
        sgt[node] = combine(sgt[2 * node], sgt[2 * node + 1]);
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (l > qr or r < ql) {
            return 0; // Edit here
        }
        if (l >= ql and r <= qr) {
            return sgt[node];
        }
        int mid = l + (r - l) / 2;
        int left = query(node * 2, l, mid, ql, qr);
        int right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return combine(left, right);
    }
    void build() { build(1, 1, n); }
    void update(int idx, int val) { update(1, 1, n, idx, val); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
};
signed main() {
    int n;
    cin >> n;

    SegmentTree a(n * 2);
    vector<int> pfx(n * 2 + 1, 0), ans(n + 1, 0), x(2 * n + 1);

    for (int i = 1; i <= 2 * n; i++) {
        cin >> x[i];
        
        if (pfx[x[i]] == 0) {
            pfx[x[i]] = i;
            a.update(i, 1);
        } else {
            a.update(pfx[x[i]], 0);
            ans[x[i]] = a.query(pfx[x[i]], i);
            pfx[x[i]] = 0;
        }
    }

    for (int i = 2 * n; i >= 1; i--) {
        if (pfx[x[i]] == 0) {
            pfx[x[i]] = i;
            a.update(i, 1);
        } else {
            a.update(pfx[x[i]], 0);
            ans[x[i]] += a.query(i, pfx[x[i]]);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
