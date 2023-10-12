/**
 * Author: tfg, Aeren, pajenegod, chilli
 * Date: 2020-04-15
 * License: CC0
 * Source: https://codeforces.com/blog/entry/69287
 * Description: Given two matroids, finds the largest common independent set.
 * For the color and graph matroids, this would be the largest forest where no
 * two edges are the same color. A matroid has 3 functions
 * \begin{itemize}
 * \item check(int x): returns if current matroid can add x without becoming dependent
 * \item add(int x): adds an element to the matroid (guaranteed to never make it dependent)
 * \item clear(): sets the matroid to the empty matroid
 * \end{itemize}
 * The matroid is given an int representing the element, and is expected to
 * convert it (e.g: the color or the endpoints)
 * Pass the matroid with more expensive add/clear operations to $M_1$.
 * Time: $O(R^2N(M_2.a + M_1.ch + M_2.ch) + R^3 M_1.a + R^2 M_1.cl + RN M_2.cl)$
 * Status: Tested on SWERC 2011D, Pick Your Own Nim
 * Usage:
 * Details:
 */
#include "../data-structures/UnionFind.h"

struct ColorMat {
	vi cnt, clr;
	ColorMat(int n, vector<int> clr) : cnt(n), clr(clr) {}
	bool check(int x) { return !cnt[clr[x]]; }
	void add(int x) { cnt[clr[x]]++; }
	void clear() { fill(all(cnt), 0); }
};
struct GraphMat {
	UF uf;
	vector<array<int, 2>> e;
	GraphMat(int n, vector<array<int, 2>> e) : uf(n), e(e) {}
	bool check(int x) { return !uf.sameSet(e[x][0], e[x][1]); }
	void add(int x) { uf.join(e[x][0], e[x][1]); }
	void clear() { uf = UF(sz(uf.e)); }
};
template <class M1, class M2> struct MatroidIsect {
	int n;
	vector<char> iset;
	M1 m1; M2 m2;
	MatroidIsect(M1 m1, M2 m2, int n) : n(n), iset(n + 1), m1(m1), m2(m2) {}
	vi solve() {
		rep(i,0,n) if (m1.check(i) && m2.check(i))
			iset[i] = true, m1.add(i), m2.add(i);
		while (augment());
		vi ans;
		rep(i,0,n) if (iset[i]) ans.push_back(i);
		return ans;
	}
	bool augment() {
		vector<int> frm(n, -1);
		queue<int> q({n}); // starts at dummy node
		auto fwdE = [&](int a) {
			vi ans;
			m1.clear();
			rep(v, 0, n) if (iset[v] && v != a) m1.add(v);
			rep(b, 0, n) if (!iset[b] && frm[b] == -1 && m1.check(b))
				ans.push_back(b), frm[b] = a;
			return ans;
		};
		auto backE = [&](int b) {
			m2.clear();
			rep(cas, 0, 2) rep(v, 0, n)
				if ((v == b || iset[v]) && (frm[v] == -1) == cas) {
					if (!m2.check(v))
						return cas ? q.push(v), frm[v] = b, v : -1;
					m2.add(v);
				}
			return n;
		};
		while (!q.empty()) {
			int a = q.front(), c; q.pop();
			for (int b : fwdE(a))
				while((c = backE(b)) >= 0) if (c == n) {
					while (b != n) iset[b] ^= 1, b = frm[b];
					return true;
				}
		}
		return false;
	}
};
