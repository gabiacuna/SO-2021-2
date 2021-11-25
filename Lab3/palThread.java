import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class palThread extends Thread {
    public void run(long start) {
        try {
            File myObj = new File("palabras.txt");
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
              String data = myReader.nextLine();
              String[] pal = data.split(" ");

              for (String palabra : pal) {
                if (palabra.equals("eiffel")) {
                  System.out.println(palabra);
                  myReader.close();
                  long end = System.currentTimeMillis();
                  System.out.printf("pals time : %d\n", end-start);
                  return;
                }
              }
              //System.out.println(data);
            }
                myReader.close();
            } catch (FileNotFoundException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
    }

    public static void main(String[] args) {
        palThread h1 = new palThread();
        long start = System.currentTimeMillis();
        h1.start();
        h1.run(start);
    }
}