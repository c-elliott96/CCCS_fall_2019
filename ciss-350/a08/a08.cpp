// File: a08.cpp 
// Author: Christian Elliott

#include <iostream>
#include <stack>

int main()
{
    std::stack<int> s;
    std::cout << s.empty() << ' ' << s.size() << '\n';

    std::cout << "Pushing 42, 23, 6 ... \n";
    s.push(42);
    std::cout << s.empty() << ' ' << s.size() << ' ' << s.top() << '\n';

    s.push(23);
    std::cout << s.empty() << ' ' << s.size() << ' ' << s.top() << '\n';

    s.push(6);
    std::cout << s.empty() << ' ' << s.size() << ' ' << s.top() << '\n';

    std::cout << "changing top to 1000 ... \n";
    s.top() = 1000;
    std::cout << s.empty() << ' ' << s.size() << ' ' << s.top << '\n';

    std::cout << "pop until empty ... \n";
    while (!s.empty())
    {
        std::cout << s.empty() << ' ' << s.size() << ' ' << s.top() << '\n';
        s.pop();
    }

    std::cout << s.empty() << ' ' << s.size() << '\n';

    std::cout << "copy constructor, operator=, operator== ... \n";
    s.push(5); s.push(3); s.push(7);
    std::stack<int> t = s;
    std::cout << (s == t) << '\n';

    while (!t.empty()) t.pop();
    t = s;

    std::cout << (s == t) << '\n';

    return 0;
}