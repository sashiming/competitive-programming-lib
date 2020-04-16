struct UnionFind {
	vector<int> par;

	UnionFind(int size) : par(size, -1){}
	void init(int n){ par.assign(n, -1); }

	int find(int x){
		if(par[x] < 0) return x;
		else return par[x] = find(par[x]);
	}
	bool same(int x, int y){
		return find(x)==find(y);
	}
	bool unite(int x, int y){
		x = find(x); y = find(y);
		if(x == y) return 0;
		if(par[x] > par[y]) swap(x, y);
		par[x] += par[y];
		par[y] = x;
		return 1;
	}
	int size(int x){
		return -par[find(x)];
	}
};