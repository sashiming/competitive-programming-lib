struct mint {
	long long num;
	mint(long long a = 0) : num((a%+MOD)%MOD){}
	mint operator-() const { return mint(-num); }
	mint &operator+= (const mint &a) {
		if((num += a.num) >= MOD) num -= MOD;
		return *this;
	}
	mint &operator-= (const mint &a) {
		if((num += mod-a.num) >= MOD) num -= MOD;
		return *this;
	}
	mint &operator*= (const mint &a) {
		(num *= a.num) %= MOD;
		return *this;
	}
	mint operator+ (const mint &a) const { return mint(*this) += a; }
	mint operator- (const mint &a) const { return mint(*this) -= a; }
	mint operator* (const mint &a) const { return mint(*this) *= a; }

	inline bool operator== (const mint &a) const { return num == a.num; }
	inline bool operator!= (const mint &a) const { return num != a.num; }

	mint pow(long long n) const {
		mint ret(1), mul(num);
		while(n > 0){
			if(n & 1) ret *= mul;
			mul *= mul;
			n >>= 1;
		}
		return ret;
	}

	// for prime mod	
	mint inverse() const {
		long long a = num, b = MOD, u = 1, v = 0, t;
		while(b > 0){
			t = a/b;
			swap(a -= t*b, b);
			swap(u -= t*v, v);
		}
		return mint(u);
	}
	mint &operator/= (const mint &a) {
		(*this) *= a.inverse();
		return (*this);
	}
	mint operator/ (const mint &a) const { return mint(*this) /= a; }
}
