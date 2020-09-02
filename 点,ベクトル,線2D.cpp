#include <cassert>
#include <cmath>
#include <utility>
#include <vector>
const long double EPS = 1E-10;


class Point2D{
    double x, y;
public:
    Point2D(double X=0, double Y=0): x(X), y(Y){}
    Point2D(const Point2D& v): x(v.x), y(v.y){}
    template<class T>
    Point2D(const std::vector<T> &v){
        assert(v.size() == 2);
        x = v[0]; y = v[1];
    }
    template<class T, class T2>
    Point2D(const std::pair<T, T2> &p){
        x = p.first; y = p.second;
    }

    void setX(double X){x = X;}
    double getX(){return x;}
    void setY(double Y){y = Y;}
    double getY(){return y;}

    Point2D operator+() const{return *this;}
    Point2D operator-() const{return Point2D(-x, -y);}

    Point2D& operator=(const Point2D& v){
        x = v.x; y = v.y;
        return *this;
    }

    Point2D& operator+=(const Point2D& v){
        x += v.x; y += v.y;
        return *this;
    }

    Point2D& operator-=(const Point2D& v){
        x -= v.x; y -= v.y;
        return *this;
    }

    Point2D& operator*=(const double a){
        x *= a; y *= a;
        return *this;
    }

    Point2D& operator/=(const double a){
        x /= a; y /= a;
        return *this;
    }

    Point2D operator+(const Point2D& v) const{
        Point2D tmp(*this);
        return tmp += v;
    }

    Point2D operator-(const Point2D& v) const{
        Point2D tmp(*this);
        return tmp -= v;
    }

    Point2D operator*(const double a) const{
        Point2D tmp(*this);
        return tmp *= a;
    }

    friend Point2D operator*(double a, const Point2D v){
        return v * a;
    }

    Point2D operator/(const double a) const{
        Point2D tmp(*this);
        return tmp /= a;
    }

    double norm(){return x*x + y*y;}
    friend double norm(Point2D v){return v.norm();}
    double abs(){return sqrt(norm());}
    friend double abs(Point2D v){return v.abs();}

    bool operator<(const Point2D &v) const{
        return x != v.x ? x < v.x : y < v.y;
    }

    bool operator>(const Point2D &v) const{
        return x != v.x ? x > v.x : y > v.y;
    }

    bool operator==(const Point2D &v) const{
        return std::abs(x - v.x) < EPS
            && std::abs(y - v.y) < EPS;
    }

    bool operator<=(const Point2D &v) const{
        return (*this < v) || (*this == v);
    }

    bool operator>=(const Point2D &v) const{
        return (*this > v) || (*this == v);
    }

    double dot(Point2D b){
        return x*b.x + y*b.y;
    }

    friend double dot(Point2D a, Point2D b){
        return a.dot(b);
    }

    double cross(Point2D b){
        return x*b.x - y*b.x;
    }

    friend double cross(Point2D a, Point2D b){
        return a.cross(b);
    }

    friend double distance(Point2D a, Point2D b){
        return (a - b).abs();
    }

    friend bool isParallel(Point2D a, Point2D b){
        return std::abs(a.cross(b)) < EPS;
    }

    friend bool isOrthogonal(Point2D a, Point2D b){
        return std::abs(a.dot(b)) < EPS;
    }

    int ccw(Point2D b){
        if(cross(b) > EPS) return 1;//反時計
        if(cross(b) < -EPS) return -1;//時計
        if(dot(b) < -EPS) return 2;//逆向き
        if(norm() < b.norm()) return -2;//同じ向きbが大きい
        return 0;//同じ向きaが大きい
    }

    friend int ccw(Point2D a, Point2D b){
        return a.ccw(b);//同じ向きaが大きい
    }

    int ccw(Point2D p1, Point2D p2){
        return (p1 - *this).ccw(p2 - *this);
    }

    friend int ccw(Point2D p0, Point2D p1, Point2D p2){
        return p0.ccw(p1, p2);
    }

    friend bool intersect(Point2D p1, Point2D p2, Point2D p3, Point2D p4){
        return(p1.ccw(p2, p3) * p1.ccw(p2, p4) <= 0 &&
               p3.ccw(p4, p1) * p3.ccw(p4, p2) <= 0);
    }
};
using Vector2D = Point2D;

class Line2D{
    Point2D p1, p2;
public:
    Line2D(){}
    Line2D(Point2D a, Point2D b): p1(a), p2(b){}

    void setP1(const Point2D p){p1 = p;}
    Point2D getP1(){return p1;}
    void setP2(const Point2D p){p2 = p;}
    Point2D getP2(){return p2;}

    Point2D project(Point2D p){
        Point2D base(p2 - p1);
        double r(dot(p - p1, base) / norm(base));
        return p1 + base * r;
    }

    friend Point2D project(Line2D l, Point2D p){
        return l.project(p);
    }

    friend Point2D reflect(Line2D l, Point2D p){
        return p + 2.0 * (l.project(p) - p);
    }

    friend bool isParallel(Line2D s1, Line2D s2){
        return isParallel(s1.p2 - s1.p1, s2.p2- s2.p1);
    }

    friend bool isOrthogonal(Line2D s1, Line2D s2){
        return isOrthogonal(s1.p2 - s1.p1, s2.p2- s2.p1);
    }

    friend bool intersect(Line2D s1, Line2D s2){
        return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
    }
};
using Segment2D = Line2D;
