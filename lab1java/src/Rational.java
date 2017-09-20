import java.math.BigInteger;

/**
 * Java version of fraction for popup17 lab1, exploiting
 * the STL BigInteger. Maintains the most reduced form of
 * itself with a positive denominator after each operation.
 *
 * Implements addition, subtraction, multiplication and division.
 * Objects can be used "immutably" akin to BigIntegers, but this
 * is only guaranteed until any []InPlace operation is called
 * by the user. These are exposed for performance-sensitive contexts.
 *
 * WIP version.
 *
 * (Extension note: All operators assume any negative fraction is of form
 * -numerator/denumerator and any positive fraction is of form
 * numerator/denumerator, i.e. den is never negative. This is aggressively
 * maintained where an operation is made that does not guarantee consistency.)
 *
 * @author Sean Wenström
 * @author Michal Horemuz
 */
public class Rational implements Comparable<Rational>{

    private BigInteger num = null, den = null;

    public Rational(String num, String den) {
        this.num = new BigInteger(num);
        this.den = new BigInteger(den);
        fixSigns();
    }

    private Rational(BigInteger num, BigInteger den) {
        this.num = num;
        this.den = den;
    }

    /**
     * Copy constructor, exploits BigInteger's immutability
     */
    public Rational(Rational r){
        this.num = r.num;
        this.den = r.den;
    }

    public Rational copy(){
        return new Rational(this);
    }


    public Rational add(Rational r){
        return copy().addInPlace(r.copy());
    }
    public Rational addInPlace(Rational r){
        r = matchDenominatorTotalInPlace(r);
        num = num.add(r.num);
        reduce();
        return this;
    }

    public Rational subtract(Rational r){
        return copy().subtractInPlace(r.copy());
    }
    public Rational subtractInPlace(Rational r){
        r = matchDenominatorTotalInPlace(r);
        num = num.subtract(r.num);
        reduce();
        return this;
    }

    public int signum(){
        return num.signum();
    }

    public Rational multiply(Rational r){
        return copy().multiplyInPlace(r);
    }

    public Rational multiplyInPlace(Rational r){
        //System.err.println("Multiplying in place: "+this+" / "+r);
        num = num.multiply(r.num);
        den = den.multiply(r.den);
        reduce();
        return this;
    }


    public Rational divide(Rational r){
        return copy().divideInPlace(r);
    }
    public Rational divideInPlace(Rational r){
        //cross multiply
        //System.err.println("Dividing in place: "+this+" / "+r);
        return multiplyInPlace(new Rational(r.den, r.num).fixSigns());
    }

    /**
     * Matches the denominator of the target fraction.
     *
     * Returns a copy of the target fraction also extended,
     * such that this fraction and the other have the LCM of
     * both denominators.
     *
     * @return
     */
    private Rational matchDenominatorInPlace(final Rational r2){
       return matchDenominatorTotalInPlace(r2.copy());
    }


    private Rational matchDenominatorTotalInPlace(Rational other) {
        BigInteger gcd = den.gcd(other.den);
        BigInteger lmult = other.den.divide(gcd);
        BigInteger rmult = den.divide(gcd);
        extend(lmult);
        other.extend(rmult);
        return other;
    }

    private void extend(BigInteger mult) {
        num = num.multiply(mult);
        den = den.multiply(mult);
    }


    private void reduce(){
        BigInteger gcd = num.gcd(den);
        //System.err.println("Reducing fraction "+this+", GCD "+gcd);
        num = num.divide(gcd);
        den = den.divide(gcd);
        //System.err.println("End result "+this+", GCD "+num.gcd(den));
    }

    /**
     * Call after any operation that does not guarantee format (-num)/(+den)
     * or (+num)/(+den) - i.e. input or division only.
     *
     * Also checks for 0-division, just in case.
     */
    private Rational fixSigns(){

        if(den.signum() == -1){
            num = num.negate();
            den = den.negate();
        }
        if(den.signum() == 0){
            throw new ArithmeticException("popup17:Rational.java somehow ended up with rational number with 0 denominator.");
        }
        return this;
    }

    public String toString(){
        return num + " / " + den;
    }

    @Override
    public int compareTo(Rational o) {
        return this.subtract(o).signum();
    }

    public boolean equals(Rational o) {
        return num.equals(o.num) && den.equals(o.den);
    }
}
