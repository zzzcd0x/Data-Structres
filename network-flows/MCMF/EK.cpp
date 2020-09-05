#include<cstdio>
#include<queue>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 5e5+5;
const int MAXM = 5e4+5;
const int INF = 0x3f3f3f3f;

int tot = 1;
ll Max_cost;
ll Max_flow;
int n, m, s, t;

bool v[MAXN];
ll dis[MAXN];
ll incf[MAXN];
int head[MAXN];
int to[MAXM<<1];
ll val[MAXM<<1];
int nxt[MAXM<<1];
ll cost[MAXM<<1];
int pre[MAXM<<1];

void add(int x,int y,ll z,ll h) {
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
    val[tot] = z;
    cost[tot] = h;
}

bool bfs() {
    for(int i = 1; i <= n; i++) {
        v[i] = false;
        dis[i] = INF;
    }
    queue<int> q;
    q.push(s);
    v[s] = true;
    dis[s] = 0;
    incf[s] = INF;
    bool jud = false;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        v[x] = false;
        for(int i = head[x]; i; i = nxt[i]) {
            int y = to[i];
            if(val[i] && dis[y] > dis[x] + cost[i]) {
                pre[y] = i;
                dis[y] = dis[x] + cost[i];
                incf[y] = min(incf[x],val[i]);
                if(!v[y]) {
                    q.push(y);
                    v[y] = true;
                }
                if(y == t) jud = true;
            }
        }
    }
    return jud;
}

void upd() {
    int x = t;
    while(x != s) {
        int i = pre[x];
        val[i] -= incf[t];
        val[i^1] += incf[t];
        x = to[i^1];
    }
    Max_flow += incf[t];
    Max_cost += incf[t]*dis[t];
}

void inp() {
    Max_flow = 0;
    tot = 1;
    scanf("%d %d %d %d",&n,&m,&s,&t);
    for(int i = 1; i <= m; i++) {
        int x,y;
        ll z,h;
        scanf("%d %d %lld %lld",&x,&y,&z,&h);
        add(x,y,z,h);
        add(y,x,0,-h);
    }
}

int main() {

    inp();

    while(bfs()) upd();
    printf("%lld %lld\n",Max_flow,Max_cost);

    return 0;
}