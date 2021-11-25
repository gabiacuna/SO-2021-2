import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.*;

public class morseThread extends Thread {
    static long inicio;
    static long fin;
    static String palabraf;

    public morseThread(long i){     // Constructor de morseThread, recibe el tiempo en milisegundos en el que partio la ejecucion.
        super();
        inicio = i;
        palabraf = "";              // Acá guardaremos la palabra final.
    }

    public void printTime() {       // Metodo para imprimir el tiempo de ejecucion de la hebra.
        System.out.printf("morse time : %d\n", fin-inicio);
    }


    // Crearemos el diccionario morse a partir del txt morseabc, y luego lo usaremos para traducir cada letra, asi generando una palabra por fila.
    @Override
    public void run() {
        try {
            
            // Creacion del dict
            File trad = new File("morseabc.txt");
            Scanner text = new Scanner(trad);
            Hashtable<String, String> my_dict = new Hashtable<String, String>();
            while (text.hasNextLine()) {
                String data = text.nextLine();
                String[] m = data.split(" ");
                    my_dict.put(m[1], m[0]);
              }
            text.close();

            // Recorremos morse.txt, traduciendo cada letra en la fila, concatenando estas, y cuando termine de leer dicha fila, le agregamos un espacio para separar las palabras.
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

    // Main de prueba, para ejecutar solo morseThread.
    public static void main(String[] args) {
        long start = System.currentTimeMillis();
        morseThread h1 = new morseThread(start);
        h1.start();
    }
}
