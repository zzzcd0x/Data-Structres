#include<cstdio>
#include<queue>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 5e3+5;
const int MAXM = 5e4+5;
const int INF = 0x3f3f3f3f;

int tot = 1;
int n, m, s, t;

ll d[MAXN];
ll dis[MAXN];
int gap[MAXN];
int head[MAXN];
bool vis[MAXN];
int to[MAXM<<1];
ll val[MAXM<<1];
ll cost[MAXM<<1];
int nxt[MAXM<<1];

void add(int x,int y,ll z,ll f) {
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
    val[tot] = z;
    cost[tot] = f;
}

bool bfs() {
    for(int i = 1; i <= n; i++) d[i] = dis[i] = INF;
    queue<int> q;
    q.push(s);
    dis[s] = 1;
    gap[s] = head[s];
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(int i = head[x]; i ; i = nxt[i]) {
            if(val[i] > 0 && dis[to[i]] == INF) {
                q.push(to[i]);
                gap[to[i]] = head[to[i]];
                dis[to[i]] = dis[x] + 1;
                if(to[i] == t) return true;
            }
        }
    }
    return false;
}

ll dinic(int now,ll flow) {
    if(now == t) return flow;
    ll k, res = 0;
    for(int i = gap[now] ; i && flow ; i = nxt[i]) {
        gap[now] = i;
        if(val[i] > 0 && dis[to[i]] == dis[now] + 1) {
            k = dinic(to[i],min(flow,val[i]));
            if(!k) dis[to[i]] = INF;
            val[i] -= k;
            val[i^1] += k;
            res += k;
            flow -= k;  
        }
    }
    return res;
}

void inp() {
    scanf("%d %d %d %d",&n,&m,&s,&t);
    for(int i = 1; i <= m; i++) {
        int x, y;
        ll z, f;
        scanf("%d %d %lld %lld",&x,&y,&z,&f);
        add(x,y,z,f);
        add(y,x,0,-f);
    }
}

int main() {
    inp();

    ll ans = 0;
    while(bfs()) {
        ans += dinic(s,INF);
    }
    
    printf("%lld",ans);

    return 0;
}