#include<cstdio>
#include<string.h>
#include<algorithm>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e5+5;

inline int read() {
    int x = 0;
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    while(c >= '0' && c <= '9') {
        x = x*10 + c-'0';
        c = getchar();
    }
    return x;
}

int tot;
int cnt;
int num;
int stop;
int n, m;
int d[MAXN];
int s[MAXN];
int x[MAXN];
int y[MAXN];
int dp[MAXN];
int to[MAXM];
int val[MAXM];
int nxt[MAXM];
int dfn[MAXN];
int low[MAXN];
int sum[MAXM];
int head[MAXM];
bool ins[MAXN];

void add(int x,int y) {
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}

void inp() {
    n = read();
    m = read();
    for(int i = 1; i <= n; i++) 
        val[i] = read();
    for(int i = 1; i <= m; i++) {
        x[i] = read();
        y[i] = read();
        add(x[i],y[i]);
    }
}

void tarjan(int now) {
    dfn[now] = low[now] = ++cnt;
    s[++stop] = now;
    ins[now] = true;
    for(int i = head[now]; i; i = nxt[i]) {
        int y = to[i];
        if(!dfn[y]) {
            tarjan(y);
            low[now] = min(low[y],low[now]);
        }
        else if(ins[y]) {
            low[now] = min(low[now],dfn[y]);
        }
    }
    if(dfn[now] == low[now]) {
        ++num;
        while(s[stop+1] != now) {
            d[s[stop]] = num;
            sum[num] += val[s[stop]];
            ins[s[stop--]] = false;
        }
    }
}

void dfs(int now) {
    if(dp[now]) return;
    dp[now] = sum[now];
    int Max = 0;
    for(int i = head[now]; i; i = nxt[i]) {
        int y = to[i];
        if(!dp[y]) dfs(y);
        Max = max(Max,dp[y]);
    }
    dp[now] += Max;
}

int main() {

    inp();

    for(int i = 1; i <= n; i++)
        if(!d[i])
            tarjan(i);
    
    tot = 0;
    memset(to,0,sizeof(to));
    memset(nxt,0,sizeof(nxt));
    memset(head,0,sizeof(head));

    for(int i = 1; i <= m; i++) {
        if(d[x[i]] != d[y[i]])
            add(d[x[i]],d[y[i]]);
    }
    int ans = -1;
    for(int i = 1; i <= num; i++) {
        if(!dp[i]) {
            dfs(i);
            ans = max(ans,dp[i]);
        }
    }

    printf("%d\n",ans);

    return 0;
}