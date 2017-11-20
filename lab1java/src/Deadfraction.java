import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

/**
 * Created by Raindirve on 2017-09-25.
 */
public class Deadfraction {
    public static final boolean DEBUG = false;
    private static final Rational ZERO = new Rational("0", "1");
    public static void main(String[] strings){
        ArrayList<Rational> a = new ArrayList<>(9);

        Kattio sc = new Kattio(System.in);
        String s;
        s = sc.getWord();
        while(!s.equals("0")){

            long decs = Long.parseLong(s.substring(2, s.length()-3));
            long n = s.length()-5;
            Rational r;
            for(int i = 1; i <= n; i++){//last i decimals are repeating
                if(i != n) {
                    long left_den = (long) Math.pow(10, n - i);
                    long left_num = decs / (long) Math.pow(10, i);
                    r = new Rational(left_num + "", left_den + "");
                } else {
                    r = ZERO;
                }

                a.add(r.add(fractionFromRepeatingDecimals(decs % (long) Math.pow(10, i), i, n-i)));
            }

            if(DEBUG) {
                System.err.println("Resulting fractions: ");
                for (Rational _do : a) {
                    System.err.println(_do);
                }
                System.err.println("---END fracarray---");
            }

            int maxi = 0;
            for(int i = 0; i < n; ++i){
                if(a.get(i).denominator().compareTo(a.get(maxi).denominator()) < 0){ //smaller denominator
                    maxi = i;
                }
            }

            sc.println(a.get(maxi).numerator() + "/" + a.get(maxi).denominator());


            s = sc.getWord();
            a.clear();
        }
        sc.close();

    }

    private static Rational fractionFromRepeatingDecimals(long num, long len, long offset){
        len = (long)Math.pow(10, len); // 9999 = 10^(length)-1
        offset = (long)Math.pow(10, offset);
        if(DEBUG && (offset % 10 != 0) && (1 != offset)) throw new ArithmeticException("offset "+offset+" is not legit");
        if(DEBUG && (len % 10 != 0)) throw new ArithmeticException("len "+len+" is not legit");

        return new Rational(String.valueOf(num), String.valueOf((len-1)*offset));
    }
}
