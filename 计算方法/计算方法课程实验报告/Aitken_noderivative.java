public class Aitken_noderivative {
    public static double fai(double I){
        return 703.2*(1-Math.exp(-0.0552*(I+34.0)))-700+I;
    }

    public static void main(String[] args) {
        double x0 = 50;
        double x1 = fai(x0);
        double x2 = fai(x1);
        double x3 = x2-(x2-x1)*(x2-x1)/(x2-2*x1+x0);
        while(Math.abs(x3-x0)>=0.0001){
            System.out.println(Math.abs(x3-x0));
            x0 = x3;
            x1 = fai(x0);
            x2 = fai(x1);
            x3 = x2-(x2-x1)*(x2-x1)/(x2-2*x1+x0);
        }
        System.out.println(Math.abs(x3-x0));
        System.out.println("I = "+x3);
    }
}
