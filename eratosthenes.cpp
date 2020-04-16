template<int MAX_N, int prime_size>
struct Prime{
	bool ispri[MAX_N];
	int prime[prime_size];
	int counter = 0;
	constexpr Prime() : ispri(), prime(){
		for(int i = 0; i < MAX_N; i++) ispri[i] = 1;
		ispri[0] = ispri[1] = 0;
		for(int i = 2; i < MAX_N; i++){
			if(ispri[i]){
				prime[counter] = i;
				counter++;
				if(counter > prime_size) break;
			}
			for(int j = i*i; j < MAX_N; j+=i){
				ispri[j] = 0;
			}
		}
	}
};

/* example

contexpr auto p = Prime<100, 10>();
REP(i, 10) cout << p.prime[i] << endl;

/*