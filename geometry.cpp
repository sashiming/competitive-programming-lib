inline bool eq(Real a, Real b){return fabs(b-a) < eps;}
Real to_rad(int deg){return (Real)(deg) * pi / 180.0;}
Real to_deg(Real rad){return red * 180.0 / pi;}

/* Point */
struct Point{
  Real x, y;
  Point(Real x = 0.0, Real y = 0.0) : x(x), y(y){}
  friend ostream& operator<< (ostream &os, const Point &p){return os<<fixed<<setprecision(15)<<'('<<p.x<<", "<<p.y<<')';}
  friend istream& operator>> (istream &is, const Point &p){Real a, b; is>>a>>b; p=Point(a,b); return is;}
};

/* Line */
struct Line {
  Point a, b;
  Line(Point a = Point(0.0, 0.0), Point b = Point(0.0, 0.0)) : a(a), b(b){}
  Line(Real A, Real B, Real C){ // Ax + By = C
    if(eq(A, 0.0)) a = Point(0.0, C/B), b = Point(1.0, C/B);
    else if(eq(B, 0.0)) a = Point(C/A, 0.0), b = Point(C/A, 1.0);
    else a = Point(0, C/B), b = Point(C/A, 0);
  }
  friend ostream& operator<< (ostream &os, const Line &l) {return os << l.a << " to " << l.b;}
  friend istream& operator>> (istream &is, const Line &l) {return is >> l.a >> l.b;}
}

/* Segment */
struct Segment : Line{
  Segment(Point a, Point b) : Line(a, b){}
}

/* Circle */
struct Circle : Point {
  Real r;
  Circle(Point p = Point(0.0, 0.0), Real r = 0.0) : Point(p), r(r){}
  friend ostream& operator<< (ostream &os, const Circle &p){return s<<fixed<<setprecision(15)<<'('<<c.x<<", "<<c.y<<", "<<c.r<<')';}
};

using Points = vector< Point >;
using Polygon = vector< Point >;
using Segments = vector< Segment >;
using Lines = vector< Line >;
using Circles = vector< Circle >;

/* Functions */
inline Point operator+ (const Point &p, const Point &q) {return Point(p.x+q.x, p.y+q.y);}
inline Point operator- (const Point &p, const Point &q) {return Point(p.x-q.x, p.y-q.y);}
inline Point operator* (const Point &p, Real a) {return Point(p.x*a, p.y*a);}
inline Point operator* (Real a, const Point &p) {return Point(p.x*a, p.y*a);}
inline Point operator* (const Point &p, const Point &q) {return Point(p.x*q.x - p.y*q.y, p.x*q.y + p.y*q.x);}
inline Point operator/ (const Point &p, Real a) {return Point(p.x/a, p.y/a);}
inline Point conj (const Point &p) {return Point(p.x, -p.y);}
inline Point rot (const Point &p, Real rad) {return Point(cos(rad)*p.x - sin(rad)*p.y, sin(rad)*p.x + cos(rad)*p.y);}
inline Point rot90 (const Point &p) {return Point(-p.y, p.x);}
inline Real cross (const Point &p, const Point &q) {return p.x*q.y - p.y*q.x;}
inline Real dot (const Point &p, const Point &q) {return p.x*q.x + p.y*q.y;}
inline Real norm (const Point &p) {return dot(p, p);}
inline Real abs (const Point &p) {return sqrt(dot(p, p));}
inline Real amp (const Point &p) {Real res=atan2(p.y, p.x);if(res<0){res+=pi*2;}return res;}
inline bool eq (const Point &p, const Point &q) {return abs(p-q) < eps;}
inline bool operator< (const Point &p, const Point &q) {return (fabs(p.x-q.x)>eps ? p.x<q.x : p.y<q.y);}
inline bool operator> (const Point &p, const Point &q) {return (fabs(p.x-q.x)>eps ? p.x>q.x : p.y>q.y);}

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

// 円の交点
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