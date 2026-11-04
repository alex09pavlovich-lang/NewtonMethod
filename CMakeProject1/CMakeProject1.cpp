
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

// Structure for storing root information
struct Root {
    double value;
    double residual;
    int iterations;
};

// Cubic equation
double f(double x, double a, double b, double c, double d) {
    return a * x * x * x + b * x * x + c * x + d;
}

// Derivative of cubic equation
double df(double x, double a, double b, double c) {
    return 3 * a * x * x + 2 * b * x + c;
}

// Newton's method
Root newtonMethod(double x0,
    double a, double b, double c, double d) {

    const double eps = 1e-10;
    const int maxIterations = 1000;

    double x = x0;

    for (int i = 1; i <= maxIterations; i++) {

        double derivative = df(x, a, b, c);

        if (!isfinite(derivative) ||
            abs(derivative) < 1e-14) {
            return { x, abs(f(x, a, b, c, d)), i };
        }

        double nextX = x - f(x, a, b, c, d) / derivative;

        if (!isfinite(nextX)) {
            return { nextX, INFINITY, i };
        }

        if (abs(nextX - x) < eps) {
            x = nextX;
            return { x, abs(f(x, a, b, c, d)), i };
        }

        x = nextX;
    }

    return { x, abs(f(x, a, b, c, d)), maxIterations };
}

int main() {

    double a, b, c, d;

    cout << "CUBIC EQUATION: ax^3 + bx^2 + cx + d = 0\n";

    cout << "Enter coefficients a, b, c, d: ";
    cin >> a >> b >> c >> d;

    if (!cin || !isfinite(a) || !isfinite(b) ||
        !isfinite(c) || !isfinite(d) || a == 0) {
        cout << "Invalid coefficients!\n";
        return 1;
    }

    // Initial approximations
    vector<double> starts;

    for (double x = -10; x <= 10; x += 0.5) {
        starts.push_back(x);
    }

    vector<Root> roots;

    for (double x0 : starts) {

        Root result = newtonMethod(x0, a, b, c, d);

        if (isfinite(result.value) &&
            isfinite(result.residual) &&
            result.residual < 1e-7) {

            bool duplicate = false;

            for (const auto& root : roots) {
                if (abs(root.value - result.value) < 1e-6) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                roots.push_back(result);
            }
        }
    }

    sort(roots.begin(), roots.end(),
        [](const Root& x, const Root& y) {
            return x.value < y.value;
        });

    cout << fixed << setprecision(10);

    cout << "\nNumber of roots found: " << roots.size() << "\n\n";

    cout << setw(15) << "Root"
        << setw(20) << "Residual"
        << setw(15) << "Iterations" << "\n";

    for (const auto& root : roots) {
        cout << setw(15) << root.value
            << setw(20) << root.residual
            << setw(15) << root.iterations << "\n";
    }

    if (roots.empty()) {
        cout << "\nNo roots found with the selected initial approximations.\n";
    }

    return 0;
}
