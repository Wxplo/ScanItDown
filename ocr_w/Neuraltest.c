#include <stdio.h>
#include <stdlib.h>




void initWeights() {

for(int j = 0; j < numHidden; j++){

	weightsHO[j] = (getRand() - 0.5) / 2;
        for(int i = 0; i < numInputs; i++){

            weightsIH[i][j] = (getRand() - 0.5) / 5;
            
        }
    }

}

int activationIH (int a,int b) {

int activ [];

for(int j = 0; j < numHidden; j++) {
	for(int i = 0; i < numInputs; i++) {
            if ( a*x + b*y >= 1 ) {
		
		}
        }
    }



}

double getRand() {

return double(rand() / double(RAND_MAX));

}



/*
void cases () {

double [] [] input, output;

input = new double[4][]; output = new double[4][]
for ( int i = 0; i < 4; i++) {
		input [i] = new double[2]; output = new double[1];
	}	
input [0] [0] = 0.0; input [0] [1] = 0.0; output [0] [0] = 0.0;
input [1] [0] = 1.0; input [1] [1] = 0.0; output [1] [0] = 1.0;
input [2] [0] = 0.0; input [2] [1] = 1.0; output [2] [0] = 1.0;
input [3] [0] = 1.0; input [3] [1] = 1.0; output [3] [0] = 0.0;

}

void train () {

double error = 0.0;
int max_count = 1000;
int count = 0;
while ( error > 0.0001 && count <= max_count ) {

count++;
error = 0.0;
for ( int i = 0; i < 4; i++) 
}

}


}
*/
int main () {

const int numInputs = 2;
const int numHidden = 4;
double weightsHO[numHidden];
double weightsIH[numInputs][numHidden];


}
