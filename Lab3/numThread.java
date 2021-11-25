import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class numThread extends Thread {

    static long inicio;
    static long fin;

    public numThread(long i){
        super();
        inicio = i;
    }

    @Override
    public void run() {
        int [] numeros = new int[1024];

        try {
            File myObj = new File("numeros.txt");
            Scanner myReader = new Scanner(myObj);

            

            int i = 0;

            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                String[] pal = data.split(" ");
                for (String num : pal) {
                    int n = Integer.parseInt(num);
                    numeros[i] = n;
                    i++;
                }
            }
            myReader.close();

        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        } finally {
            for (int i = 0; i < numeros.length; i++)
                for (int j = i + 1; j < numeros.length; j++)
                    if ((numeros[i] + numeros[j]) == 65){
                        System.out.printf("%d %d", numeros[i], numeros[j]);
                        fin = System.currentTimeMillis();
                        System.out.printf("num time : %d\n", fin-inicio);
                        return;
                    }
        }
    }

    public static void main(String[] args) {
        long start_time = System.currentTimeMillis();

        palThread h1 = new palThread(start_time);
        numThread h2 = new numThread(start_time);
        morse h3 = new morse(start_time);

        h1.start();
        h2.start();
        h3.start();
        // h1.run(start);
        // h2.run(start);
    }
}