//Gabrielly Neres

import java.util.Scanner;

public class Q1{

	public static String ciframento(String palavra){
		String newWord = "";
		for(int i = 0; i < palavra.length(); i++){
			//pega os caracteres
			char c = palavra.charAt(i);
			//faz o ciframento
	  		int cif = (int) c+3;
			char nova = (char) cif;
			//compoe a nova palavra cifrada
			newWord += nova;
		}

		return newWord;
	}

//funcao para ver se duas palarvas sao iguais
public static boolean strcmp (String a, String b){
	boolean resp = true;
	int tam1 = 0;
	int tam2 = 0;

	tam1 = a.length();
	tam2 = b.length();

	if (tam1 < tam2 || tam1 > tam1){
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
		Scanner scan = new Scanner(System.in);

		String palavra = scan.nextLine();
		//verificacao para ler aquivo ate ser == FIM
		while(!(strcmp(palavra, "FIM"))){

		System.out.println(ciframento(palavra));	
		
		palavra = scan.nextLine();
		}
		scan.close();
	}

}
