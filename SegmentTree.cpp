// RMQ
struct SegmentTree{
private:
  int n, OUT; vector<int> node;
public:
  SegmentTree(vector<int> vec, int &OUT){
    int siz = vec.size();
    n = 1; while(n < siz) n <<= 1;
    node.resize(n*2-1, OUT);
    REP(i, siz) node[n-1+i] = vec[i];
    for(int i = n-2; i >= 0; i--)
      node[i] = compare(node[i*2+1], node[i*2+2]);
  }
  inline int compare(int a, int b){
    return min(a, b);
  }
  void update(int i, int val){
    i += n-1;
    node[i] = val;
    while(i > 0){
      i = (i-1) / 2;
      node[i] = compare(node[i*2+1], node[i*2+2]);
    }
  }
  int query(int a, int b, int now = 0, int l = 0, int r = -1){
    if(r < 0) r = n;
    if(r <= a or b <= l) return OUT;
    if(a <= l and r <= b) return node[now];
    int vl = query(a, b, now*2+1, l, (l+r)/2);
    int vr = query(a, b, now*2+2, (l+r)/2, r);
    return compare(vl, vr);
  }
};