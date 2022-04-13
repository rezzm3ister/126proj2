//alvarez angeles tuyay proj 2
#include <iostream>
#include <chrono>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <pthread.h>

#define matR 10
#define matC 10

//make sure TC_row == matR
#define TC_row 10
//make sure TC_indiv == matR*matC
#define TC_indiv 100


using namespace std;

void matrixmultnothread(double (&matA)[matC][matR],double (&matB)[matC][matR],double (&product)[matC][matR]){
  for(int i=0;i<matR;i++){
    for (int j=0;j<matC;j++){
      for(int k=0;k<matC;k++){
        product[i][j] += matA[i][k] * matB[k][j];
      }
    }
  }
}


void *matrixmultrowthreads(void *threadid, double (&matA)[matC][matR],double (&matB)[matC][matR],double (&product)[matC][matR]){
  int i=(int)threadid;
  for (int j=0;j<matC;j++){
    for(int k=0;k<matC;k++){
      product[i][j] += matA[i][k] * matB[k][j];
    }
  }

}



void showproduct(double (&product)[matC][matR]){
  for (int i = 0; i < matR; i++){
    for(int j = 0; j < matC; j++){
      cout<<product[i][j]<<" ";
    }
    cout<<endl;
  }
}

void showmatrices(double (&matA)[matC][matR],double (&matB)[matC][matR]){
  int r1=matR;
  int r2=matR;
  int c1=matC;
  int c2=matC;
  for (int i = 0; i < r1; i++){
    for(int j = 0; j < c1; j++){
      cout<<matA[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;         
  for (int i = 0; i < r1; i++){
    for(int j = 0; j < c1; j++){
      cout<<matB[i][j]<<" ";
    }
    cout<<endl;
  }
}

int main(){
  double matA[matC][matR],matB[matC][matR], product[matC][matR];
  int r1=matR;
  int r2=matR;
  int c1=matC;
  int c2=matC;
  srand(time(0));
  //matrix fill
  for (int i = 0; i < r1; i++)
    {
      for (int j = 0; j < c1; j++)
      {
        matA[i][j] = rand() % 10;
      }
    }
    for (int i = 0; i < r1; i++){
      for (int j = 0; j < c1; j++){
        matB[i][j] = rand() % 10;
        }
    } 
  //no threads here
  //matrixmultnothread(matA,matB,product);

  //thread per row
  pthread_t trows[TC_row];
  int tcreation;

  for (int i=0;i<TC_row;i++){
    tcreation=pthread_create(&trows[i],NULL,matrixmultrowthreads,(void*)i);
    if(tcreation){
      cout<<"cant make thread "<<tcreation<<endl;
      exit(-1);
    }
  }

  showproduct();

}