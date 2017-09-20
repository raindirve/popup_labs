/** Simple yet moderately fast I/O routines.
 *
 * Example usage:
 *
 * Kattio io = new Kattio(System.in, System.out);
 *
 * while (io.hasMoreTokens()) {
 *    int n = io.getInt();
 *    double d = io.getDouble();
 *    double ans = d*n;
 *
 *    io.println("Answer: " + ans);
 * }
 *
 * io.close();
 *
 *
 * Some notes:
 *
 * - When done, you should always do io.close() or io.flush() on the
 *   Kattio-instance, otherwise, you may lose output.
 *
 * - The getInt(), getDouble(), and getLong() methods will throw an
 *   exception if there is no more data in the input, so it is generally
 *   a good idea to use hasMoreTokens() to check for end-of-file.
 *
 * @author: Kattis
 */

import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.OutputStream;

class Kattio extends PrintWriter {
    public static void main(String[] args) {
        Kattio sc = new Kattio(System.in);
        int t = sc.getInt();
        while (t-- > 0) {
            int n1, n2;
            int n = 1;
            n1 = sc.getInt();
            System.err.println("ok got n1");
            String[] tmp = new String[n1+1];
            for (int i = 0; i <= n1; ++i) {
                tmp[i] = sc.getWord();
            }
            System.err.println("ok got first array");
            n2 = sc.getInt();
            System.err.println("ok got n2");
            while (n1 >= n || n2 >= n) { //find smallest power of 2 larger than both degrees
                n <<= 1;
            }

            int[] a1 = new int[n], a2 = new int[n];
            for (int i = 0; i < tmp.length; ++i) {
                a1[i] = Integer.parseInt(tmp[i]);
            }
            for (int i = 0; i <= n2; ++i) {
                a2[i] = sc.getInt();
            }

            int[] result = Karatsuba.pmult_new(a1, a2, n);
            //find largest non0 value
            int i = result.length - 1;
            while (i-- > 0 && result[i] == 0) ;
            sc.println(i);
            for (int j = 0; j <= i; ++j) {
                sc.print(result[j] + " ");
            }
        }
        sc.close();
    }
    public Kattio(InputStream i) {
        super(new BufferedOutputStream(System.out));
        r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
        super(new BufferedOutputStream(o));
        r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
        return peekToken() != null;
    }

    public int getInt() {
        return Integer.parseInt(nextToken());
    }

    public double getDouble() {
        return Double.parseDouble(nextToken());
    }

    public long getLong() {
        return Long.parseLong(nextToken());
    }

    public String getWord() {
        return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
        if (token == null)
            try {
                while (st == null || !st.hasMoreTokens()) {
                    line = r.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                }
                token = st.nextToken();
            } catch (IOException e) { }
        return token;
    }

    private String nextToken() {
        String ans = peekToken();
        token = null;
        return ans;
    }
}
