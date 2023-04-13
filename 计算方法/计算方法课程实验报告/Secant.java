public class Secant {
    public static double f(double I){
        return 703.2*(1-Math.exp(-0.0552*(I+34.0)))-700;
    }

    public static void main(String[] args) {
        double x0 = 50, x1 = 90;
        double x2 = x1-(x1-x0)*f(x1)/(f(x1)-f(x0));
        double tol = 0.0001;
        while(Math.abs(x2-x1)>=tol){
            x0 = x1;
            x1 = x2;
            x2 = x1-(x1-x0)*f(x1)/(f(x1)-f(x0));
            System.out.println(Math.abs(x2-x1));
        }
        System.out.println("I = "+x2);
    }
}
