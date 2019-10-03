// file: 
// name: Christian Elliott

#include <iostream>

int main()
{
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 1;
    std::cin >> a >> b >> c >> d >> e >> f >> g;
    
    // Declare your temporary variables below.
    // For instance if you need three temporary variables below you
    // should have "int t0, t1, t2;" below this line

    // REPLACE YOUR WORK for 
    // a = a + b - c * d + e * f / g;

    // Number of temporary variables: 2;

    int t0 = f / g;
    int t1 = e * t0;
    t0 = d + t1; 
    t1 = c * t0;
    t0 = b - t1;
    a = a + t0;

    std::cout << a << ' ' << b << ' ' << c << ' '
              << d << ' ' << e << ' ' << f << ' '
              << g << std::endl;

    // change this so it's just two temp variables alternating
    
    // The original values of b, c, d, e, f, g are preserved.

    return 0;
}