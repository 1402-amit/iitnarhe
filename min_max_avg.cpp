//Implement Min, Max, Sum  and Average operations using Parallel  Reduction
// commands to execute code
//> gcc -o min_max_avg -fopenmp min_max_avg.cpp -lstdc++
//> ./min_max_avg


#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;
void min_reduction(vector<int> &arr)
{
    int min_value = arr[0];
    omp_set_num_threads(4);
    #pragma omp parallel for reduction(min: min_value) 
        for (int i = 0; i < arr.size(); i++) 
        {
            if (arr[i] < min_value)
            {
                min_value = arr[i];
            }
        }
 cout << "Minimum value: " << min_value << endl;
}
void max_reduction(vector<int> &arr)
{
    int max_value = 0;
    #pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}
void sum_reduction(vector<int> &arr)
{
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

void average_reduction(vector<int> &arr)
{
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    cout << "Average: " << (double)sum / arr.size() << endl;
}

int main()
{
    vector<int> arr = {5, 2, 9, 1, 7, 6, 8, 3, 4};
    double st=omp_get_wtime();
    min_reduction(arr);
    max_reduction(arr);
    sum_reduction(arr);
    average_reduction(arr);
    double et=omp_get_wtime();
    cout<<"Parallel operations time:"<<et-st<<endl;
    return 0;
}