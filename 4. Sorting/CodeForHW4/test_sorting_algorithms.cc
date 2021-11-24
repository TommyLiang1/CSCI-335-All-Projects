// Homework 4
// Testing Sorting Algorithms
// Tommy Liang
// This is the file that contains the testing for Homework 4

#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include "Sort.h"
using namespace std;

// Computes duration given a start time and a stop time in nano seconds.
// Keep it in.
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time,
                          chrono::high_resolution_clock::time_point end_time)
{
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

// Test function that shows how you can time a piece of code.
// Just times a simple loop. Remove for final submission.

void TestTiming()
{
  cout << "Test Timing" << endl;
  const auto begin_time = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i)
    sum++;
  // End of piece of code to time.
  const auto end_time = chrono::high_resolution_clock::now();
  cout << ComputeDuration(begin_time, end_time) << "ns" << endl;
}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector)
{
  // Use rand() to generate random integer
  vector<int> random_vector;
  srand(time(NULL));
  for (unsigned i = 0; i < size_of_vector; i++)
    random_vector.push_back(rand());
  return random_vector;
}

// Generates and returns sorted vector of size @size_of_vector.
// If @smaller_to_larger is true, returns vector sorted from small to large.
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger)
{
  vector<int> sorted_vector;
  if (smaller_to_larger)
    for (unsigned i = 0; i < size_of_vector; i++)
      sorted_vector.push_back(i);
  else
    for (unsigned i = size_of_vector; i > 0; i--)
      sorted_vector.push_back(i);
  return sorted_vector;
}

// Verifies that a vector is sorted given a comparator.
// I.e. it applies less_than() for consecutive pair of elements and returns true
// iff less_than() is true for all pairs.
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than)
{
  for (unsigned i = 1; i < input.size(); i++)
  {
    if (input[i] != input[i - 1] && less_than(input[i], input[i - 1]))
      return false;
  }
  return true;
}

// Wrapper function to test different sorting algorithms. See homework's PDF for details.
void testSortingWrapper(int argc, char **argv)
{
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small")
  {
    cout << "Invalid input type" << endl;
    return;
  }
  if (input_size <= 0)
  {
    cout << "Invalid size" << endl;
    return;
  }
  if (comparison_type != "less" && comparison_type != "greater")
  {
    cout << "Invalid comparison type" << endl;
    return;
  }

  // This block of code to be removed for your final submission.

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " " << comparison_type << "\n"
       << endl;
  vector<int> input_vector;
  if (input_type == "random")
  {
    input_vector = GenerateRandomVector(input_size);
  }
  else if (input_type == "sorted_small_to_large")
  {
    input_vector = GenerateSortedVector(input_size, true);
  }
  else if (input_type == "sorted_large_to_small")
  {
    input_vector = GenerateSortedVector(input_size, false);
  }

  if (comparison_type == "less")
  {
    const auto begin_time = chrono::high_resolution_clock::now();
    HeapSort(input_vector, less<int>{});
    const auto end_time = chrono::high_resolution_clock::now();
    std::cout << "Heapsort\n\n"
              << "Runtime: " << ComputeDuration(begin_time, end_time) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";

    const auto begin_time1 = chrono::high_resolution_clock::now();
    MergeSort(input_vector, less<int>{});
    const auto end_time1 = chrono::high_resolution_clock::now();
    std::cout << endl;
    std::cout << "MergeSort\n\n"
              << "Runtime: " << ComputeDuration(begin_time1, end_time1) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n\n";

    const auto begin_time2 = chrono::high_resolution_clock::now();
    QuickSort(input_vector, less<int>{});
    const auto end_time2 = chrono::high_resolution_clock::now();
    std::cout << "QuickSort\n\n"
              << "Runtime: " << ComputeDuration(begin_time2, end_time2) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";

    std::cout << "\nTesting Quicksort Pivot Implementations" << std::endl;
    std::cout << std::endl;

    const auto begin_time3 = chrono::high_resolution_clock::now();
    Median3(input_vector, less<int>{});
    const auto end_time3 = chrono::high_resolution_clock::now();
    std::cout << "Median of Three\n\n"
              << "Runtime: " << ComputeDuration(begin_time3, end_time3) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n\n";

    const auto begin_time4 = chrono::high_resolution_clock::now();
    QuickSort2(input_vector, less<int>{});
    const auto end_time4 = chrono::high_resolution_clock::now();
    std::cout << "Middle\n\n"
              << "Runtime: " << ComputeDuration(begin_time4, end_time4) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n\n";

    const auto begin_time5 = chrono::high_resolution_clock::now();
    QuickSort3(input_vector, less<int>{});
    const auto end_time5 = chrono::high_resolution_clock::now();
    std::cout << "First\n\n"
              << "Runtime: " << ComputeDuration(begin_time5, end_time5) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n";
  }
  else if (comparison_type == "greater")
  {
    const auto begin_time = chrono::high_resolution_clock::now();
    HeapSort(input_vector, greater<int>{});
    const auto end_time = chrono::high_resolution_clock::now();
    std::cout << "Heapsort\n\n"
              << "Runtime: " << ComputeDuration(begin_time, end_time) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

    const auto begin_time1 = chrono::high_resolution_clock::now();
    MergeSort(input_vector, greater<int>{});
    const auto end_time1 = chrono::high_resolution_clock::now();
    std::cout << endl;
    std::cout << "MergeSort\n\n"
              << "Runtime: " << ComputeDuration(begin_time1, end_time1) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

    const auto begin_time2 = chrono::high_resolution_clock::now();
    QuickSort(input_vector, greater<int>{});
    const auto end_time2 = chrono::high_resolution_clock::now();
    std::cout << endl;
    std::cout << "QuickSort\n\n"
              << "Runtime: " << ComputeDuration(begin_time2, end_time2) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";

    std::cout << "\nTesting Quicksort Pivot Implementations" << std::endl;
    std::cout << endl;

    const auto begin_time3 = chrono::high_resolution_clock::now();
    Median3(input_vector, greater<int>{});
    const auto end_time3 = chrono::high_resolution_clock::now();
    std::cout << "Median of Three\n\n"
              << "Runtime: " << ComputeDuration(begin_time3, end_time3) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n\n";

    const auto begin_time4 = chrono::high_resolution_clock::now();
    QuickSort2(input_vector, greater<int>{});
    const auto end_time4 = chrono::high_resolution_clock::now();
    std::cout << "Middle\n\n"
              << "Runtime: " << ComputeDuration(begin_time4, end_time4) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n\n";

    const auto begin_time5 = chrono::high_resolution_clock::now();
    QuickSort3(input_vector, greater<int>{});
    const auto end_time5 = chrono::high_resolution_clock::now();
    std::cout << "First\n\n"
              << "Runtime: " << ComputeDuration(begin_time5, end_time5) << " ns\n";
    std::cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n";
    /*
    for (auto x : input_vector)
      std::cout << x << " ";
    std::cout << std::endl;
    */
  }
}

int main(int argc, char **argv)
{
  // DO NOT CHANGE or ADD ANY CODE in this function.
  if (argc != 4)
  {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }

  testSortingWrapper(argc, argv);

  return 0;
}