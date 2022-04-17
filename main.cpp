//alvarez angeles tuyay proj 2
/**
*VERY IMPORTANT: make sure to compile with 
*-pthread or -lpthread argument in g++
*/

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

#define matR 50
#define matC 50

//make sure TC_row == matR
#define TC_row 50
//make sure TC_indiv == matR*matC
#define TC_indiv 100

using namespace std;
using namespace std::chrono;

struct coords
{
  int row;
  int col;
};

struct matrices
{
  double matA[matC][matR],matB[matC][matR], product[matC][matR];
  int r1=matR;
  int r2=matR;
  int c1=matC;
  int c2=matC;
  coords loc;
  long unsigned int tids[TC_row];
};

void matrixmultnothread(matrices &compute)
{
  for(int i=0;i<matR;i++)
  {
    for (int j=0;j<matC;j++)
    {
      for(int k=0;k<matC;k++)
      {
        compute.product[i][j] += 
          compute.matA[i][k] * compute.matB[k][j];
      }
    }
  }
}



void *matrixmultrowthreads(void *vars)
{
  matrices *compute=static_cast<matrices*>(vars);
  int i;
  double tempcell[matC];
  long unsigned int tid=gettid();

  for(i=0;i<TC_row;i++)
  {
    if(tid==compute->tids[i])
    {
      break;
    }
  }

  for (int j=0;j<matC;j++)
  {
    for(int k=0;k<matC;k++)
    {
      tempcell[j] += compute->matA[i][k] *compute->matB[k][j];
    }
    compute->product[i][j]=tempcell[j];
  }

  pthread_exit(NULL);
  
}

void *matrixmultthreads(void* vars)
{
  matrices *compute=static_cast<matrices*>(vars);

  for(int k=0;k<matC;k++)
  {
    compute->product[compute->loc.row][compute->loc.col] += 
      compute->matA[compute->loc.row][k]*
      compute->matB[k][compute->loc.col];
  }
  pthread_exit(NULL);
}


//debug to check content
void showproductout(matrices output)
{
  for (int i = 0; i < matR; i++)
  {
    for(int j = 0; j < matC; j++)
    {
      cout<<output.product[i][j]<<" ";
    }
    cout<<endl;
  }
}
//debug to check if working
void showmatrices(matrices &vars)
{
  
  for (int i = 0; i < vars.r1; i++)
  {
    for(int j = 0; j < vars.c1; j++)
    {
      cout<<vars.matA[i][j]<<" ";
    }
    cout<<endl;
  }

  cout<<endl;         
  for (int i = 0; i < vars.r1; i++)
  {
    for(int j = 0; j < vars.c1; j++)
    {
      cout<<vars.matB[i][j]<<" ";
    }
    cout<<endl;
  }
}


void fillmats(matrices &vars)
{
    for (int i = 0; i < vars.r1; i++)
    {
      for (int j = 0; j < vars.c1; j++)
      {
        vars.matA[i][j] = rand() % 10;
      }
    }
    
    for (int i = 0; i < vars.r1; i++)
    {
      for (int j = 0; j < vars.c1; j++)
      {
        vars.matB[i][j] = rand() % 10;
      }
    } 
}

int main()
{
  
  matrices vars; 
  srand(time(0));

  const double dur=5.0;
  long int passes=0;


  fillmats(vars);
  int input=69;
  while(input>3)
  {
    cout<<"matrix size: "<<matR<<"x"<<matC<<"\n";
    cout<<"choose option:\n[1] no threads\n[2] thread per row\n[3] thread per item\n[0] exit\nchoice: ";
    cin>>input;

    if(input==1)
    {
      //no threads here
      for(int i=0;i<10;i++)
      {
        passes=0;
        auto start = high_resolution_clock::now();
        while (duration_cast<seconds>
               (high_resolution_clock::now() - start).count() < dur)
        {
          matrixmultnothread(vars);
          passes++;
        }
        cout<<passes<<endl;
      }
    }

    else if(input==2)
    {
      //thread per row
      pthread_t trows[TC_row];
      for(int i=0;i<TC_row;i++)
        vars.tids[i]=trows[i];

      for(int i=0;i<10;i++)
      {
        passes=0;
        auto start = high_resolution_clock::now();
        
        
        while (duration_cast<seconds>
               (high_resolution_clock::now() - start).count() < dur)
        {
          //fillmats(vars);
          for (int i=0;i<TC_row;i++)
          {
            pthread_create(&trows[i],NULL,
            matrixmultrowthreads,(void*)&vars);
          }
          for (int i=0;i<TC_row;i++)
          {
            pthread_join(trows[i],NULL);
          }
          passes++;
        }
        cout<<passes<<endl;

      }
    }
    else if(input==3)
    {
      
      for(int i=0;i<10;i++)
      {
        passes=0;
        auto start = high_resolution_clock::now();
        
        pthread_t trows[TC_row][TC_row];
        while (duration_cast<seconds>
               (high_resolution_clock::now() - start).count() < dur)
        {
          //fillmats(vars);
          for (int i=0;i<TC_row;i++)
          {
            for (int j=0;j<TC_row;j++)
            {
              vars.loc.col=j;
              vars.loc.row=i;
              pthread_create(&trows[i][j],NULL,
              matrixmultthreads,(void*)&vars);
            }
          }
          for (int i=0;i<TC_row;i++)
          {
            for(int j=0;j<TC_row;j++)
            {
              pthread_join(trows[i][j],NULL);

            }
          }
          passes++;
        }
        cout<<passes<<endl;

      }
    }
    else if(input==0)
    {
      return 0;
    }
    else
    {
      system("CLS");
    }
  }
}
