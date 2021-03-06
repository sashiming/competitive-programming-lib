template<class T>
struct Matrix {
	vector<vector<T>> A;
	Matrix() {}
	Matrix(size_t n, size_t m) : A(n, vector<T>(m, 0)) {};

	static Matrix I(size_t n) {
		Matrix mat(n);
		for(int i = 0; i < n; i++) mat[i][i] = 1;
		return (mat);
	}

	size_t height() const { return (A.size()); }
	size_t width() const { return (A[0].size()); }

	inline vector<T> &operator[](int k) {
		return (A.at(k));
	}

	Matrix &operator+= (const Matrix &B){
		size_t n = height(), m = width();
		assert(n == B.height() and m == B.width());
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				(*this)[i][j] += B[i][j];
			}
		}
		return (*this);
	}
	Matrix &operator-= (const Matrix &B){
		size_t n = height(), m = width();
		assert(n == B.height() and m == B.width());
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				(*this)[i][j] -= B[i][j];
		return (*this);
	}
	Matrix &operator*= (const Matrix &B){
		size_t n = height(), m = B.width(), p = width();
		assert(p == B.height());
		vector<vector<T>> C(n, vector<T>(m, 0));
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				for(int k = 0; k < p; k++)
					C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
		A.swap(C);
		return (*this);
	}
	Matrix &operator^= (long long p){
		Matrix B = Matrix::I(height());
		while(p > 0){
			if(p & 1) B *= (*this);
			(*this) *= (*this);
			k >>= 1ll;
		}
		A.swap(B.A);
		return (*this);
	}

	Matrix operator+ (const Matrix &B) const {
		return (Matrix(*this) += B);
	}
	Matrix operator- (const Matrix &B) const {
		return (Matrix(*this) -= B);
	}
	Matrix operator* (const Matrix &B) const {
		return (Matrix(*this) *= B);
	}
	Matrix operator^ (const long long p) const {
		return (Matrix(*this) ^= k);
	}
};
