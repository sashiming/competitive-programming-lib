#include <bits/stdc++.h>
using namespace std;

// int powmod(int a, int p, int m){
// 	int res = 1, tmp = a;
// 	while(p != 0){
// 		if(p % 2)
// 			res = (res*tmp) % m;
// 		tmp = (tmp*tmp) % m;
// 		p /= 2;
// 	}
// 	return res;
// }

/*****/
#define int long long
const long long MOD = 1e9+7;

int fact[500000], invfact[500000];

int invmod(int a, int p){ // a^-1 mod p
	int b = p, u = 1, v = 0;
	while(b){
		int t = a / b;
		a -= t*b; swap(a, b);
		u -= t*v; swap(u, v);
	}
	u %= p;
	if(u < 0) u += p;
	return u;
}

void factmod(int m){
	fact[0] = invfact[0] = 1;
	for(int i = 1; i < 500000; i++){
		fact[i] = (fact[i-1] * i) % m;
		invfact[i] = (invfact[i-1] * invmod(i, m)) % m;
	}
}

int nCrmod(int n, int r, int m){
	return (((fact[n] * invfact[r]) % m) * invfact[n-r]) % m;
}

/*****/

signed main(){
	int n, r; cin >> n >> r;
	factmod(MOD);
	cout << nCrmod(n, r, MOD) << endl;

	return 0;
}
