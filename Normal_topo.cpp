//This is to simulate the working of Topoisomerase enzyme which
//removes catenations from DNA which is necessary while replication
//of DNA. 

//Enzymes randomly surround medium of DNA, we pick latice points
//equal to number of points and check if the catenation exists
//and if it does whether it can be removed or not

#include<iostream>
#include<stdlib.h>

using namespace std;

#define N 100	//SSize of latice
#define N_ENZYMES 1		//No. Of enzymes around the latice
#define N_CATS	N/10	//No. of catenations in the latice

int track[N];

void fill_cat(){	//To add randomly placed catenations

	for(int i = 0; i< N_CATS; i++){
		
		int pos = rand()%N;

		if(track[pos] == 1){
			
			i--;
			continue;
		}
		else{

			track[pos] = 1;

		}

	}	

}

void initialize(int a[], int n){	//To make all values of an array zero

	for(int i = 0; i<n; i++){

		a[i] = 0;

	}


}

void work(){	//To simulate a single time step 




}

void print(int a[], int n){		//To display an array

	for(int i = 0; i<n; i++){

		cout<<a[i]<<" ";

	}

	cout<<endl;

}


int main(){

	initialize(track, N);	//To make all entries 0

	fill_cat();	//To insert catenations

	print(track, N);

	return 0;
}