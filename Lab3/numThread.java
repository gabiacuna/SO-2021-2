import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class numThread extends Thread {
    public void run(long start) {
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
                        long end = System.currentTimeMillis();
                        System.out.printf("num time : %d\n", end-start);
                        return;
                    }
        }
    }

    public static void main(String[] args) {
        palThread h1 = new palThread();
        numThread h2 = new numThread();

        long start_time = System.currentTimeMillis();
        h1.start();
        h2.start();
        // h1.run(start);
        // h2.run(start);
    }
}