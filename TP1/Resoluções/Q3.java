//Gabrielly Neres

public class Q3{

	public static boolean vogal (String palavra){
		boolean resp = true;
		for(int i = 0; i < palavra.length(); i++){
			char c = palavra.charAt(i);
			//verificar se nao e vogal 
			if(c != 'a' || c != 'e' || c != 'i' || c != 'o' ||
					c != 'u'){
				resp = false;		
			} 
		}
		return resp;
	}

	public static boolean consoantes (String palavra){
		boolean resp = true;
		for(int i = 0; i < palavra.length(); i++){
			char c = palavra.charAt(i);
			if(c == 'a' || c == 'e' || c == 'i' || c == 'o' ||
                                        c == 'u'){
                                resp = false;
                        }	
		}
		return resp;
	}

	public static boolean inteiros (String numero){
		boolean resp = true;
		for(int i = 0; i < numero.length(); i++){
			char c = numero.charAt(i);

			if(numero.charAt(0) == '-' || numero.charAt(0) == '+'){
				
			}else if(!())

		}
	}

}
