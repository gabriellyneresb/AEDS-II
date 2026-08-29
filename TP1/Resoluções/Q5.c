// Gabrielly Neres

#include <stdio.h>

int soma (int n){
	if(n == 0){
	   return 0;
	}

	return n%10 + soma (n/10);
}


int main(){
	int n = 0;

	while(scanf("%d", &n) == 1){

	printf("%d\n", soma(n));
	
	}
	return 0;
}
