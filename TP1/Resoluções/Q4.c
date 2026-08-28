// Gabrielly Neres

#include <stdio.h>

void inverter (char palavra[]){
	int tam = 0;
	while(palavra[tam] != '\0'){
		tam++;
	}
	
	//recebe palavra e printa ao contrario comecando da ultima posicao e indo pra primeiro
	for(int i = tam-1; i >= 0; i--){
		printf("%c", palavra[i]);
	}
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
  char palavra[100];

  fgets(palavra,100,stdin);
  //remove o '\n' do fegets toda vez que le uma palavra
  remover(palavra);

  //enquanto palavra for diferente de FIM inverte e le mais
  while(strcmp(palavra, "FIM") == 0){

	inverter(palavra);
	printf("\n");
	fgets(palavra,100,stdin);
	remover(palavra);
  }
	return 0;
}
