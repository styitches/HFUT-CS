class firstcal extends Thread{
    long answer1;

    public boolean isPrime(int n){
        if (n < 2) {
            return false;
        }
        int squareRoot=(int) Math.sqrt(n);
        for (int i = 2; i <= squareRoot; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    @Override
    public void run(){
        answer1 = 0;
        for (int i = 1; i < 100000; i++){
            if (isPrime(i)){
                answer1 += i;
            }
        }
        System.out.println(answer1);
    }

    public long getAnswer1(){
        return answer1;
    }
};

class secondcal extends Thread{
    long answer2;

    public boolean isPerfect(int x)
    {
        int sum = 1;
        for(int i = 2; i < x; i++){
            if( x % i == 0){
                sum += i;
            }
        }
        if(sum == x){
            return true;
        } else {
            return false;
        }
    }

    @Override
    public void run(){
        for(int i = 1; i <= 10000; i++){
            if(isPerfect(i)){
                answer2 += i;
            }
        }
        System.out.println(answer2);
    }

    public long getAnswer2(){
        return answer2;
    }
}
public class work4_2 {
    public static void main(String[] args) {
        firstcal first = new firstcal();
        secondcal second = new secondcal();
        first.start();
        second.start();
        try {
            first.join();
            second.join();
        } catch (InterruptedException e){}

        System.out.println(first.getAnswer1() * second.getAnswer2());
    }
}