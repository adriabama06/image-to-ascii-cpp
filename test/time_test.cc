#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    auto start = chrono::high_resolution_clock::now();

    auto current = chrono::high_resolution_clock::now();
    
    auto elapsed_time = chrono::duration_cast<chrono::microseconds>(current - start).count();

    while (elapsed_time < 1000000)
    {
        current = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::microseconds>(current - start).count();
    }

    cout << elapsed_time << endl;
}