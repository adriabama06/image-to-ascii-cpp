#include <iostream>
#include <string>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, const vector<string>& arr)
{
    const size_t arr_size = arr.size();
    
    os << "[";
    
    for (size_t i = 0; i < arr_size; i++)
    {
        os << arr.at(i);
        if(i+1 != arr_size)
        {
            os << ", ";
        }
    }

    os << "]";

    return os;
}

void sort_by_aplhabet(vector<string> &arr)
{
    string temp;
    const size_t arr_size = arr.size();
    for (size_t i = 0; i < arr_size; i++)
    {
        for (size_t j = i + 1; j < arr_size; j++)
        {
            if (arr.at(i) > arr.at(j))
            {
                temp = arr.at(i);

                arr.at(i) = arr.at(j);
                
                arr.at(j) = temp;
            }
        }
    }
}

int main()
{
    vector<string> arr;
    arr.push_back("C");
    arr.push_back("A");
    arr.push_back("B");

    cout << arr << endl;

    cout << "Sort:" << endl;

    sort_by_aplhabet(arr);

    cout << arr << endl;
}