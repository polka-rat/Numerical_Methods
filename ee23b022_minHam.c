/*Roll no: EE23B022
 Name: Deepak Charan S
 Date: 15.9.23
 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


int hammingDistance(int *str1, int *str2, int length) {
    int distance = 0;
    for (int i = 0; i < length; i++) {
        if (str1[i] != str2[i]) {
            distance++;
        }
    }
    return distance;
}

int main(int argc, char* argv[]){
	int n,nseed,m,mseed;
	n=atoi(argv[1]);
	nseed=atoi(argv[2]);
	m=atoi(argv[3]);
	mseed=atoi(argv[4]);
	
	if(m>n){
		printf("Error \n");
		return 1;
	}
	
	int* mptr;
	mptr=(int*)malloc(m*sizeof(int));
	
	int* nptr;
	nptr=(int*)malloc(n*sizeof(int));
	
	FILE * fp1=fopen("Mfile.dat","w");
	srand((unsigned)mseed);
	for(int i=0; i<m;i++){
		mptr[i]=rand()%2;
		fprintf(fp1,"%d ",mptr[i]);
	}
	
	FILE * fp2=fopen("Nfile.dat","w");
	srand((unsigned)nseed);
	for(int i=0; i<n;i++){
		nptr[i]=rand()%2;
		fprintf(fp2,"%d ",nptr[i]);
	}
		
	fclose(fp1);
	fclose(fp2);
	

	int mincount=10000;
	int count=0;
	int k=0;
	int loc;

	for (int i = 0; i <= n - m; i++) {
        int distance = hammingDistance(nptr + i, mptr, m);
        if (distance < mincount) {
            mincount = distance;
            loc = i;
        }
        }
	printf("%d %d\n",mincount,loc);
	
	return 0;
}
