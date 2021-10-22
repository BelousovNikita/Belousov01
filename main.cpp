#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");


class Equation {
public:
    virtual double principalRoot() = 0;
    virtual double sum () = 0;
};

class Disjunction : public Equation {
    Equation *R, *L;
public:
    Disjunction(Equation *R, Equation *L) : R(R), L(L) {
    }

    double principalRoot() {
        double res;
        if (abs(R->principalRoot()) < abs(L->principalRoot()))
            res = (R->principalRoot());
        else if (abs(R->principalRoot()) == abs(L->principalRoot()))
            res = max((R->principalRoot()), abs(L->principalRoot()));
        else (res = (L->principalRoot()));
        return res;
    }
    double sum () {
        return (R->sum() + L->sum());
    }
};

class Linear : public Equation {
    double a;
    double b;
public:
    Linear(double a, double b) : a(a), b(b) {
    }

    double principalRoot() {
        return a == 0 ? 0 : (-b / a);
    }
    double sum () {
        return principalRoot();
    }
};

class Trigonometric : public Equation {
    double k;
public:
    Trigonometric(double k) : k(k) {
    }

    double principalRoot() {
        return asin(k);
    }
    double sum () {
        return principalRoot();
    }
};

int main() {
    int N;
    fin >> N;
    char type;
    double a = 0, b = 0, k = 0, sum = 0;
    Equation *tempr = nullptr;
    Equation *templ = nullptr;
    for (int i = 0; i < N; i++) {
        fin >> type;
        if (type == 'L') {
            fin >> a >> b;
            if (tempr == nullptr) {
                tempr = new Linear(a, b);
            } else if (templ == nullptr) {
                templ = new Linear(a, b);
            } else {
                tempr = new Disjunction(tempr, templ);
                templ = new Linear(a, b);
            }
        } else {
            fin >> k;
            if (tempr == nullptr) {
                tempr = new Trigonometric(k);
            } else if (templ == nullptr) {
                templ = new Trigonometric(k);
            } else {
                tempr = new Disjunction(tempr, templ);
                templ = new Trigonometric(k);
            }
        }
    }
    if (tempr != nullptr and templ != nullptr) tempr = new Disjunction(tempr, templ);
    fout << fixed << setprecision(2) << tempr->sum();
    return 0;
}
