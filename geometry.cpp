const double eps = 1e-8, pi = acos(-1);
using Real = long double;

struct Point{
  Real x, y;
  Point(Real x = 0.0, Real y = 0.0) : x(x), y(y){}
};
inline Point operator+ (const Point &p, const Point &q) {return Point(p.x+q.x, p.y+q.y);}
inline Point operator- (const Point &p, const Point &q) {return Point(p.x-q.x, p.y-q.y);}
inline Point operator* (const Point &p, Real a) {return Point(p.x*a, p.y*a);}
inline Point operator* (Real a, const Point &p) {return Point(p.x*a, p.y*a);}
inline Point operator/ (const Point &p, Real a) {return Point(p.x/a, p.y/a);}
inline Real cross(const Point &p, const Point &q) {return p.x*q.y - p.y*q.x;}
inline Real dot(const Point &p, const Point &q) {return p.x*q.x + p.y*q.y;}
inline Real abs(const Point &p) {return sqrt(dot(p, p));}
inline bool eq(const Point &p, const Point &q) {return abs(p-q) < eps;}

struct Circle : Point {
  Real r;
  Circle(Point p = Point(0.0, 0.0), Real r = 0.0) : Point(p), r(r){}
};

using Points = vector<Point>;
using Circles = vector<Circle>;

int checker(Circle c1, Circle c2) {
  if(c1.r < c2.r) swap(c1, c2);
  Real d = abs(c1 - c2);
  if(c1.r + c2.r < d) return 4;
  if(eq(c1.r + c2.r, d)) return 3;
  if(c1.r - c2.r < d) return 2;
  if(eq(c1.r - c2.r, d)) return 1;
  return 0;
}

bool intersect(const Circle &c1, const Circle &c2){
  int tmp = checker(c1, c2);
  return 1 <= tmp and tmp <= 3;
}

Points crosspoint(const Circle &c1, const Circle &c2){
  Points res;
  Real d = abs(c1-c2);
  Real a = acos((c1.r*c1.r + d*d - c2.r*c2.r) / (2 * c1.r * d)); // 余弦定理
  Real t = atan2(c2.y - c1.y, c2.x - c1.x);
  Point p1 = c1 + Point(cos(t+a) * c1.r, sin(t+a) * c1.r);
  Point p2 = c1 + Point(cos(t-a) * c1.r, sin(t-a) * c1.r);
  res.pb(p1);
  if(!eq(p1, p2)) res.pb(p2);
  return res;
}