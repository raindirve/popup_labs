import java.util.Scanner;

/**
 * Created by Raindirve on 2017-09-20.
 *
 * IO gate from kattis:rationalarithmetic to popup17:michalh+seanw:Rational
 */

public class RationalKattis {
    public static void main(String[] strings){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        sc.nextLine();
        String[] split;
        Rational r1, r2;
        while(n-->0){
            split = sc.nextLine().split(" ");
            r1 = new Rational(split[0], split[1]);
            r2 = new Rational(split[3], split[4]);
            switch (split[2].charAt(0)){
                case '+':
                    r1.addInPlace(r2);
                    break;
                case '-':
                    r1.subtractInPlace(r2);
                    break;
                case '*':
                    r1.multiplyInPlace(r2);
                    break;
                case '/':
                    r1.divideInPlace(r2);
                    break;
                default:
                    System.err.println("Did not recognise operation: "+split[2]+" - Please make sure it's a character matching one of [+-*/]!");
                    throw new RuntimeException("invalid operation");
            }
            System.out.println(r1);
        }
    }
}
