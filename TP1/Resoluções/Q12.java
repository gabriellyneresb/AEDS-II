import java.util.Scanner;

public class Q12{

	public static int soma(int n){
		
		if(n == 0){
		    return 0;
		}
		// soma os digitos que sao o resto da divisao de n por 10 
		return n%10 + soma(n/10);
	}

	public static void main (String[] args){
		Scanner scan = new Scanner(System.in);

		int num = scan.nextInt();

		int resultado = soma(num);

		System.out.println(resultado);

		scan.close();
	}
}
