#include "Matrix.cpp"
#include <stdio.h>
#include <assert.h>

void test(int nodos);
void readKey();

int main()
{
  test(3);
  test(4);
  test(5);
  readKey();
  return 0;
}

void test(int nodos)
{
  std::string fileName = "./aserciones/" + std::to_string(nodos) + "nodos";
  std::string extension = ".txt";
  Matrix matrix(fileName + extension, nodos);
  matrix.floydWarshall();
  Matrix expected(fileName + "_test" + extension, nodos);
  for (int i = 0; i < nodos; i++)
    for (int j = 0; j < nodos; j++)
    {
      if (matrix.get(i, j) != expected.get(i, j)) 
      {
        std::cout << "Falla en la posición (i: " << i << ", j: " << j << ")" << std::endl;
      }
      assert(matrix.get(i,j) == expected.get(i,j));
    }
  printf(("Test " + std::to_string(nodos) + " finalizado exitosamente.\n").c_str());
}

void readKey()
{
  std::string linea;
  std::getline(std::cin, linea);
}