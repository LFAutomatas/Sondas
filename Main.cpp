#include "Matrix.cpp"

int main()
{
  Matrix max;  
  max.fillMatrix();
  max.printMatrix();
  max.floydWarshall();
  max.printMatrix();
}