//Gabrielly Neres

import java.util.Scanner;

public class Q3{

	public static boolean vogal (String palavra){
		boolean resp = true;
		for(int i = 0; i < palavra.length(); i++){
			char c = palavra.charAt(i);
			//se nao é letra ou nao for vogal = false 
			if((c != 'a' && c != 'e' && c != 'i' &&
                             c != 'o' && c != 'u') && (c != 'A' && c != 'E' && c != 'I' &&
                             c != 'O' && c != 'U')){
				resp = false;		
			} 
		}
		return resp;
	}

	public static boolean consoante (String palavra){
		boolean resp = true;
		for(int i = 0; i < palavra.length(); i++){
			//verifica se é consoante
			char c = palavra.charAt(i);
			if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || (c == 'a' || c == 'e' || c == 'i' ||
			     c == 'o' || c == 'u') || (c == 'A' || c == 'E' || c == 'I' ||
                             c == 'O' || c == 'U')){
			     	resp = false;
			     }
		}
		return resp;
	}

	public static boolean inteiros (String numero){
		boolean resp = true;
		for(int i = 0; i < numero.length(); i++){
			char c = numero.charAt(i);
			//se nao for numero retorno false
			//se iniciar com '-' anda pra frente e ignora o sinal
			if((numero.charAt(i) == '-' && i == 0)|| (numero.charAt(i) == '+' && i == 0)){
				continue;
			}else if(!(c == '0' || c == '1'|| c == '2' || c == '3' || c == '4' ||
				 c == '5' || c == '6' || c == '7' || c == '8' || c == '9' ) || 
					(c =='.' || c == ',')){
				 	resp = false;	
			}
		}	
		return resp;
	}

	public static boolean reais(String numero){
		boolean resp = true;
		int cont = 0;
		for(int i = 0; i < numero.length(); i++){
			char c = numero.charAt(i);
			if((numero.charAt(i) == '-' && i == 0)|| (numero.charAt(i) == '+' && i == 0)){
				continue;
			}else if(c == '.' || c == ',' ){
				cont++;
				continue;
			}else if(!(c == '0' || c == '1'|| c == '2' || c == '3' || c == '4' || 
                                 c == '5' || c == '6' || c == '7' || c == '8' || c == '9' )){
				resp = false;	 
			}
			if(cont > 1){
				resp = false;
			}
		}
		return resp;
	}

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
		Scanner scan = new Scanner(System.in);
		
		String palavra = scan.nextLine();
		
		while(!strcmp(palavra, "FIM")){
			if(vogal(palavra)){
				System.out.println("SIM NAO NAO NAO");
			}else if(consoante(palavra)){
				System.out.println("NAO SIM NAO NAO");
			}else if(inteiros(palavra)){
				System.out.println("NAO NAO SIM SIM");
			}else if(reais(palavra)){
				System.out.println("NAO NAO NAO SIM");
			}else{
				System.out.println("NAO NAO NAO NAO");
			}
		   palavra = scan.nextLine();
		}
		scan.close();
	}
}
