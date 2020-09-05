#include<cstdio>
#include<queue>
#include<string.h>
#include<algorithm>
using namespace std;
const int INF = 1<<29;
const int MAXN = 1e5+5;

int Max;
int tot = 1;
int n, m, s, t;

bool v[MAXN];
int head[MAXN];
int incf[MAXN];
int to[MAXN<<1];
int pre[MAXN<<1];
int val[MAXN<<1];
int nxt[MAXN<<1];

void add(int x,int y,int z) {
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
    val[tot] = z;
}

queue<int> q;
bool bfs() {
    memset(v,false,sizeof(v));
    q.push(s);
    v[s] = true;
    incf[s] = INF;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(int i = head[x]; i; i = nxt[i]) {
            int y = to[i];
            if(v[y]) continue;
            if(val[i]) {
                incf[y] = min(incf[x],val[i]);
                pre[y] = i;
                q.push(y);
                v[y] = true;
            }
        }
    }
    return v[t] != false;
}

void upd() {
    int x = t;
    while(x != s) {
        int i = pre[x];
        val[i] -= incf[t];
        val[i^1] += incf[t];
        x = to[i^1];
    }
    Max += incf[t];
}

void inp() {
    Max = 0;
    tot = 1;
    scanf("%d %d %d %d",&n,&m,&s,&t);
    for(int i = 1; i <= m; i++) {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        add(x,y,z);
        add(y,x,0);
    }
}

int main() {

    inp();

    while(bfs()) upd();
    printf("%d\n",Max);

    return 0;
}