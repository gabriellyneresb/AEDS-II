// Gabrielly Neres

#include <stdio.h>

int vogais(char *palavra, int i){
	int resp = 0;
	//caso base se for vazia ou fim
	if(palavra[i] == '\0'){
		return 1;
	}

	char c = palavra[i];
	//deixar minusculo
	if(c >= 'A' && c <= 'Z'){
		c = c+32;
	}
	//verificar se nao e vogal
	if(c != 'a' && c!= 'e' && c != 'i' && c!= 'o' && c!= 'u'){
		resp = 0;
	}else{
		//se for vogal continua andando na cadeia
		resp = vogais(palavra, i+1);
	}

	return resp;
}

//funcao secundaria recebendo um parametro so
int Vogais(char *palavra){
	int resp = 1;
	if(palavra[0] == '\0'){
		resp = 0;
	}else{
		//chama funcao princpal
		resp = vogais(palavra, 0);
	}
	return resp;
}

int consoantes(char *palavra, int i){
	int resp = 0;
	//caso base se for vazia ou fim
	if(palavra[i] == '\0'){
		return 1;
	}

	//deixar minusculo
	char c = palavra[i];
	if(c >= 'A' && c <= 'Z'){
		c = c+32;
	}
	//se nao for letra e for vogal e falso
	if(!(c >= 'a' && c <= 'z') || (c == 'a' || c == 'e' || c== 'i' || c == 'o' || c == 'u')){
		resp = 0;
	}else{
		resp = consoantes(palavra,i+1);
	}
	return resp;
}

//funcoa com so um parametro
int Consoantes(char *palavra){
	int resp = 1;
	if(palavra[0] == '\0'){
		resp = 0;
	}else{
		//chama a funcao principal
		resp = consoantes(palavra,0);
	}
	return resp;
}

int inteiros(char *numero, int i){
	int resp = 1;
	if(numero[i] == '\0'){
		return 1;
	}
	int cont = 0;
	char c = numero[i];
	//se for sinal na primeira posicao continua 
	if(c == '-' && i == 0 || c == '+' && i == 0){
		resp = inteiros(numero, i+1);
	
	}else if(!(c >= '0' && c <= '9')){
		resp = 0;
	}else{
		resp = inteiros(numero, i+1);
	}

	return resp;
}

//funcao auxiliar com um parametro apenas
int Inteiros(char *numero){
	int resp = 1;

	if(numero[0] == '\0'){
		resp = 0;
	}else{
		resp = inteiros(numero,0);
	}
	return resp;
}

//variavel global para nao reiniciar toda vez que a recursão reinicia
int ponto = 0;

int reais(char *numero, int i){
	int resp = 1;
	//caso base
	if(numero[i] == '\0'){
		return 1;
	}

	char c = numero[i];
	if(c == '-' && i == 0 || c == '+' && i == 0){
		resp = reais(numero, i+1);
	//se for . ou , garantimos que so ocorre uma vez
	}else if(c == '.' || c == ','){
			if(ponto){
				resp = 0;
			}else{
				//se nao tinha antes, marca que já encontrou o ponto
				ponto = 1;
				// e vai pro proximo
				resp = reais(numero,i+1);
			}
	//se nao for num e falso
	}else if(!(c >= '0' && c <= '9')){
		resp = 0;
	}else{
		resp = reais(numero, i+1);
	}

	return resp;
}

int Reais(char *numero){
	int resp = 1;
	ponto = 0;

	if(numero[0] == '\0'){
		resp = 0;
	}else{
		resp = reais(numero,0);
	}
	return resp;
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

	fgets(palavra, 1000, stdin);
	remover(palavra);

	while(strcmp(palavra, "FIM") == 0){
		if(Vogais(palavra) == 1){
			printf("SIM NAO NAO NAO\n");
		}else if(Consoantes(palavra) == 1){
			printf("NAO SIM NAO NAO\n");
		}else if(Inteiros(palavra) == 1){
			printf("NAO NAO SIM SIM\n");
		}else if(Reais(palavra) == 1){
			printf("NAO NAO NAO SIM\n");
		}else{
			printf("NAO NAO NAO NAO\n");
		}

		fgets(palavra,1000,stdin);
		remover(palavra);
	}

	return 0;
}
