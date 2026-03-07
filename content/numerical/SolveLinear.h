/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$ modulo a prime. 
 * If there are multiple solutions, an arbitrary one is returned.
 * Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
 * Written to be easily modifiable to work with reals
 * Just remove/adjust commented lines and remove mods.
 * Time: O(n^2 m)
 * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
 */
#pragma once
const double eps = 1e-12;
template<class T>
int solveLinear(vector<vector<T>>& A, 
    vector<T>& b, vector<T>& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m); 
	vi col(m); iota(all(col), 0);
	rep(i,0,n) {
		T v, bv = 0;
		rep(r,i,n) rep(c,i,m)
			if ((v = std::abs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv <= T(eps)) {
			rep(j,i,n) if(std::abs(b[j]) > T(eps)) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = modpow(A[i][i],mod-2); //bv = T(1)/A[i][i];
		rep(j,i+1,n) {
			T fac = (A[j][i] * bv) % mod;
			b[j] -= (fac * b[i])%mod;
            if(b[j]<0) b[j]+=mod; //remove line
			rep(k,i+1,m){
                A[j][k] -= (fac*A[i][k])%mod;
                if(A[j][k]<0) A[j][k]+=mod; //remove line
            }
		}
		rank++;
	}
	x.assign(m, 0);
	for (int i = rank; i--;) { //b[i]/=A[i][i] below
		b[i] = (b[i] * modpow(A[i][i],mod-2))%mod; 
		x[col[i]] = b[i];
		rep(j,0,i){
            b[j] -= (A[j][i] * b[i])%mod;
            if(b[j] < 0) b[j]+=mod; //remove line
        }
	}
	return rank;
}