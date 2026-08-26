//Gabrielly Neres

import java.util.Scanner;
import java.util.Random;

public class Q2{

	public static Random gerador = new Random();

	public static String aleatorio(String palavra){
		//soma o valor do caracter a com o numero aleotorio para gerar a letra
		char letra1 = (char) ( 'a' + (Math.abs(gerador.nextInt()) % 26));
		char letra2 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));

		String Nova = "";
		
		//verifica a ocorrencia da letra1 na string recebida
		for(int i = 0; i < palavra.length(); i++){
			char c = palavra.charAt(i);
		
			//se tem a letra1 substitui todas ocorencias
			if(c == letra1){
				Nova+= letra2;	
			}else{
		     		Nova+= c;
			}
		}
		return Nova;
	}	

	//metodo para comparar duas palavras para ser usado na main, para ler ate entrada ser FIM
	public static boolean strcmp (String a, String b){
		boolean resp = true;
		int tam1 = 0;
		int tam2 = 0;

		tam1 = a.length();
		tam2 = b.length();

		if (tam1 < tam2 || tam1 > tam2){
			resp = false;
		} else {
			for(int i = 0; i < tam1 && i < tam2; i++){
				if(a.charAt(i) != b.charAt(i)){
					resp = false;
				}
			}
		}
         	return resp;
      }

	public static void main (String[] args){
		gerador.setSeed(4);

		Scanner scan = new Scanner(System.in);

		String palavra = scan.nextLine();

		while(!(strcmp(palavra, "FIM"))){
			
			System.out.println(aleatorio(palavra));

			palavra = scan.nextLine();
		}

		scan.close();	
	}

}
