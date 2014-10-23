#include <stdio.h>
#include <stdlib.h>

double xor ( double a, double  b) {

struct neuron {   /* struct of each neuron */

int threshold;

double weight [2];

double output;

};

struct neuron neural [3];


for ( int i = 0 ; i < 3; i++) {
	if (i == 0) {
		struct neuron neuron1 = {.threshold = 1, .weight[0] = 0.6, .output = 0};
		neural [i] = neuron1;
	}
	if (i == 1) {
		struct neuron neuron2 = {.threshold = 1, .weight[0] =1.1, .output = 0};
        	neural [i] = neuron2;
        }
	if (i == 2) {
		struct neuron neuron3 = {.threshold = 1, .weight[0] =-2, .weight[1] =1.1, .output = 0};
        	neural[i] = neuron3;
        }
}

/* AND GATE */
if ( neural[0].weight[0]*a + b*neural[0].weight[0] >= neural[0].threshold ) {
	neural[0].output = 1;
	}
/* OR GATE */
if ( neural[1].weight[0]*a + b*neural[1].weight[0] >= neural[1].threshold ) {
        neural[1].output = 1;
	}
/* XOR GATE */
if ( neural[2].weight[0]*neural[0].output + neural[1].output*neural[2].weight[1] >= neural[2].threshold ) {
        neural[2].output = 1;
	}
return neural[2].output;
}


int main () {

int a, b;

printf("\nXOR DEMO\nEnter the first input ( 0 or 1 )");
scanf("%d", &a);
printf("\nEnter the second input ( 0 or 1 )");
scanf("%d", &b);
printf("\n%d xor %d = %f\n",a ,b , xor(a,b));

return 0;
}
