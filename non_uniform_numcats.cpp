//This is to simulate the working of Topoisomerase enzyme which
//removes catenations from DNA which is necessary while replication
//of DNA. 

//Enzymes randomly surround medium of DNA, we pick latice points
//equal to number of points and check if the catenation exists
//and if it does whether it can be removed or not

//This is to see the relation of number of catenations remaining to be 
//unsolved vs time.

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<fstream>

using namespace std;

#define N 10000	//SSize of latice
#define MAX_ENZYMES 100		//No. Of enzymes around the latice
#define FORCE 40.0	//Max force applied
#define V_MAX	3.38  //Max number of cycles per second at a given force (s)
#define Km	270 //Michaelis Constant for the enzyme (uM)
#define Kb	1.38	//Boltzmann Constant (10^-23 units)
#define T 300	//Temperature (K)
#define E_PRODUCT	Kb*T //To increase speed
#define TIME_STEP 0.1		//Time step
#define DELTA 0.241	//angie's parameter (pN), 0.835 is parameter of motion
#define T_MAX 30000.0		//Seconds
#define FILE_NAME "time_non-uniform.dat"		//To see where to output data
#define MAX_CATS 100		//Number of catenations to insert initially
#define ATP_MAX 2000	//Maximum ATP till which readings are taken
#define N_RUNS 200		//Number of runs for averaging
#define MAX_FORCE 30	//Maximum force (pN)


int n_cats = N;	//No. of catenations in the latice

int track[N];

float prob;	//Probabability of resolving a catenation
float f_each; 	//Force experienced by each catenation
float f_previous = 0;	//To increase speed
float ATP_conc = ATP_MAX;		//Concentration of ATP
int cats_resolved; //To see cycles per second
int pos;	//To store where the nect catenation is


void calcProb(){	//To update the probability

	f_each = (float)FORCE*(1 - (float)abs(pos - N/2)/N);

	float v = V_MAX*exp(-1*f_each*DELTA)*((float)ATP_conc/(ATP_conc + Km));		//Adjust 100 if order changes

	//cout<<v<<endl;

	prob = v*TIME_STEP;
}


void fill_cat(){	//To add randomly placed catenations

	for(int i = 0; i< MAX_CATS; i++){
		
		int pos = rand()%N;

		if(track[pos] == 1){
			
			i--;
			continue;
		}
		
		else{

			track[pos] = 1;

		}

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

	fill_cat();


}


void work(){	//To simulate a single time step 

	for(int i = 0; i< MAX_ENZYMES; i++){

		calcProb();	//To calculate the probability now

		if(n_cats == 0){
			break;
		}

		pos = rand()%N;

		if(track[pos] == 0){
			continue;
		}

		if(rand1() < prob){
			
			track[pos] = 0;

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

	//Never start from 0

		//cout<<ATP_conc;

		float avg_time[(int)(T_MAX/TIME_STEP) + 1] = {0};

		//cout<<(int)(T_MAX/TIME_STEP)<<endl;

		for(int runs = 0; runs< N_RUNS; runs++){

			int time1; //To see the time elapsed

			initialize(track, N);	//To make all entries 0

			fill_cat();	//To insert catenations


			for(time1 = 0; time1<= T_MAX/TIME_STEP + 1; time1++){

				avg_time[time1] += n_cats;

				if(n_cats == 0){
					break;
				}

				work();

				if(runs == 0){
					cout<<time1<<" "<<n_cats<<endl;
				}


			}


			cout<<runs<<endl;
			//cout<<"ATP conc: "<<ATP_conc<<"Force: "<<f_each<<"Cats: "<<n_cats<<"Runs: "<<runs<<" "<<"%"<<endl;

		}

		for(int i = 0; i<= (int)(T_MAX/TIME_STEP) + 1; i++){

			avg_time[i] /= N_RUNS;

			f1<<i*TIME_STEP<<" "<<avg_time[i]<<endl;

		}

//		f1<<ATP_conc<<" "<<(float)(MAX_CATS-n_cats)/time1<<endl;
//		cout<<"ATP: "<<ATP_conc<<" "<<"Cycles per sec: "<<(float)(MAX_CATS-n_cats)/time1<<endl;
		//cout<<"here";	


	f1.close();

	return 0;
}