import java.io.*; 


class G {
  public static int count = 0;
}

class ThreadJoining extends Thread 
{ 
    @Override
    public void run() 
    { 
        Thread t = Thread.currentThread();

        System.out.println("This is Thread :"+ t.getName()); 
        System.out.println("Thread ID: " + t.getId());

        for(int i=0; i<250000; i++) G.count++;
    } 
} 

class test{

    public static void main(String args[]){  
        ThreadJoining t1 = new ThreadJoining(); 
        ThreadJoining t2 = new ThreadJoining(); 
        ThreadJoining t3 = new ThreadJoining();
        ThreadJoining t4 = new ThreadJoining();

        t1.start();
        t2.start();
        t3.start();
        t4.start();

        try {
            t1.join();
            t2.join();
            t3.join();
            t4.join();
        } catch (InterruptedException e) {
            System.out.println("執行緒被中斷");
        }

        
        System.out.println(G.count);
     }  
}  