// Range Minimum Query
// abstracted

template <typename T, typename F>
struct SegmentTree {
	int n; T *dat;
	T identity; F merge;
	SegmentTree(F f, T id) : merge(f), identity(id){}
	void init(int siz){
		n = 1; while(n < siz) n <<= 1;
		dat = new T[n*2-1];
		REP(i, n*2-1) dat[i] = identity;
	}
	void set(int i, T x){
		dat[i+n-1] = x;
	}
	void build(void){
		for(int i = n-2; i >= 0; i--){
			dat[i] = merge(dat[i*2 + 1], dat[i*2 + 2]);
		}
	}
	void update(int i, T x){
		i += n-1;
		dat[i] = x;
		while(i > 0){
			i = (i-1) / 2;
			dat[i] = merge(dat[i*2 + 1], dat[i*2 + 2]);
		}
	}
	T query(int l, int r){  // [l, r)(0-indexed), 処理だけ 1-indexed で考える
		l += n, r += n;
		T res = identity;
		while(l < r){
			if(r & 1){
				--r; res = merge(res, dat[r-1]);
			}
			if(l & 1){
				res = merge(res, dat[l-1]);
				++l;
			}
			l >>= 1; r >>= 1;
		}
		return res;
	}
};

// AOJ DSL_2_A
signed main(void){
	int N, Q; cin >> N >> Q;
	auto f = [&](int a, int b){ return min(a, b); };
	SegmentTree<int, decltype(f)> seg(f, (1<<31)-1);
	seg.init(N);
	REP(_, Q){
		int com, x, y; cin >> com >> x >> y;
		if(com) cout << seg.query(x, y+1) << endl;
		else seg.update(x, y);
	}
}