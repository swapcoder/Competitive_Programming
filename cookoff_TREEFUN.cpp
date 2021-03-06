#include <stdio.h>

const int N = 100010;

int tin[N], tout[N], d[N], p[N], ss[N], ff[N], pred[N], last[N], g[N], used[N];
int pr[20][N];
int tt, n, q, i, m, t, kg, j, time;

int anc(int x, int y) {
  return (tin[x] <= tin[y]) && (tout[y] <= tout[x]);
}

int lca(int x, int y) {
  if (anc(x, y)) return x;
  for (int j=17;j>=0;j--)
    if (!anc(pr[j][x], y)) x = pr[j][x];
  return p[x];
}

void go(int v) {
  tin[v] = ++time;
  int j = last[v];
  while (j > 0) {
    if (!tin[ff[j]]) {
      d[ff[j]] = d[v]+1;
      p[ff[j]] = v;
      go(ff[j]);
    }
    j = pred[j];
  }
  tout[v] = ++time;
}

int main() {
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d %d", &n, &q);
    int m = n-1;
    for (i=1;i<=m;i++) {
      scanf("%d %d", &ss[i], &ff[i]);
      ss[i+m] = ff[i];
      ff[i+m] = ss[i];
    }
    for (i=1;i<=n;i++) last[i] = 0;
    for (i=1;i<=m+m;i++) {
      pred[i] = last[ss[i]];
      last[ss[i]] = i;
    }
    for (i=1;i<=n;i++) tin[i] = tout[i] = 0;
    time = 0;
    d[1] = 0; p[1] = 1;
    go(1);
    for (i=1;i<=n;i++) pr[0][i] = p[i];
    for (j=1;j<=17;j++)
      for (i=1;i<=n;i++) pr[j][i] = pr[j-1][pr[j-1][i]];
    for (i=1;i<=n;i++) used[i] = 0;
    for (t=1;t<=q;t++) {
      scanf("%d", &kg);
      for (i=0;i<kg;i++) scanf("%d", &g[i]);
      if (kg == 2) {
        int v = lca(g[0], g[1]);
        printf("%d\n", d[g[0]]+d[g[1]]-2*d[v]-1);
      } else {
        int x = lca(g[0], g[1]), y = lca(g[0], g[2]), z = lca(g[1], g[2]);
        if (d[y] > d[x]) x = y;
        if (d[z] > d[x]) x = z;
        int up = 0;
        for (i=0;i<kg;i++)
          if (x == g[i]) up = 2; else
          if (!anc(x, g[i])) up++; else {
            int u = g[i];
            for (j=17;j>=0;j--)
              if (d[pr[j][u]] > d[x]) u = pr[j][u];
            if (used[u] == t) up = 2;
            used[u] = t;
          }
        printf("%d\n", (up <= 1) ? 1 : 0);
      }
    }
  }
  return 0;
}
