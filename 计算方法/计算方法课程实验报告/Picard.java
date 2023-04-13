public class Picard {
    public static double fai(double I){
        return 703.2*(1-Math.exp(-0.0552*(I+34.0)))-700+I;
    }

    public static void main(String[] args) {
        double x0 = 50;
        double x1 = fai(x0);
        while(Math.abs(x1-x0)>=0.0001){
            System.out.println(Math.abs(x1-x0));
            x0 = x1;
            x1 = fai(x0);
        }
        System.out.println(Math.abs(x1-x0));
        System.out.println("I = "+x1);
    }
}
