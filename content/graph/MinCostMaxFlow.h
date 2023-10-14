/**
 * Author: Andrew He
 * Date: Unknown
 * Source: https://codeforces.com/contest/1178/submission/57573815
 * Description: Min-cost max-flow.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: Approximately O(E^2)
 */
#pragma once

// #include <bits/extc++.h> /// include-line, keep-include

const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;

struct MCMF {
	int N;
	vector<vi> adj;
	struct edge {
		int dest;
		ll cap, cost;
	};
	vector<edge> edges;
 
	VL pi, dist;
	vi prv, vis;
	__gnu_pbds::priority_queue<pair<ll, int>> q;
	vector<typename decltype(q)::point_iterator> its;
 
	MCMF(int N) : N(N), adj(N), pi(N, 0), prv(N), vis(N) {}
 
	void addEdge(int from, int to, ll cap, ll cost) {
		int e = int(edges.size());
		edges.emplace_back(edge{to, cap, cost});
		edges.emplace_back(edge{from, 0, -cost});
		adj[from].push_back(e);
		adj[to].push_back(e+1);
	}
 
	void path(int s) {
		dist.assign(N, INF);
		dist[s] = 0;
 
		its.assign(N, q.end());
		its[s] = q.push({0, s});
 
		while (!q.empty()) {
			int i = q.top().second; q.pop();
			ll d = dist[i];
			for (int e : adj[i]) {
				if (edges[e].cap) {
					int j = edges[e].dest;
					ll nd = d + edges[e].cost;
					if (nd < dist[j]) {
						dist[j] = nd;
						prv[j] = e;
						if (its[j] == q.end()) {
							its[j] = q.push({-(dist[j] - pi[j]), j});
						} else {
							q.modify(its[j], {-(dist[j] - pi[j]), j});
						}
					}
				}
			}
		}
 
		swap(pi, dist);
	}
 
	pair<ll, ll> maxflow(int s, int t) {
		ll totFlow = 0, totCost = 0;
		while (path(s), pi[t] < INF) {
			ll fl = INF;
			for (int cur = t; cur != s; ) {
				int e = prv[cur], nxt = edges[e^1].dest;
				fl = min(fl, edges[e].cap);
				cur = nxt;
			}
			totFlow += fl; totCost += pi[t] * fl;
			for (int cur = t; cur != s; ) {
				int e = prv[cur], nxt = edges[e^1].dest;
				edges[e].cap -= fl;
				edges[e^1].cap += fl;
				cur = nxt;
			}
		}
		return {totFlow, totCost};
	}

/*
	// SPFA if the graph is dense
	void path(int s) {
		dist.assign(N, INF); dist[s] = 0;
		queue<int> q;
		for (q.push(s); !q.empty(); q.pop()) {
			int i = q.front(); vis[i] = 0;
			ll d = dist[i];
			for (int e : adj[i]) {
				if (edges[e].cap) {
					int j = edges[e].dest;
					ll nd = d + edges[e].cost;
					if (nd < dist[j]) {
						dist[j] = nd;
						prv[j] = e;
						if (!vis[j]) {
							vis[j] = 1; q.push(j);
						}
					}
				}
			}
		}
		swap(pi, dist);
	}
*/

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
				for (int e : adj[i]) if (auto [to, cap, cost] = edges[e]; cap)
					if ((v = pi[i] + edges[e].cost) < pi[to])
						pi[to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};
