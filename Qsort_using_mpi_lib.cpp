#include <iostream>
#include <vector>
#include <mpi.h>
#define MAX_ARRAY_SIZE 100
using namespace std;
void swap(int& a, int& b) {
 int t = a;
 a = b;
 b = t;
}
int partition(vector<int>& arr, int low, int 
high) {
 int pivot = arr[high];
 int i = (low - 1);
 for (int j = low; j <= high - 1; j++) {
 if (arr[j] < pivot) {
 i++;
 swap(arr[i], arr[j]);
 }
 }
 swap(arr[i + 1], arr[high]);
 return (i + 1);
}
void quickSort(vector<int>& arr, int low, int 
high) {
 if (low < high) {
 int pi = partition(arr, low, high);
 quickSort(arr, low, pi - 1);
 quickSort(arr, pi + 1, high);
 }
}
int main(int argc, char** argv) {
 int rank, size;
 vector<int> arr(MAX_ARRAY_SIZE);
 MPI_Init(&argc, &argv);
 MPI_Comm_rank(MPI_COMM_WORLD, 
&rank);
 
MPI_Comm_size(MPI_COMM_WORLD, 
&size);
 if (rank == 0) {
 cout << "Parallel Quicksort using 
MPI:" << endl;
 cout << "Enter the number of elements: 
";
 int n;
 cin >> n;
 cout << "Enter elements: ";
 for (int i = 0; i < n; i++)
 cin >> arr[i];
 }
 MPI_Bcast(arr.data(), 
MAX_ARRAY_SIZE, MPI_INT, 0, 
MPI_COMM_WORLD);
 int n = arr.size();
 quickSort(arr, 0, n - 1);
 MPI_Finalize();
 if (rank == 0) {
 cout << "Sorted array: " << endl;
 for (int i = 0; i < n; i++)
 cout << arr[i] << " ";
 cout << endl;
 }
 return 0;
}
