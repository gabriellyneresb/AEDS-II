//Gabrielly Neres

import java.util.Scanner;

public class Q8{


        public static boolean validar(String senha){
                boolean resp = true;
                boolean maiuscula = false;
                boolean minuscula = false;
                boolean numero = false;
                boolean oitodigitos = false;
                boolean especial = false;
		boolean espaco = true;

                int tam = senha.length();

		//verifica tamanho da senha
                if(tam >= 8){
                        oitodigitos = true;
                }
                //verificar se cada condicao e true
                for(int i = 0; i < tam; i++){
                        char c = senha.charAt(i);
                        if(c == ' '){
                                espaco = false;
                        }else if(c >= 'a' && c <= 'z'){
                                minuscula = true;
                        }else if(c >= '0' && c <= '9'){
                                numero = true;
                        }else if (c >= 'A' && c <= 'Z'){
                                maiuscula = true;
                        }else{
                                especial = true;
                        }
                }

                //se todas forem verdadeiras, sim senha invalido
                if(maiuscula && minuscula && numero && oitodigitos && especial && espaco){
                        resp = true;
                }else{
			resp = false;
		}

                return resp;
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
                Scanner scan = new Scanner (System.in);
		
		String senha = scan.nextLine();

		while(!strcmp(senha, "FIM")){
			if(validar(senha)){
				System.out.println("SIM");
			}else{
				System.out.println("NAO");
			}
			senha = scan.nextLine();
		}

                scan.close();
        }
}
