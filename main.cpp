#include <iostream>
#include <cmath>

int gcd(int n_b, int n_s) // 最大公约数
{
    if(n_b < n_s) return gcd(n_s, n_b);
    else
    {
        if (n_s == 0) return n_b;
        else return gcd(n_s, n_b % n_s);
    }
}

int gbs(int m, int n) // 最小公倍数
{
    return m * n / gcd(m, n);
}


class Rational
{
    int m;   // 分母
    int n;   // 分子
    void simple();
public:
    Rational operator-()
    {
        return Rational(-n, m);
    }

    bool operator>(const Rational &A)
    {
        return (n*A.m - A.n*m) * (m*A.m) > 0;
    }

    explicit Rational(int nn=1,int mm=1); //构造
    friend double operator-(double D, Rational R);
    double operator-(double D);
    Rational operator*(const Rational &A);    //乘法操作，返回乘积对象
    friend std::ostream &operator<<(std::ostream &os, const Rational &R);            //以分数形式显示，注意约分和符号
};

Rational::Rational(int nn, int mm):m(abs(mm)), n(abs(nn))
{
    if(m == 0)
    {
        m = 1;
        std::cerr << "m can't be 0!" << std::endl
        << "m has been set as 1." << std::endl;
    }
    n *= (mm*nn)/abs(mm*nn);
    this -> simple();
}

double operator-(double D, Rational R)
{
    return D - (double)R.n/R.m;
}

double Rational::operator-(double D)
{
    return (double)n / m - D;
}

Rational Rational::operator*(const Rational &A)    //乘法操作，返回乘积对象
{
    Rational output;
    output.m = m * A.m;
    output.n = n * A.n;
    output.simple();
    return output;
}

void Rational::simple()        //约分
{
    int sign = n/abs(n);
    n = abs(n);
    int i = gcd(m, n);
    m /= i;
    n /= i;
    n *= sign;
}

std::ostream &operator<<(std::ostream &os, const Rational &R)
{
    if(R.n == 0)
        os << 0;
    else if(R.m == 1)
        os << R.n;
    else
        os << R.n << '/' << R.m;
    return os;
}


int main()
{
    Rational r1(4, 6), r2(1, 2);
    std::cout << r1 * r2 << std::endl;
    if(r1 > r2)
        std::cout << ">" << std::endl;
    std::cout << r1 << std::endl;
    std::cout << -r1 << std::endl;
    std::cout << -r2 - 1 << std::endl;
    return 0;
}
