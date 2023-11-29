#include <stdio.h>
#include <assert.h>
#pragma once
class Matrix
{
public:
  static const int filas = 5;
  static const int columnas = 5;
  int nodos= 5;
  FILE *fp;
  int m[filas][columnas];
  void floydWarshall();
  void printMatrix();
  void fillMatrix();
};
void Matrix::fillMatrix(){
  fp = fopen("data.txt", "r");
  int ret = 0;
  if (!fp)
  {
    fprintf(stderr, "No se puede abrir el archivo");
  }
  //assert(fp);
  for (int i = 0; i < filas && ret != EOF; i++)
  {
    for (int j = 0; j < columnas && ret != EOF; j++)
    {
      ret = fscanf(fp, "%d", &m[i][j]);
      if (ret == 0)
      {
        fprintf(stderr, "Error al leer el archivo");
      }
      //assert(ret!=0);      
    }
  }
  fclose(fp);
}
void Matrix::floydWarshall()
{
  for (int k = 0; k < nodos; k++)
  {
    for (int i = 0; i < filas; i++)
    {
      for (int j = 0; j < columnas; j++)
      {
        if( m[i][k] != -2 && m[k][j] != -2 )
        {
          if ( m[i][j] == -2 || m[i][j] > m[i][k] + m[k][j] )
            m[i][j] = m[i][k] + m[k][j];
        }
      }
    }
  }
}
void Matrix::printMatrix()
{
  for (int i = 0; i < filas; i++)
  {
    for (int j = 0; j < columnas; j++)
    {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}