//alvarez angeles tuyay proj 2
#include <iostream>
#include <chrono>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define matR 10
#define matC 10

//make sure TC_row == matR
#define TC_row 10
//make sure TC_indiv == matR*matC
#define TC_indiv 100

using namespace std;

struct matrices{
  double matA[matC][matR],matB[matC][matR], product[matC][matR];
  int r1=matR;
  int r2=matR;
  int c1=matC;
  int c2=matC;
  int threadid;
};



void matrixmultnothread(matrices &compute){
  for(int i=0;i<matR;i++){
    for (int j=0;j<matC;j++){
      for(int k=0;k<matC;k++){
        compute.product[i][j] += compute.matA[i][k] * compute.matB[k][j];
      }
    }
  }
}


void *matrixmultrowthreads(void *vars){
  matrices *compute=static_cast<matrices*>(vars);
  cout<<syscall(SYS_gettid)<<"penis"<<endl;

  for (int j=0;j<matC;j++){
    for(int k=0;k<matC;k++){
      compute->product[compute->threadid][j] += compute->matA[compute->threadid][k] *compute->matB[k][j];
    }
  }
  pthread_exit(NULL);
}


void showproductout(matrices output){
  for (int i = 0; i < matR; i++){
    for(int j = 0; j < matC; j++){
      cout<<output.product[i][j]<<" ";
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
  /* moved to struct
  double matA[matC][matR],matB[matC][matR], product[matC][matR];
  int r1=matR;
  int r2=matR;
  int c1=matC;
  int c2=matC;
  */
  matrices vars; 
  srand(time(0));
  //matrix fill
  for (int i = 0; i < vars.r1; i++)
    {
      for (int j = 0; j < vars.c1; j++)
      {
        vars.matA[i][j] = rand() % 10;
      }
    }
    for (int i = 0; i < vars.r1; i++){
      for (int j = 0; j < vars.c1; j++){
        vars.matB[i][j] = rand() % 10;
        }
    } 
  //no threads here
  matrixmultnothread(vars);

  //thread per row
  
  pthread_t trows[TC_row];
  int tcreation;

  for (int i=0;i<TC_row;i++){
    vars.threadid=i;
    tcreation=pthread_create(&trows[i],NULL,matrixmultrowthreads,(void*)&vars);
    if(tcreation){
      cout<<"cant make thread "<<tcreation<<endl;
      exit(-1);
    }
  }
   for (int i=0;i<TC_row;i++){
    pthread_join(trows[i],NULL);
    }
    //showproductout(vars);
}
