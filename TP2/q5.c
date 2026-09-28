#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	int dia;
	int mes;
	int ano;
}Data;

Data parseData(char *s){
	Data d;
	// corta a cadeia ate encontarr -
	char *c = strtok(s, "-");
	d.ano = atoi(c);

	// pega de novo de onde parou ate encontrar outro -
	c = strtok(NULL, "-");
	d.mes = atoi(c);

	//repete e retrona a data convertida pro tipo int
	c = strtok(NULL, "-");
	d.dia = atoi(c);

	return d;
}

//format na string pra el ficar no formato certo de data 
//buffer pra receber o valor da data
void formatData(Data d, char* buffer ){
	 sprintf(buffer, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

typedef struct{
	int id;
	char marca[50];
	char modelo[100];
	int ano;
	char categoria[50];
	char combustivel[30][30];
	int quantidade_combustivel;
	int cilindros;
	double cilindradas;
	char transmissao[50];
	char tracao[50];
	double consumo_cidade;
	double consumo_estrada;
	double co2;
	bool turbo;
	Data data_registro;
}veiculos;

//trasforma os objetos em seus tipos primitivos com atois
veiculos parseVeiculos(char *linha){
	veiculos v;
	
	char *c = strtok(linha, ",");
	v.id = atoi(c);

	c = strtok(NULL, ",");
	sscanf(c, "%49[^\n]", v.marca);

	c = strtok(NULL, ",");
	sscanf(c, "%99[^\n]", v.modelo);

	c = strtok(NULL, ",");
	v.ano = atoi(c);

	c = strtok(NULL, ",");
	sscanf(c, "%49[^\n]" ,v.categoria);

 	c = strtok(NULL, ",");
	//para transformar a funcoa combustivel ja que pode ter 2 palavras separadas por ;
	v.quantidade_combustivel = 0;
	
	int i = 0, j = 0;

	while(c[i] != '\0'){
		//se for , ele anda pra posição do próximo combustivel e zera j
		if(c[i] == ';'){
			//coloca \o pra identificar o fim da primeira palavra
			v.combustivel[v.quantidade_combustivel][j] = '\0';
			v.quantidade_combustivel++;
			j = 0;
		//senao vai inserindo letra por letra do combustivel
		}else{
			v.combustivel[v.quantidade_combustivel][j] = c[i];
			j++;
		}
		i++;
	}

	//coloca \0 no final do iltimo combustivel delimitar o fim
	v.combustivel[v.quantidade_combustivel][j] = '\0';
	v.quantidade_combustivel++;

	c = strtok(NULL, ",");
	v.cilindros = atoi(c);

	c = strtok(NULL, ",");
	v.cilindradas = atof(c);

	c = strtok(NULL, ",");
	sscanf(c, "%49[^\n]",v.transmissao);

	c = strtok(NULL, ",");
	sscanf(c, "%49[^\n]" ,v.tracao);

	c = strtok(NULL, ",");
	v.consumo_cidade = atof(c);

	c = strtok(NULL, ",");
	v.consumo_estrada = atof(c);

 	c = strtok(NULL, ",");	
	v.co2 = atof(c);

	c = strtok(NULL, ",");
	v.turbo = (strcmp( c, "true")==0);

	c = strtok(NULL, ",");
	v.data_registro = parseData(c);

	return v;
}
//formatar os dados de veiculos
void formatVeiculos(char *buffer, veiculos v){
	//teto da data
	char dataTexto[15];
	formatData(v.data_registro, dataTexto);
	
	//montar o texto do combustivel em uma string so 
	char texto_comb[100] = "";
	int pos = 0;
	//for percorre cada cadeia dentro da string
	for(int i = 0; i < v.quantidade_combustivel; i++){
		//adiciona o ; se já tiver adicionado a primeira palavra
		if(i > 0){
			texto_comb[pos] = ',';
			pos++;
		}
		int j = 0;
		//adiciona o novo combustivel se tiver
		while(v.combustivel[i][j] != '\0'){
			texto_comb[pos] = v.combustivel[i][j];
			pos++;
			j++;
		}
	}
		texto_comb[pos] = '\0';
	

	sprintf(buffer, "[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %s ## %s]", 
	v.id, v.marca, v.modelo, v.ano, v.categoria, texto_comb,
        v.cilindros, v.cilindradas, v.transmissao, v.tracao,
        v.consumo_cidade, v.consumo_estrada, v.co2, v.turbo ? "true":"false", dataTexto);
}

int LerCsv(veiculos v[]){
	FILE* arquivo;
	char linha[1000];
	int quantidade = 0;

	//abre o arquivo
	arquivo = fopen("/tmp/veiculos.csv", "r");

	if(arquivo == NULL){
		return 0;
	}

	//pular cabecalho
	fgets(linha, sizeof(linha), arquivo);
	//compoe o vetor e conta a quantidade de linhas do arquivo
	while(fgets(linha, sizeof(linha), arquivo) != NULL){
		v[quantidade] = parseVeiculos(linha);
		quantidade++;
	}	
	fclose(arquivo);
	return quantidade;
}

void coutingSort(veiculos v[], int quantidade){
	int maior = v[0].cilindros;

	for(int i = 0; i < quantidade; i++){
		if(v[i].cilindros > maior){
			maior = v[i].cilindros;
		}
	}

	int contagem[maior+1];
	//cria o vetor de contagem
	for(int i = 0; i <= maior; i++){
		contagem[i] = 0;
	}

	// conta a frequencia do maior valor
	for(int i = 0; i < quantidade; i++){
		contagem[v[i].cilindros]++;
	}	

	//soma o valor com todos menores que ele 
	for(int i = 1; i <= maior; i++){
		contagem[i]=contagem[i]+contagem[i-1]; 
	}

	veiculos ordenado[quantidade];

	//monta o vet
	for(int i = quantidade-1; i >= 0; i--){
		ordenado[contagem[v[i].cilindros]-1] = v[i];
		contagem[v[i].cilindros]--; 
	}

	for(int i = 0; i < quantidade; i++){
		v[i] = ordenado[i];
	}
}

int main(){
	veiculos v[1000];
	int quantidade = LerCsv(v);

	int id;

	scanf("%d", &id);

	int quantidade_ve = 0;
	veiculos ve[1000];

	while(id != -1){

		for(int i = 0; i < quantidade; i++){
			if(v[i].id == id){
				ve[quantidade_ve] = v[i];
				quantidade_ve++;
			}
		}
		scanf("%d", &id);
	}

	coutingSort(ve, quantidade_ve);

	for(int i = 0; i < quantidade_ve; i++){
		char buffer[1000];
		formatVeiculos(buffer,ve[i]);
		printf("%s\n", buffer);
	}
return 0;
}
