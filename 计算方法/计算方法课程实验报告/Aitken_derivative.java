public class Aitken_derivative {
    public static double fai(double I){
        return 703.2*(1-Math.exp(-0.0552*(I+34.0)))-700+I;
    }

    public static double dfai(double I){
        return 38.81664*Math.exp(-0.0552*(I+34.0))+1;
    }

    public static void main(String[] args) {
        double l = dfai((50+90)/2.0);
        double x0 = 50;
        double x1 = (fai(x0)-l*x0)/(1-l);
        while(Math.abs(x1-x0)>=0.0001){
            System.out.println(Math.abs(x1-x0));
            x0 = x1;
            x1 = (fai(x0)-l*x0)/(1-l);
        }
        System.out.println(Math.abs(x1-x0));
        System.out.println("I = "+x1);
    }
}
