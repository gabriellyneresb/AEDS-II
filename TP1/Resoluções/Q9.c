//Gabrielly Neres 

#include <stdio.h>

char *ciframento (char *palavra){
	if(*palavra == '\0'){
		return palavra;	
	}
	//anda 3 casas a cada chamada 
	*palavra = *palavra +3;
	//vai pra proxima letra
	ciframento(palavra+1);
	//retorna a palavra
	return palavra;
}

//funcao para comparar duas strings se sao iguais
int strcmp(char a[], char b[]){
	int resp = 1;
	int tam1 = 0, tam2 = 0;
	while(a[tam1] != '\0'){
		tam1++;
	}

	while(b[tam2] != '\0'){
		tam2++;
	}

	if(tam1>tam2 || tam1<tam2){
		resp = 0;
	}else{
		for(int i = 0; i<tam1 && i<tam2 ; i++){
			if(a[i] != b[i]){
				resp = 0;
			}
		}
	}
	return resp;
}

//metodo para remover a quebra de linha do fgets e a siada ficar certa
void remover(char palavra[]){
	int tam = 0;
	while(palavra[tam] != '\0'){
		tam++;
	}
	//troca o \n por \0
	if(palavra[tam-1] == '\n'){
		palavra[tam-1] = '\0';
	}
}


int main (){
	char palavra[1000];
	//le e limpa o \n
	fgets(palavra, 1000, stdin);
	remover(palavra);

	while(strcmp(palavra, "FIM") == 0){
	printf("%s", ciframento(palavra));
	printf("\n");
	fgets(palavra, 1000, stdin);
	remover(palavra);
	
	}
	return 0;
}
