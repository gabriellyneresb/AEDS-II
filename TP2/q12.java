import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class q12{

	static class Data{
		private int dia;
		private int mes;
		private int ano;
	
		public Data (int dia, int mes, int ano){
			this.dia = dia;
			this.mes = mes;
			this.ano = ano;
		}

		public int getdia(){
			return dia;
		}

		public int getmes(){
			return mes;
		}

		public int getano(){
			return ano;
		}

		//convertendo os valores para os objjetos
		public static Data parseData(String s){
			String[]c = s.split("-");
			//integer na ordem da data Br
			return new Data(Integer.parseInt(c[2]),
					Integer.parseInt(c[1]),
					Integer.parseInt(c[0])
					);
		}
		//formata os valores para o formarto de data 
		public String format(){
			return String.format("%02d/%02d/%04d", dia, mes, ano);
		}
	}

	static class veiculos{
		private int id;
		private String marca;
		private String modelo;
		private int ano;
		private String categoria;
		private String[] combustivel;
		private int cilindros;
		private double cilindradas;
		private String transmissao;
		private String tracao;
		private double consumo_cidade;
		private double consumo_estrada;
		private double co2;
		private boolean turbo;
		private Data data_registro;
	
		public veiculos(int id, String marca, String modelo, int ano, String categoria, String[] combustivel, 
				int cilindros, double cilindradas, String transmissao, String tracao, double consumo_cidade,
			        double consumo_estrada, double co2, boolean turbo, Data data_registro){
				this.id = id;
				this.marca = marca;
				this.modelo = modelo;
				this.ano = ano;
				this.categoria = categoria;
				this.combustivel = combustivel;
				this.cilindros = cilindros;
				this.cilindradas = cilindradas;
				this.transmissao = transmissao;
				this.tracao = tracao;
				this.consumo_cidade = consumo_cidade;
				this.consumo_estrada = consumo_estrada;
				this.co2 = co2;
				this.turbo = turbo;
				this.data_registro = data_registro;
		}

		public int getid(){
			return id;
		}

		public String getmarca(){
			return marca;
		}

		public String getmodelo(){
			return modelo;
		}

		public int getano(){
			return ano;
		}

		public String getcategoria(){
			return categoria;
		}

		public String[] getcombustivel(){
			return combustivel;
		}

		public int getcilindros(){
			return cilindros;
		}

		public double getcilindradas(){
			return cilindradas;
		}

		public String gettransmissao(){
			return transmissao;
		}

		public String gettracao(){
			return tracao;
		}

		public double getconsumo_cidade(){
			return consumo_cidade;
		}

		public double getconsumo_estrada(){
			return consumo_estrada;
		}

		public double getco2(){
			return co2;
		}

		public boolean getturbo(){
			return turbo;
		}

		public Data getdata_registro(){
			return data_registro;
		}

		//transformar os dados para objetos
		public static veiculos parse_veiculos(String s){
			String[] c = s.split(",");	
			//converte os nums para seus respectivos valores e combustivel convete com split pq pode receber dois valores
			return new veiculos(Integer.parseInt(c[0]), c[1], c[2], Integer.parseInt(c[3]), c[4], c[5].split(";"), Integer.parseInt(c[6]),
			Double.parseDouble(c[7]), c[8], c[9], Double.parseDouble(c[10]), Double.parseDouble(c[11]), Double.parseDouble(c[12]), 
			Boolean.parseBoolean(c[13]), Data.parseData(c[14]));
		}
		//formata o texto 
		public String format(){
			//formarando a string combustivel separada pq ela pode pissuir mais de 1 valor
			String texto_comb = "";
			//percorre cada palavra e adiciona na nova cadeia
			for(int i = 0; i < combustivel.length; i++){
				texto_comb += combustivel[i];
				//verifica se nao chegou ao fim para nao correr risco de colocar ';' no final
				if (i < combustivel.length - 1){
					texto_comb+= ",";
				}
			}

			return String.format("[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %b ## %s]",
					id, marca, modelo, ano, categoria, texto_comb, cilindros, cilindradas, transmissao, tracao, consumo_cidade,
					consumo_estrada, co2, turbo, data_registro.format());
		}

	}

	static class LerCsv{
		private veiculos[] v = new veiculos[1000];
		private int tamanho = 0;

		public veiculos[] getveiculos(){
			return v;
		}

		public int gettamanho(){
			return tamanho;
		}

		//metodo que le o arquivo ate o final e vai guardando os objetos no array
		public void leitor_csv(String path) throws IOException{
			BufferedReader br = new BufferedReader(new FileReader(path));
			String linha = "";

			tamanho = 0;
			
			//para pular linha do cabecalho
			br.readLine();
			while((linha = br.readLine())!= null){
				veiculos ve = veiculos.parse_veiculos(linha);

				v[tamanho] = ve;
				//atualiza o tamanho a cada vez que guarda algo no vetor
				tamanho++;
			}

			br.close();
		}

		//chama o metodo anterior cm o nosso arquivo  
		public static LerCsv leitor ()  throws IOException{
			LerCsv ler = new LerCsv();

			ler.leitor_csv("/tmp/veiculos.csv");

			return ler;
		}
	}

	static class Celula{
		veiculos elemento;
		Celula prox;

		public Celula(){
			this(null);
		}

		public Celula(veiculos elemento){
			this.elemento = elemento;
			this.prox = null;
		}
	}

	static class Pilha{
		Celula topo;

		public Pilha(){
			topo = null;
		}

		public void inserir(veiculos x){
			Celula tmp = new Celula(x);
			tmp.prox = topo;
			topo = tmp;
			tmp = null;
		}

		public veiculos remover() throws Exception{
			if(topo == null){
				throw new Exception("ERRO");
			}

			veiculos resp = topo.elemento;
			Celula tmp = topo;
			topo = topo.prox;
			tmp.prox = null;
			tmp = null;
			return resp;
		}

		public void mostrar(){
			for(Celula i = topo; i != null; i = i.prox){
				System.out.println(i.elemento.format() + " ");
			}
		}
	}

	public static void main (String[] args)throws Exception{
		Scanner sc = new Scanner(System.in);

		LerCsv ler = LerCsv.leitor();
		veiculos[] v = ler.getveiculos();
		int tamanho = ler.gettamanho();

		Pilha pilha = new Pilha();

		int id = sc.nextInt();

		//parte 1
		while(id != -1){
			for(int i = 0; i < tamanho; i++){
				if(v[i].getid() == id){
					pilha.inserir(v[i]);
				}
			}
			id = sc.nextInt();
		}

		//segunda parte
		int quantidade = sc.nextInt();

		for(int i = 0; i < quantidade; i++){
			String comando = sc.next();

			if(comando.equals("I")){
				id = sc.nextInt();

				for(int j = 0; j < tamanho; j++){
					if(v[j].getid() == id){
						pilha.inserir(v[j]);
					}
				}
			}else if(comando.equals("R")){
				veiculos removido = pilha.remover();
				System.out.println("(R)" + removido.getmarca() + " " + removido.getmodelo());
			}
		}

		pilha.mostrar();

		sc.close();
	}
}
