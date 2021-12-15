import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class MyThread extends Thread {

      public void run(){

         try {
            File pals_file=new File("palabras.txt");
            System.out.println(pals_file.canRead());
   
            Scanner myReader = new Scanner(pals_file);
            while (myReader.hasNextLine()) {
               String data = myReader.nextLine();
               // System.out.println(data);

               String[] linea = data.split(" ");

               for (String pal : linea) {
                  // System.out.println(pal);

                  if (pal.equals("eiffel")) {
                     System.out.println(pal);
                     myReader.close();
                     return;
                  }
               }
            }

         } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
         } finally {
         }

      }

      public static void main(String[] args) {
         MyThread myThread = new MyThread();
         myThread.start();
      }
  }