#pragma once

#include "Angle.h"
#include "Point.h"

typedef Point<ll> P;
typedef Angle A;
P::P(A a) : x(a.x), y(a.y) {}
A::A(P p) : x(p.x), y(p.y), t(0) {}

vector<P> minkowskiSum(vector<vector<P>> hs) {
    priority_queue<tuple<A, int, int>> pq;
    P cur = P();
    int s = 0, t = 0;
    rep(i, 0, sz(hs)) {
        auto& v = hs[i];
        reverse(all(v));
        rotate(begin(v), min_element(all(v)), end(v));
        if (sz(v) > 1) pq.push({v[1] - v[0], 0, i}), s += sz(v);
        cur = cur + v[0];
    }
    vector<P> h(s + 1);
    for (h[t++] = cur; sz(pq); pq.pop()) {
        auto [p, j, i] = pq.top();
        if (t >= 2 && !(A(p) < A(h[t - 1] - h[t - 2]))) t--;
        h[t++] = (cur = cur + p);
        auto& v = *hs[i];
        if (++j < sz(v)) pq.push({v[(j + 1) % sz(v)] - v[j], j, i});
    }
    reverse(h.begin(), h.begin() + t);
	return {h.begin(), h.begin() + t - (t >= 2 && h[0] == h[t - 1])};
} 
