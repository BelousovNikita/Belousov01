#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

class Complex{
    double Re, Im;

public:
    Complex(): Re(1), Im (0)
    {
    }

    Complex(const double a, const double b): Re(a), Im(b)
    {
    }

    Complex operator+(const Complex &other)
    {
        return Complex(Re + other.Re, Im + other.Im);
    }

    Complex operator+(const double scalar)
    {
        return *this + Complex(scalar, 0);
    }

    Complex operator-(const Complex &other)
    {
        return Complex(Re - other.Re, Im - other.Im);
    }

    Complex operator-(const double scalar)
    {
        return *this - Complex(scalar, 0);
    }

    Complex operator*(const Complex &other)
    {
        return Complex(Re * other.Re - Im * other.Im, Re * other.Im + other.Re * Im);
    }

    Complex operator*(const double scalar)
    {
        return *this * Complex(scalar, 0);
    }

    Complex operator/(const Complex &other)
    {
        return Complex((other.Re * Re + Im * other.Im) / (pow(other.Re, 2) + pow(other.Im, 2)),
                       (other.Re * Im - Re * other.Im) / (pow(other.Re, 2) + pow(other.Im, 2)));
    }

    Complex operator/(const double scalar)
    {
        return *this / Complex(scalar, 0);
    }

    bool operator==(const Complex &other)
    {
        return (Re == other.Re && Im == other.Im);
    }

    bool operator!=(const Complex &other)
    {
        return (Re != other.Re && Im != other.Im);
    }

    double abs()
    {
        return sqrt(pow(Re, 2) + pow(Im, 2));
    }

    void print()
    {
        if (Im >= 0)
        {
            fout << fixed << setprecision(2) << Re << "+i*" << Im;
        } else {
            fout << fixed << setprecision(2) << Re << "-i*" << -Im;
        }
    }

    void read()
    {
        fin >> Re >> Im;
    }
};

int main()
{
    Complex a, b, c, d;
    a.read();
    b.read();
    c.read();
    d.read();
    Complex res = ((a * b) - (c * d)) + Complex(a.abs() * a.abs(), d.abs() * d.abs()) + (c * Complex(b.abs() * b.abs(), 1));
    res.print();
    return 0;
}
