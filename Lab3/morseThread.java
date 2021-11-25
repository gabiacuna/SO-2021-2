import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.*;

public class morseThread extends Thread {
    static long inicio;
    static long fin;
    static String palabraf;

    public morseThread(long i){
        super();
        inicio = i;
        palabraf = "";
    }

    public void printTime() {
        System.out.printf("morse time : %d\n", fin-inicio);
    }

    public void run() {
        try {
            
            File trad = new File("morseabc.txt");
            Scanner text = new Scanner(trad);
            Hashtable<String, String> my_dict = new Hashtable<String, String>();
            while (text.hasNextLine()) {
                String data = text.nextLine();
                String[] m = data.split(" ");
                    // System.out.printf("Key: %s,   val: %s\n", m[1], m[0]);
                    my_dict.put(m[1], m[0]);
              }
            text.close();


            File myObj = new File("morse.txt");
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
              String data = myReader.nextLine();
              String[] mor = data.split(" ");

                for (String palabra : mor) {
                    palabra = my_dict.get(palabra);
                    palabraf += palabra;
                }
                palabraf += " ";
            }
            myReader.close();

            System.out.println(palabraf);

            } catch (FileNotFoundException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            } finally {
                fin = System.currentTimeMillis();

            }
    }

    public static void main(String[] args) {
        long start = System.currentTimeMillis();
        morseThread h1 = new morseThread(start);
        h1.start();
    }
}
