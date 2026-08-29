// Gabrielly Neres


#include <stdio.h>

int maior(char *palavra){
	//pegar tamanho da palavra
	int tam = 0;
	while(palavra[tam] != '\0'){
		tam++;
	}

	int comeco = 0, totalAtual = 0, total = 0;
	
	//for para ir expadindo a substring ate encontrar rep 
	for(int fim = 0; fim < tam; fim++){
		
		int rep = 0;
		//for que verifica repeticos na substring
		for(int i = comeco; i < fim; i++){
		
			if(!rep && palavra[i] == palavra[fim]){
				//se encontra repeticao atualiza o comeco da nova substring
				comeco = i+1;
				//marca que encontrou
				rep = 1;
			}
		}
		//quantidade de caracteres da substring atual
		totalAtual = fim-comeco+1;

		//atualizando valor da maior
		if(totalAtual > total){
			total = totalAtual;
		}
	}
	return total;
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


int main(){

	char palavra[1000];

	//sempre tira o \n depos da leitura, pq string com palavras com um espaco da um \n a mais
	fgets(palavra,1000, stdin);
	remover(palavra);

	while(strcmp(palavra, "FIM") == 0){
	printf("%d", maior(palavra));

	printf("\n");

	fgets(palavra,1000,stdin);
	remover(palavra);
	}

	return 0;
}
