//alvarez angeles tuyay proj 2
#include <iostream>
#include <chrono>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>

#define matX 10
#define matY 10


using namespace std;

void matrixmultnothread(int &matA[matX][matY[],int &matB[matX][matY[]){
  
}


int main(){
  int matA[matX][matY],matB[matX][matY];
  int r1=matY;
  int r2=matY;
  int c1=matX;
  int c2=matX;

  for (int i = 0; i < r1; i++)
    for (int j = 0; j < c1; j++)
      matA[i][j] = rand() % 100;
           
    for (int i = 0; i < r1; i++)
      for (int j = 0; j < c1; j++)
        matB[i][j] = rand() % 100;

    //display matrices:
    /*
    for (int i = 0; i < r1; i++){
      for(int j = 0; j < c1; j++)
        printf("%d ",matA[i][j]);
      printf("\n");
    }
    cout<<endl;         
    for (int i = 0; i < r2; i++){
      for(int j = 0; j < c2; j++)
        printf("%d ",matB[i][j]);
      printf("\n");   
    }
    */

}