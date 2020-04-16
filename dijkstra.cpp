void dijkstra(const vector<vector<edge2> > &G, int s, INTV &dist/*, INTV &prev*/){
	int E = G.size();
	dist.assign(E, VERYBIG); dist[s] = 0;
	// prev.assign(E, -1);
	priority_queue<INTP, vector<INTP>, greater<INTP> > que;
	que.push({0, s}); // {dist, index}
	while(!que.empty()){
		INTP p = que.top(); que.pop();
		int v = p.second;
		if(dist[v] < p.first) continue;
		REP(i, G[v].size()){
			edge2 e = G[v][i];
			if(dist[e.to] > dist[v]+e.cost){
				dist[e.to] = dist[v]+e.cost;
				// prev[e.to] = v;
				que.push({dist[e.to], e.to});
			}
		}
	}
}

// INTV get_path(int t, INTV &prev){
//   INTV path;
//   for(; t != -1; t = prev[t]){
//     path.eb(t);
//   }
//   reverse(ALL(path));
//   return path;
// }

/**********   cut   *********/

/*
#define MAX_V 100000
int V;
typedef pair<int, int> P;
struct edge {int to, cost;};
vector<edge> graph[MAX_V];
int d[MAX_V];

void dijkstra(int s){
	fill(d, d+V, INF); d[s] = 0;
	priority_queue<P, vector<P>, greater<P> > que;
	que.push(P(0, s));
	while(!que.empty()){
		P a = que.top(); que.pop();
		if(d[a.second] < a.first) continue;
		REP(i, graph[a.second].size()){
			edge e = graph[a.second][i];
			if(d[e.to] > d[a.second]+e.cost){
				d[e.to] = d[a.second]+e.cost;
				que.push(P(d[e.to], e.to));
			}
		}
	}
}
*/