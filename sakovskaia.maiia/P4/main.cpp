#include <iostream>
#include <fstream>
#include <cstdlib>
#include "matrix.hpp"
#include "matrix_input_res.hpp"

int main(int argc, char * argv[])
{
  using namespace sakovskaia;
  AnswerCounter countanswer;
  if (argc != 4)
  {
    std::cerr << "Error in command line arguments\n";
    return 1;
  }

  int num = 0;
  try
  {
    num = std::stoll(argv[1]);
  }
  catch(const std::invalid_argument & e)
  {
    std::cerr << "Cannot read first argument\n";
    return 1;
  }
  if ((num > 2) || (num < 1))
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  size_t rows = 0, columns = 0;
  input >> rows >> columns;
  if (!input)
  {
    std::cerr << "Error in reading input file\n";
    return 2;
  }

  std::ofstream output(argv[3]);

  int * input_matrix = nullptr;
  int * counterclockwise_matrix = nullptr;
  int * new_dynamic_matrix = nullptr;
  int * new_dynamic_counterclockwise_matrix = nullptr;
  int new_input_matrix[10000] = {};
  int new_counterclockwise_matrix[10000] = {};

  if (num == 1)
  {
    try
    {
      input_matrix = new_input_matrix;
      counterclockwise_matrix = new_counterclockwise_matrix;
    }
    catch (const std::logic_error & e)
    {
      std::cerr << e.what() << "\n";
      input.close();
      output.close();
      return 2;
    }
  }
  else if (num == 2)
  {
    try
    {
      input_matrix = new int[rows * columns];
      counterclockwise_matrix = new int[rows * columns];
      new_dynamic_matrix = input_matrix;
      new_dynamic_counterclockwise_matrix = counterclockwise_matrix;
    }
    catch (const std::logic_error & e)
    {
      std::cerr << e.what() << "\n";
      delete [] input_matrix;
      delete [] counterclockwise_matrix;
      input.close();
      output.close();
      return 2;
    }
  }
  try
  {
    inputMatrix(input, input_matrix, rows * columns);
    countCounterclockwiseMatrix(counterclockwise_matrix, rows, columns);
    countanswer(input_matrix, counterclockwise_matrix, rows * columns);
    output << rows << " " << columns;
    printAnswer(output, counterclockwise_matrix, rows * columns);
    if (num == 2)
    {
      delete [] new_dynamic_matrix;
      delete [] new_dynamic_counterclockwise_matrix;
    }
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << "\n";
    if (num == 2)
    {
      delete [] new_dynamic_matrix;
      delete [] new_dynamic_counterclockwise_matrix;
    }
    input.close();
    output.close();
    return 2;
  }
  input.close();
  output.close();
}