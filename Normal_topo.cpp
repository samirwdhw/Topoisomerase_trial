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

#define N 100	//SSize of latice
#define N_ENZYMES 1		//No. Of enzymes around the latice
#define FORCE 1.0		//Force applied on the strand (pN)
#define V_MAX	1.5  //Max number of cycles per second at a given force (s)
#define Km	280 //Michaelis Constant for the enzyme (uM)
#define Kb	1.38	//Boltzmann Constant (10^-23 units)
#define T 300	//Temperature (K)
#define E_PRODUCT	Kb*T //To increase speed
#define TIME_STEP 0.1		//Time step
#define DELTA 1.0	//F*Delta (nm)
#define T_MAX 10000		//Seconds
#define FILE_NAME "results.dat"		//To see where to output data
#define MAX_CATS 10.0		//Number of catenations to insert initially
#define ATP_MAX 3000	//Maximum ATP till which readings are taken
#define N_RUNS 100		//Number of runs for averaging

int n_cats = N/10;	//No. of catenations in the latice

int track[N];

float prob;	//Probabability of resolving a catenation
float f_each; 	//Force experienced by each catenation
float f_previous = 0;	//To increase speed
float ATP_conc;		//Concentration of ATP
int cats_resolved; //To see cycles per second

void calcProb(){	//To update the probability

	f_each = FORCE/n_cats;

/*
	if(f_each == f_previous){
		
		return;
	
	}
*/

	float v = V_MAX*exp(-1*f_each*DELTA*100/(E_PRODUCT))*((float)ATP_conc/(ATP_conc + Km));		//Adjust 100 if order changes

	//cout<<v<<" "<<endl;

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

		int pos = rand()%N;

		calcProb();	//To calculate the probability now

		if(track[pos] == 0){
			
			//cout<<1;
			continue;
		}

		else{

			if( rand1() < prob){

				track[pos] = 0;
				n_cats--;

				//cout<<1<<" ";

			}

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

	initialize(track, N);	//To make all entries 0

	//print(track, N);

	for(ATP_conc = 0; ATP_conc<	ATP_MAX; ATP_conc += ATP_MAX/100){

		float avg_cycles = 0;

		for(int runs = 0; runs< N_RUNS; runs++){

			float time1; //To see the time elapsed

			fill_cat();	//To insert catenations

			for(time1 = 0; time1< T_MAX; time1 += TIME_STEP){
				
				if(n_cats == 0){
					break;
				}

				//cout<<time1<<" "<<prob<<endl;;

				work();

			}

			avg_cycles += (float)(MAX_CATS-n_cats)/time1;

		}

		avg_cycles /= N_RUNS;

		f1<<ATP_conc<<" "<<avg_cycles<<endl;
		cout<<"ATP: "<<ATP_conc<<" "<<"Cycles per sec: "<<avg_cycles<<endl;

	}


	f1.close();

	return 0;
}