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
#include <algorithm>
#include <string>

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
  vector<int> threadids;
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
  int i=69;
  int tid=gettid();

  /*
  std::vector<int>::iterator it=find(compute->threadids.begin(),compute->threadids.end(),tid);
  if(it!=compute->threadids.end()){
    i=distance(compute->threadids.begin(),it);
  }
  else{
    compute->threadids.push_back(tid);
  } 

  
  }
  */
  compute->threadids.push_back(tid);

  for(int j=0;j<compute->threadids.size();j++){
    if(compute->threadids[j]==tid){
      i=j;
    }
  }
  if(i!=69){
  for (int j=0;j<matC;j++){
    for(int k=0;k<matC;k++){
      compute->product[i][j] += compute->matA[i][k] *compute->matB[k][j];
    }
  }
  cout<<i<<endl;

  pthread_exit(NULL);
  }
}



void showproductout(matrices output){
  for (int i = 0; i < matR; i++){
    for(int j = 0; j < matC; j++){
      cout<<output.product[i][j]<<" ";
    }
    cout<<endl;
  }
}

void showmatrices(matrices &vars){
  
  for (int i = 0; i < vars.r1; i++){
    for(int j = 0; j < vars.c1; j++){
      cout<<vars.matA[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;         
  for (int i = 0; i < vars.r1; i++){
    for(int j = 0; j < vars.c1; j++){
      cout<<vars.matB[i][j]<<" ";
    }
    cout<<endl;
  }
}


void fillmats(matrices &vars){
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
}

int main(){
  
  matrices vars; 
  srand(time(0));
  int input=69;
  while(input>3){
    cout<<"choose option:\n[1] no threads\n[2] thread per row\n[3] thread per item\nchoice: ";
    cin>>input;

    if(input==1){
      //no threads here
      fillmats(vars);
      matrixmultnothread(vars);
    }
    else if(input==2){
      fillmats(vars);
      //thread per row
      pthread_t trows[TC_row];
      int tcreation;

      for (int i=0;i<TC_row;i++){
        //vars.threadid=i;
        tcreation=pthread_create(&trows[i],NULL,matrixmultrowthreads,(void*)&vars);
        //cout<<i<<endl;
        if(tcreation){
          cout<<"cant make thread "<<tcreation<<endl;
          exit(-1);
        }
      }
      for (int i=0;i<TC_row;i++){
        pthread_join(trows[i],NULL);
      }
    }
    else if(input==3){
      
    }
    else if(input==0){

    }
    else{
      system("CLS");
    }
    //showmatrices(vars);
    showproductout(vars);

  }
  

  
}
