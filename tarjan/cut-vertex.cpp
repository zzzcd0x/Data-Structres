#include<cstdio>
#include<string.h>
#include<algorithm>
using namespace std;

struct Edge{
    int from;
    int to;
    int next;
}edge[200005];

int sum;
int tot;
int head[20005];

int n, m;
int dfscnt;
int dfn[20005];
int low[20005];
bool cut[20005];

inline int read(){

    int x = 0;
    char c = getchar();

    while(c < '0' || c > '9')
        c = getchar();
    while(c >= '0' && c <= '9')
    {
        x = x*10 + c-'0';
        c = getchar();
    }
    return x;
}

void tarjan(int now,int fa){
    int chi = 0;
    low[now] = dfn[now] = ++dfscnt;
    for(int i = head[now]; i ; i = edge[i].next)
    {
        int to = edge[i].to;
        if(!dfn[to])
        {
            tarjan(to,fa);
            low[now] = min(low[to],low[now]);
            if(low[to] >= dfn[now] && now != fa && !cut[now])
            {
                cut[now] = true;
                sum++;
            }
            if(now == fa)
                chi++;
        }
        low[now] = min(low[now],dfn[to]);//后向边
    }

    if(now == fa && chi >= 2 && !cut[now])
    {
        sum++;
        cut[now] = true;
    }
}

void add(int x,int y){

    edge[++tot].next = head[x];
    head[x] = tot;
    edge[tot].from = x;
    edge[tot].to = y;
}

void inp(){

    n = read();
    m = read();
    for(int i = 1; i <= m; i++)
    {
        int x,y;
        x = read();
        y = read();
        add(x,y);
        add(y,x);
    }
}

int main(){

    inp();

    for(int i = 1; i <= n; i++)
        if(!dfn[i])
            tarjan(i,i);
    
    printf("%d\n",sum);

    for(int i = 1; i <= n; i++)
        if(cut[i])
            printf("%d ",i);

    return 0;
}