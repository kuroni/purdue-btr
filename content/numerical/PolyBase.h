/**
 * Author: chilli, Andrew He, Adamant
 * Date: 2019-04-27
 * Description: A FFT based Polynomial class.
 */
#pragma once

#include "../number-theory/ModularArithmetic.h"
#include "FastFourierTransform.h"
#include "FastFourierTransformMod.h"
#include "NumberTheoreticTransform.h"

typedef Mod num;
typedef vector<num> poly;
poly &operator+=(poly &a, const poly &b) {
	a.resize(max(sz(a), sz(b)));
	rep(i, 0, sz(b)) a[i] = a[i] + b[i];
	return a;
}
poly &operator-=(poly &a, const poly &b) {
	a.resize(max(sz(a), sz(b)));
	rep(i, 0, sz(b)) a[i] = a[i] - b[i];
	return a;
}

poly &operator*=(poly &a, const poly &b) {
	if (sz(a) + sz(b) < 100){
		poly res(sz(a) + sz(b) - 1);
		rep(i,0,sz(a)) rep(j,0,sz(b))
			res[i + j] = (res[i + j] + a[i] * b[j]);
		return (a = res);
	}
	// auto res = convMod<mod>(vl(all(a)), vl(all(b)));
	auto res = conv(vl(all(a)), vl(all(b)));
	return (a = poly(all(res)));
}
poly operator*(poly a, const num b) {
	poly c = a;
<<<<<<< HEAD
<<<<<<< HEAD
	for(auto& i : c) i = i * b;
=======
	trav(i, c) i = i * b;
>>>>>>> 5063a41 (First commit)
=======
	for(auto& i : c) i = i * b;
>>>>>>> 9bcad7b (Added BostanMori and MinkowskiSum + various changes)
	return c;
}
#define OP(o, oe) \
	poly operator o(poly a, poly b) { \
		poly c = a; \
		return c o##= b; \
	}
OP(*, *=) OP(+, +=) OP(-, -=);
