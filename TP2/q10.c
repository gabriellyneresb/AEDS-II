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

//fila mais metodos dela
#define MAX 5

typedef struct{
    veiculos v[MAX+1];//max mais 1 pela fila circular que sempre tem um elemento a mais
    int primeiro;
    int ultimo;
}Fila;

Fila fila;

void iniciar(){

    fila.primeiro = 0;
    fila.ultimo = 0;
}

bool ischeia(){
    return ((fila.ultimo + 1) % (MAX+1)) == fila.primeiro;
}

void inserir(veiculos x){
    fila.v[fila.ultimo] = x;
    fila.ultimo = (fila.ultimo + 1) % (MAX+1);
}

veiculos remover(){
	//encerra o prog pq esta vazio 
    if(fila.primeiro == fila.ultimo){
        exit(1);
    }
    veiculos resp = fila.v[fila.primeiro];
    fila.primeiro = (fila.primeiro + 1) % (MAX+1);

    return resp;
}

void mostrar(){
    int i = fila.primeiro;

    while(i != fila.ultimo){
        char buffer[1000];
        formatVeiculos(buffer, fila.v[i]);
        printf("%s\n", buffer);
        i = (i + 1) % (MAX+1);
    }
}

int main(){

    veiculos v[1000];
    int tamanho = LerCsv(v);

    iniciar();

    int id;
    scanf("%d", &id);

   //parte 1 ler os ids
    while(id != -1){
        veiculos veiculo;
        bool achou = false;

        for(int j = 0; j < tamanho && !achou; j++){
            if(v[j].id == id){
                veiculo = v[j];
                achou = true;
            }
        }
//parte 2 realizar as ops e printar
        if(achou){
            if(ischeia()){
                veiculos removido = remover();
                printf("(R)%s %s\n", removido.marca, removido.modelo);
            }
            inserir(veiculo);
        }

        scanf("%d", &id);
    }
    int quantidade = 0;
    scanf("%d", &quantidade);

    char comando[5];

    for(int i = 0; i < quantidade; i++){

        scanf("%s", comando);

        if(strcmp(comando, "I") == 0){
            scanf("%d", &id);
            veiculos veiculo;
            bool achou = false;

            for(int j = 0; j < tamanho && !achou; j++){
                if(v[j].id == id){
                    veiculo = v[j];
                    achou = true;
                }
            }

            if(achou){
                if(ischeia()){
                    veiculos removido = remover();
                    printf("(R)%s %s\n", removido.marca, removido.modelo);
                }
                inserir(veiculo);
            }

        }else if(strcmp(comando, "R") == 0){
            veiculos removido = remover();
            printf("(R)%s %s\n", removido.marca, removido.modelo);
        }
    }

    mostrar();

    return 0;
}
