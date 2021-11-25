import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.*;

public class morse extends Thread {
    static long inicio;
    static long fin;
    static String palabraf;

    public morse(long i){
        super();
        inicio = i;
        palabraf = "";
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
            System.out.println(palabraf);
            fin = System.currentTimeMillis();
            myReader.close();

            System.out.printf("morse time : %d\n", fin-inicio);

            } catch (FileNotFoundException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
    }

    public static void main(String[] args) {
        long start = System.currentTimeMillis();
        morse h1 = new morse(start);
        h1.start();
    }
}
