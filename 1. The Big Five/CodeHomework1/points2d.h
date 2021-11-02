// Tommy Liang
// Few comments describing the class Points2D
// The Points2D class is an array consisting of 2D Points with an x and y value.
// So essentially, it is a 2D array but with a column size of 2.
// This class has the construction of the big 5 constructors, print Points2D class, and read Points2D from a given text file.

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project
{

  // Place comments that provide a brief explanation of the class,
  // and its sample usage.
  template <typename Object>
  class Points2D
  {
  public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation.

    // Zero-parameter constructor.
    // Set size to 0.
    Points2D() : size_(0)
    {
      sequence_ = nullptr;
    }

    // Copy-constructor.
    Points2D(const Points2D &rhs) : size_(rhs.size_)
    {
      //Copy the data members from rhs to this
      if (rhs.size_ == 0)
        sequence_ = nullptr;
      sequence_ = new std::array<Object, 2>[rhs.size_];
      for (size_t i = 0; i < rhs.size_; ++i)
        sequence_[i] = rhs.sequence_[i];
    }

    // Copy-assignment. If you have already written
    // the copy-constructor and the move-constructor
    // you can just use:
    // {
    // Points2D copy = rhs;
    // std::swap(*this, copy);
    // return *this;
    // }
    Points2D &operator=(const Points2D &rhs)
    {
      //Make a copy of the Points2D and swap it with *this
      Points2D copy = rhs;
      std::swap(*this, copy);
      return *this;
    }

    // Move-constructor.
    Points2D(Points2D &&rhs) : sequence_(std::move(rhs.sequence_)), size_(std::move(rhs.size_))
    {
      //Set the rhs data members to default
      rhs.size_ = 0;
      rhs.sequence_ = nullptr;
    }

    // Move-assignment.
    // Just use std::swap() for all variables.
    Points2D &operator=(Points2D &&rhs)
    {
      //Check to make sure we aren't moving the same thing onto another variable
      if (this != &rhs)
      {
        std::swap(sequence_, rhs.sequence_);
        std::swap(size_, rhs.size_);
      }
      return *this;
    }

    ~Points2D()
    {
      //Free sequence_ memory
      delete[] sequence_;
      //Set sequence_ to nullptr and size_ to 0
      sequence_ = nullptr;
      size_ = 0;
    }

    // End of big-five.

    // One parameter constructor.
    Points2D(const std::array<Object, 2> &item)
    {
      //Create one point
      sequence_ = new std::array<Object, 2>[1];
      size_ = 1;
      sequence_[0] = item;
    }

    // Read a chain from standard input.
    void ReadPoints2D()
    {
      // Part of code included (without error checking).
      std::string input_line;
      std::getline(std::cin, input_line);
      std::stringstream input_stream(input_line);
      if (input_line.empty())
        return;
      // Read size of sequence (an integer).
      int size_of_sequence;
      input_stream >> size_of_sequence;
      // Allocate space for sequence.
      // Add code here.

      //Declare and set the data members
      size_ = size_of_sequence;
      sequence_ = new std::array<Object, 2>[size_of_sequence];

      Object token;
      for (int i = 0; input_stream >> token; ++i)
      {
        // Read coordinates.
        // Fill sequence_ here.
        //The input is read two times, once for x value and once for y value
        sequence_[i][0] = token;
        input_stream >> token;
        sequence_[i][1] = token;
      }
      //Print new line
      std::cout << std::endl;
    }

    size_t size() const
    {
      // Code missing.
      //Accessor method to get size of 2D array
      return size_;
    }

    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2> &operator[](size_t location) const
    {
      // Code missing.
      //Check for out-of-range
      if (location < 0 || location > size_)
        abort();
      //Otherwise return the point at location
      return sequence_[location];
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    friend Points2D operator+(const Points2D &c1, const Points2D &c2)
    {
      // Code missing.
      //Declare the Points2D object to return
      Points2D result;
      //Find the smaller size and bigger size so we can access it later on when we combine the Points2D
      size_t small_of_2 = c1.size_ < c2.size_ ? c1.size_ : c2.size_;
      size_t big_of_2 = c1.size_ > c2.size_ ? c1.size_ : c2.size_;
      //Implement the object data members
      result.sequence_ = new std::array<Object, 2>[big_of_2];
      result.size_ = big_of_2;
      //Loop through the smaller size and take the sum of both points
      for (size_t i = 0; i < small_of_2; i++)
      {
        result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
        result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
      }
      //Add the remaining points from index smallof2 to bigof2-1
      if (c1.size_ < c2.size_)
        for (size_t i = small_of_2; i < big_of_2; i++)
        {
          result.sequence_[i][0] = c2.sequence_[i][0];
          result.sequence_[i][1] = c2.sequence_[i][1];
        }
      else
        for (size_t i = small_of_2; i < big_of_2; i++)
        {
          result.sequence_[i][0] = c1.sequence_[i][0];
          result.sequence_[i][1] = c1.sequence_[i][1];
        }
      return result;
    }

    // Overloading the << operator.
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2)
    {
      //Check if 2D array is empty. If 2D array is empty, return empty parenthesis.
      if (some_points2.size_ == 0)
        out << "()";
      else
        //Return the points in the form (a, b)
        for (size_t i = 0; i < some_points2.size_; i++)
          out << "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ") ";
      //Print new line after done printing the points
      out << std::endl;
      return out;
    }

  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;
    // Size of sequence.
    size_t size_;
  };

} // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2D_H_
