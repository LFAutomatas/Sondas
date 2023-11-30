#include <stdio.h>
#include <iostream>
#include <string>

class Matrix
{
public:
  static const int mem = 10;
  int nodos;
  FILE *fp;
  std::string fileName;
  int m[mem][mem];

  void floydWarshall();
  void printMatrix();
  void fillMatrix();
  void setFileName(std::string aFileName);
  int get(int x, int y);

  Matrix(std::string aFileName, int nodes)
  {
    fileName = aFileName;
    nodos = nodes;
    fillMatrix();
  }
  
  Matrix()
  {
    nodos = 5;
    fileName = "data.txt";
    fillMatrix();
  }

};

int Matrix::get(int x, int y)
{
  return m[x][y];
}

void Matrix::setFileName(std::string aFileName)
{
  fileName = aFileName;
}

void Matrix::fillMatrix(){
  fp = fopen(fileName.c_str(), "r");
  int ret = 0;
  if (!fp)
  {
    fprintf(stderr, "No se puede abrir el archivo");
  }
  //assert(fp);
  for (int i = 0; i < nodos && ret != EOF; i++)
  {
    for (int j = 0; j < nodos && ret != EOF; j++)
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
    for (int i = 0; i < nodos; i++)
    {
      for (int j = 0; j < nodos; j++)
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
  for (int i = 0; i < nodos; i++)
  {
    for (int j = 0; j < nodos; j++)
    {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}