#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int page_frame[6][2];
	int i=0, j=0;
	for(i=0; i<6; i++){
		for(j=0; j<2; j++) page_frame[i][j]=-1;
	}

	int frame_list[16];
	for(i=0; i<16; i++) frame_list[i]=0;
	int x;
	srand(time(NULL));
	for(i=0; i<6; i++){
		x = rand()%16;
		while(frame_list[x]!=0) x = rand()%16;
		frame_list[x]=1;
		page_frame[i][0]=i%3;
		page_frame[i][1]=x;
	}

	printf("process0's page_table is:\n");
	printf("Page\tFrame\n");
	printf("%d\t%d\n",page_frame[0][0],page_frame[0][1]);
	printf("%d\t%d\n",page_frame[1][0],page_frame[1][1]);
	printf("%d\t%d\n",page_frame[2][0],page_frame[2][1]);

	printf("\nprocess1's page_table is:\n");
	printf("Page\tFrame\n");
	printf("%d\t%d\n",page_frame[3][0],page_frame[3][1]);
	printf("%d\t%d\n",page_frame[4][0],page_frame[4][1]);
	printf("%d\t%d\n",page_frame[5][0],page_frame[5][1]);

	printf("\nprocess0's logical memory is:\n");
	printf("page\tdata\n");
	printf("0\tab\n");
	printf("1\tef\n");
	printf("2\tcd\n");

	printf("\nprocess1's logical memory is:\n");
	printf("page\tdata\n");
	printf("0\trx\n");
	printf("1\tyy\n");
	printf("2\tzz\n");


	char data[12] = {'a','b','e','f','c','d','r','x','y','y','z','z'};

	char physical_memory[32];
	for(i=0; i<32; i++) physical_memory[i]='-';
	for(i=0; i<6; i++){
		x = page_frame[i][1];
		// printf("%d\n", x);
		physical_memory[x*2] = data[i*2];
		physical_memory[x*2+1] = data[i*2+1];
	}
	printf("\nphysical memory\n");
	printf("frame\toffset\tdata\n");
	for(i=0; i<16; i++){
		for(j=0; j<2; j++) printf("%d\t%d\t%c\n",i,j,physical_memory[i*2+j]);
	}
	printf("Freeframelist is:");
	for(i=0; i<16; i++){
		if(frame_list[i]==0) printf("%d ",i);
	}
	printf("\n");
	return 0;
}
