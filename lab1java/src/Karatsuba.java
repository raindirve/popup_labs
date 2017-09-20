import java.util.ArrayList;
import java.util.Arrays;

/**
 * Java implementation of Karatsuba polynomial multiplication,
 * for popup17 lab1 polymul2
 *
 * WIP version
 *
 * Based on Karatsuba's algorithm as described in
 * http://www.maia.ub.es/dsg/sam07/sam07mul.pdf
 *
 * Seriously, read it if you don't understand the algorithm.
 * This code will not help in that respect.
 *
 * @author Sean Wenström
 * @author Michal Horemuz
 */
public class Karatsuba {
    public static void main(String[] args){
        //TEST UNIT: CollectResults

//        int[] target = new int[8];
//        int[] c1 = {1,2,3,4}, c6 = {1,1,1,1}, c2 = {-2,-2,-2,-2};
//        collectResults(target, c1, c6, c2, 4);
//        System.out.println(Arrays.toString(target));

//        int[] target = new int[8];
//        int[] op1 = new int[]{1, 1, 1, 1};
//        int[] op2 = new int[]{1, 1, 1, 1};
//        pmult(target, op1, op2, 4);


    }

    /**
     * CALL WITH n=2^k where n>=max(a.size, b.size)
     */
    static int[] pmult_new(int[] a, int[] b, int n){
        int[] target = new int[n*2];
        pmult(target, a, b, n);
        return target;
    }
    static void pmult(int[] target, int[] a, int[] b, int n){
//        System.err.println(""+n);
        // INVARIANT to make sense of the function calls: "n" is always the length of the largest array,
        // (except in this function cause I done goofed)
        // always a power of 2, and always passed as the last argument
        if(n == 1){ //1-size array, base case
            target[0] = a[0] * b[0];
            target[1] = 0;
            return;
        }

        int half = n/2;

        int[] a0 = new int[half], a1 = new int[half];
        int[] b0 = new int[half], b1 = new int[half];
        splitInto(a, a0, a1, n);
        splitInto(b, b0, b1, n);
        if(0 == -1) {
            System.out.println("SPLIT a, b INTO");
            System.out.println(Arrays.toString(a0));
            System.out.println(Arrays.toString(a1));
            System.out.println(Arrays.toString(b0));
            System.out.println(Arrays.toString(b1));
            System.out.println("END");
        }
        //reuse to avoid making so many gorram arrays, c1,c2 = a,b
        a = pmult_new(a0, b0, half);
        b = pmult_new(a1, b1, half);
        if(0 == -1) {
            System.out.println("c1, c2");
            System.out.println(Arrays.toString(a));
            System.out.println(Arrays.toString(b));
            System.out.println("END");
        }
        //c3,c4 = a0,b0
        addInPlace(a0, a1, half);
        addInPlace(b0, b1, half);
        if(0 == -1) {
            System.out.println("c3=a0+a1");
            System.out.println(Arrays.toString(a0));
            System.out.println("c4=b0+b1");
            System.out.println(Arrays.toString(b0));
            System.out.println("END");
        }
        //c5 <=> c6
        int[] c5 = pmult_new(a0, b0, half);
        if(0 == -1) {
            System.out.println("c5=c3*c4");
            System.out.println(Arrays.toString(c5));
        }
        subtractInPlace(c5, a, n);
        subtractInPlace(c5, b, n);
        if(0 == -1) {
            System.out.println("c6=c5-c1-c2");
            System.out.println(Arrays.toString(c5));
        }
        collectResults(target, a, c5, b, n);
        if(0 == -1) {
            System.out.println("TARGET REACHED");
            System.out.println(Arrays.toString(target));
        }
    }

    static private void collectResults(int[] target, int[] c1, int[] c6, int[] c2, int n) {
        /*System.err.println("Collecting results, target.length="+target.length+", n="+n);
        System.err.println(Arrays.toString(c1));
        System.err.println(Arrays.toString(c6));
        System.err.println(Arrays.toString(c2));*/
        for(int i = 0; i < n; ++i){
            target[i] = c1[i];
        }
        for(int i = n/2; i < n+n/2; ++i){
            target[i] += c6[i-n/2];
        }
        for(int i = n; i < 2*n; ++i){
            target[i] += c2[i-n];
        }
    }

    static void splitInto(int[] orig, int[] a1, int[] a2, int n){
        for(int i = 0; i < n/2; ++i){
            a1[i] = orig[i];
            a2[i] = orig[i+n/2];
        }
    }

    static void addInPlace(int[] op, int[] add, int n){
        for(int i = 0; i < n; ++i){
            op[i] += add[i];
        }
    }

    static void subtractInPlace(int[] op, int[] dif, int n){
        for(int i = 0; i < n; ++i){
            op[i] -= dif[i];
        }
    }
}
