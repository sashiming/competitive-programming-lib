// Range Minimum Query
template <typename T>
struct SparseTable {
	int N;
	T** table;
	int* logtable;

	SparseTable(vector<T> &vec){
		N = vec.size();
		logtable = new int[N+1];
		for(int i = 2; i <= N; i++){
			logtable[i] = logtable[i >> 1] + 1;
		}

		table = new T*[N];
		REP(i, N){
			table[i] = new T[logtable[N] + 1];
			table[i][0] = vec[i];
		}
		for(int k = 1; (1<<k) <= N; k++){
			for(int i = 0; i + (1<<k) <= N; i++){
				T first = table[i][k-1];
				T second = table[i+(1<<(k-1))][k-1];
				table[i][k] = min(first, second);
			}
		}
	}

	T query(int l, int r){ // [l, r)
		assert(l < r);
		int length = r-l;
		int k = logtable[length];
		return min(table[l][k], table[r-(1<<k)][k]);
	}
};