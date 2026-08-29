//Gabrielly Neres

#include <stdio.h>

int anagrama(char str[], char str1[]){
	
	int resp = 1;
	int tam = 0;
	int tam1= 0;
	
	//pega tam das strings
	while(str[tam] != '\0'){
		tam++;
	}

	while(str1[tam1] != '\0'){
		tam1++;
	}

	if(tam != tam1){
		resp = 0;
	}

	//vetor que vai marcar a frenquancia de cada caracter 
	char freq[256] = {0}; 

	//percorrer a primeira, transforma pra minusculo ignroa espacos
	for(int i = 0; i < tam; i++){
		 char c = str[i];
		//ignora espacos
		if(c == ' '){
			continue;
		}
		//se for maiscula trasnforma p minuscula
		if(c >= 'A' && c <= 'Z'){
			c = c+32;
		}
		//armazena na posicao do codigo ascii
		freq[c]++;
	}

	//faz o mesmo com a segunda
	for(int i = 0; i < tam1; i++){
		char c1 = str1[i];
		if(c1 == ' '){
			continue;
		}
		if(c1 >= 'A' && c1<= 'Z'){
			c1 = c1+32;
		}
		//decrementa pra ver se vai sobrar 0
		freq[c1]--;
	}

	//for pra ver se vai ficar zerado e são iguais se ficar
	for(int i = 0; i<255; i++){
		if(freq[i] != 0){
			resp = 0;
		}
	}

	return resp;
}

//metodo para comparar se duas palavras soa iguais
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


int main (){
    char palavra[100];
    char palavra1[100];

    while(scanf("%s", palavra) == 1 && strcmp(palavra, "FIM") == 0){
    	scanf("%s", palavra1);

    if(anagrama(palavra,palavra1) != 0){
    	printf("SIM\n");
    }else{
    	printf("NAO\n");
    }
   }
	
	return 0;
}
