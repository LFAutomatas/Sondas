#include "Matrix.cpp"
#include <stdio.h>
#include <assert.h>

void test(int nodos);
void readKey();

int main()
{
  Matrix matrix("data.txt", 5);
  printf("Parte 1:\n\n");
  printf("1) Realice la matriz de adyacencia y calcule la matriz de distancias minimas implementando el algoritmo de FLoyd en Lenguaje C. La implementacion del algoritmo debe ser escalable a k nodos.\n");
  printf("\nRespuesta:\nMatriz adyacencia:\n");
  matrix.printMatrix();
  matrix.floydWarshall();
  matrix.floydWarshall();
  matrix.floydWarshall();
  matrix.floydWarshall();
  matrix.floydWarshall();
  printf("Matriz de distancias minimas:\n");
  matrix.printMatrix();
  printf("\n2) Determine si se pueden realizar conexiones entre todos los nodos, menores a 500 metros, pasando por nodos intermedios.\n");
  printf("\nRespuesta: \nEn el grafo /Sondas/primera-parte/doc/grafo.png se observa que se puede ir de 1 a 2 en 300m, de 2 a 4 en 420m y de 4 a 5 en 150m. Por lo tanto si es posible realizar conexciones.\n");
  printf("\n3) Implemente una serie de aserciones para verificar la correctitud del código.\n");
  printf("\nRespuesta:\nTest unitarios:\n");
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