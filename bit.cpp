struct BIT{
  // 1-indexed BIT
private:
  int N; vector<int> bit;
public:
  BIT(vector<int> vec){
    N = vec.size();
    bit.assign(N+1, 0);
    copy(vec.begin(), vec.end(), bit.begin()+1);
  }
  void add(int a, int w){
    for(int x = a; x <= N; x += x & -x)
      bit[x] += w;
  }
  int sum(int a){ // prefix sum
    int res = 0;
    for(int x = a; x > 0; x -= x & -x)
      res += bit[x];
    return res;
  }
};