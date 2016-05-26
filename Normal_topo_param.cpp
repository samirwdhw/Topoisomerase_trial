//This is to simulate the working of Topoisomerase enzyme which
//removes catenations from DNA which is necessary while replication
//of DNA. 

//Enzymes randomly surround medium of DNA, we pick latice points
//equal to number of points and check if the catenation exists
//and if it does whether it can be removed or not

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<fstream>

using namespace std;

#define N 30000	//SSize of latice
#define N_ENZYMES 1		//No. Of enzymes around the latice
#define FORCE 3.0		//Force applied on the strand (pN)
#define V_MAX	3.38  //Max number of cycles per second at a given force (s)
#define Km	270 //Michaelis Constant for the enzyme (uM)
#define Kb	1.38	//Boltzmann Constant (10^-23 units)
#define T 300	//Temperature (K)
#define E_PRODUCT	Kb*T //To increase speed
#define TIME_STEP 0.1		//Time step
#define DELTA 0.241	//angie's parameter (pN), 0.835 is parameter of motion
#define T_MAX 200000		//Seconds
#define FILE_NAME "results_v_pre3.dat"		//To see where to output data
#define MAX_CATS N		//Number of catenations to insert initially
#define ATP_MAX 3000	//Maximum ATP till which readings are taken
#define N_RUNS 200		//Number of runs for averaging

int n_cats = N;	//No. of catenations in the latice

int track[N];

float prob;	//Probabability of resolving a catenation
float f_each; 	//Force experienced by each catenation
float f_previous = 0;	//To increase speed
float ATP_conc;		//Concentration of ATP
int cats_resolved; //To see cycles per second
int pos;	//To store where the nect catenation is


void calcProb(){	//To update the probability

	f_each = FORCE;

	float v = V_MAX*exp(-1*f_each*DELTA)*((float)ATP_conc/(ATP_conc + Km));		//Adjust 100 if order changes

	prob = v*TIME_STEP;
}


void fill_cat(){	//To add randomly placed catenations

	for(int i = 0; i< MAX_CATS; i++){
			
		track[i] = 1;

	}	

	n_cats = MAX_CATS;
	pos = 0;

}

float rand1(){		//To generate values b/w 0,1

	float val = (float)rand()/(RAND_MAX);

	return val;
}

void initialize(int a[], int n){	//To make all values of an array zero

	for(int i = 0; i<n; i++){

		a[i] = 0;

	}


}

void work(){	//To simulate a single time step 

	for(int i = 0; i< N_ENZYMES; i++){

		calcProb();	//To calculate the probability now

		if(rand1() < prob){
/*			
			track[pos] = 0;
			pos++;
*/
			n_cats--;

		}


	}


}

void print(int a[], int n){		//To display an array

	for(int i = 0; i<n; i++){

		cout<<a[i]<<" ";

	}

	cout<<endl;

}


int main(){

	ofstream f1;	//To output data

	f1.open(FILE_NAME);	

	//print(track, N);

	//cout<<"here1";

	for(ATP_conc = 0; ATP_conc<= ATP_MAX; ATP_conc += ATP_MAX/100){

		//cout<<ATP_conc;

		float avg_cycles = 0;

		for(int runs = 0; runs< N_RUNS; runs++){

			float time1; //To see the time elapsed

			initialize(track, N);	//To make all entries 0

			fill_cat();	//To insert catenations


			for(time1 = 0; time1< T_MAX; time1 += TIME_STEP){

				if(n_cats == 0){
					break;
				}

				work();
/*
				if(runs == 0 && ATP_conc == 1650){	
					
					if((time1>T_MAX/4 && time1 <T_MAX/4 +TIME_STEP)|| (time1>T_MAX/2 && time1 <T_MAX/2 + TIME_STEP) || (time1>3*T_MAX/4 && time1 <3*T_MAX/4 + TIME_STEP) || (time1<T_MAX && time1 >T_MAX - TIME_STEP)){

						cout<<"time: "<<time1<<"solved: "<<MAX_CATS-n_cats<<endl;

					}
				}
*/
			}

//			cout<<"\t: "<<(float)(MAX_CATS-n_cats)/time1<<endl;

			avg_cycles += (float)(MAX_CATS-n_cats)/time1;

		}

		avg_cycles /= N_RUNS;

		f1<<ATP_conc<<" "<<avg_cycles<<endl;
		cout<<"ATP: "<<ATP_conc<<" "<<"Cycles per sec: "<<avg_cycles<<endl;
//		f1<<ATP_conc<<" "<<(float)(MAX_CATS-n_cats)/time1<<endl;
//		cout<<"ATP: "<<ATP_conc<<" "<<"Cycles per sec: "<<(float)(MAX_CATS-n_cats)/time1<<endl;
		//cout<<"here";
	}	


	f1.close();

	return 0;
}