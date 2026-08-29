// Gabrielly Neres

import java.util.Scanner;

public class Q11{
	
	//metodo privado passando i como parametros
	private static String inverter(String palavra, int i){
		int tam = palavra.length();
		//se for final da string retorna vazio 
		if(i == tam){
			return "";
		}
		//retorna palavra na volta, depois das chamadas retorna do maior i para o menor
		//resultado depois da chamada recursiva printa ao contrario
		return inverter(palavra, i+1) + palavra.charAt(i);
	}

	//metodo publico passando so a string como parametro
	public static String inverter(String palavra){
		return inverter(palavra, 0);
	}

	//funcao comparar se duas strings sao iguais
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
			System.out.println(inverter(palavra));

			palavra = scan.nextLine();
		}

		scan.close();
		
	}

}
