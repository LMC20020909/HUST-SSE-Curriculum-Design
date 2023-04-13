public class Dichotomy {
    public static double f(double I){
        return 703.2*(1-Math.exp(-0.0552*(I+34.0)))-700;
    }

    public static void main(String[] args) {
        double a = 50, b = 90;
        while(b-a >= 0.0001){
            double c = (a+b)/2;
            if(f(c)==0)
                break;
            else if(f(a)*f(c)<0)
                b = c;
            else
                a = c;
            System.out.println(b-a);
        }
        System.out.println("I = "+(a+b)/2);
    }
}