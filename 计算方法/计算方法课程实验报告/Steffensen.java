public class Steffensen {
    public static double f(double I){
        return 703.2*(1-Math.exp(-0.0552*(I+34.0)))-700;
    }

    public static void main(String[] args) {
        double x0 = 98;
        double x1 = x0-f(x0)*f(x0)/(f(x0)-f(x0-f(x0)));
        while(Math.abs(x1-x0)>=0.0001){
            x0 = x1;
            x1 = x0-f(x0)*f(x0)/(f(x0)-f(x0-f(x0)));
            System.out.println(Math.abs(x1-x0));
        }
        System.out.println("I = "+x1);
    }
}
