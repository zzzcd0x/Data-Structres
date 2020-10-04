/*  区间修改时1为整个区间乘某个数，2为整个区间加某个数
    tag数组开到3是为了防RE
*/
#include<cstdio>
#include<ctype.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 4e5+5;
const int INF = 0x3f3f3f3f;

int n, m, p;
int le[MAXN];
int ri[MAXN];
ll num[MAXN];
ll sum[MAXN];
ll Max[MAXN];
ll Min[MAXN];
ll tag[3][MAXN];

inline int ls(int now) {return now<<1;}
inline int rs(int now) {return now<<1|1;}
void pushup(int now) {
    sum[now] = (sum[ls(now)] + sum[rs(now)]);
    Max[now] = max(Max[now],max(Max[ls(now)],Max[rs(now)]));
    Min[now] = min(Min[now],min(Min[ls(now)],Min[rs(now)]));
}
//标记下放
void pushdown(int now) {
    int mid = (l+r)>>1;
    int L = ls(now),R = rs(now);
    int l = le[now],r = ri[now];
    sum[L] = (tag[1][now]*sum[L]+(mid-l+1)*tag[2][now]);
    Max[L] = (tag[1][now]*Max[L]+(mid-l+1)*tag[2][now]);
    Min[L] = (tag[1][now]*Min[L]+(mid-l+1)*tag[2][now]);
    sum[R] = (tag[1][now]*sum[R]+(r-mid)*tag[2][now]);
    Max[R] = (tag[1][now]*Max[R]+(mid-l+1)*tag[2][now]);
    Min[R] = (tag[1][now]*Min[R]+(mid-l+1)*tag[2][now]);

    tag[1][L] = (tag[1][L]*tag[1][now]);
    tag[1][R] = (tag[1][R]*tag[1][now]);

    tag[2][L] = (tag[2][L]*tag[1][now]+tag[2][now]);
    tag[2][R] = (tag[2][R]*tag[1][now]+tag[2][now]);

    tag[1][now] = 1;
    tag[2][now] = 0;
}
//更新
void upd(int now,int f,ll k) {
    if(f == 1) {
        tag[1][now] = (tag[1][now]*k);
        tag[2][now] = (tag[2][now]*k);
        sum[now] = (sum[now]*k);
        Max[now] = (Max[now]*k);
        Min[now] = (Min[now]*k);
    }
    else if(f == 2) {
        int l = le[now],r = ri[now];
        tag[2][now] = (tag[2][now]+k);
        sum[now] = (sum[now]+k*(r-l+1));
        Max[now] = (Max[now]+k*(r-l+1));
        Min[now] = (Min[now]+k*(r-l+1));
    }
}
//建树
void build(int now,int l,int r) {
    le[now] = l,ri[now] = r;
    tag[1][now] = 1,tag[2][now] = 0;
    if(l == r) {
        sum[now] = Max[now] = Min[now] = num[l];
        return;
    }
    int mid = (l+r)>>1;
    build(ls(now),l,mid);
    build(rs(now),mid+1,r);
    pushup(now);
}
//区间修改
void modify(int now,ll k,int f,int L,int R) {
    int l = le[now],r = ri[now];
    if(L <= l && R >= r) {
        upd(now,f,k);
        return;
    }

    pushdown(now);
    int mid = (l+r)>>1;
    if(L <= mid) modify(ls(now),k,f,L,R);
    if(R > mid) modify(rs(now),k,f,L,R);
    pushup(now);
}
//查询区间和
ll querysum(int now,int L,int R) {
    int l = le[now],r = ri[now];

    if(L <= l && R >= r) return sum[now];

    ll ans = 0;
    int mid = (l+r)>>1;

    pushdown(now);

    if(L <= mid) ans += querysum(ls(now),L,R);
    if(R > mid) ans += querysum(rs(now),L,R);

    return ans;
}
//查询区间最大值
ll querymax(int now,int L,int R) {
    int l = le[now],r = ri[now];

    if(L <= l && R >= r) return Max[now];

    pushdown(now);

    ll ans = -INF;
    int mid = (l+r)>>1;

    if(l <= mid) ans = max(ans,querymax(ls(now),L,R));
    if(R > mid) ans = max(ans,querymax(rs(now),L,R));

    return ans;
}
//查询区间最小值
ll querymin(int now,int L,int R) {
    int l = le[now],r = ri[now];

    if(L <= l && R >= r) return Min[now];

    pushdown(now);

    ll ans = INF;
    int mid = (l+r)>>1;

    if(L <= mid) ans = min(ans,querymin(ls(now),L,R));
    if(R > mid) ans = min(ans,querymin(rs(now),L,R));

    return ans;
}