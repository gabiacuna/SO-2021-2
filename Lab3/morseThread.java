import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.*;

public class morseThread extends Thread {
    static long inicio;
    static long fin;
    static String palabraf;
    String abc = "A .-_N -._B -..._Ñ --.--_C -.-._O ---_P .--._D -.._Q --.-_E ._R .-._F ..-._S ..._G --._T -_H ...._U ..-_I .._V ...-_J .---_W .--_K -.-_X -..-_L .-.._Y -.--_M --_Z --..";
    static Hashtable<String, String> my_dict;

    public morseThread(long i){     // Constructor de morseThread, recibe el tiempo en milisegundos en el que partio la ejecucion.
        super();
        inicio = i;
        palabraf = "";              // Acá guardaremos la palabra final.

        // Traspasamos del abc en str a un diccionario, para acceder facilmente a los significados.
        my_dict = new Hashtable<String, String>();

            String[] abc_list = abc.split("_");
            for (String par : abc_list) {
                String[] m = par.split(" ");
                my_dict.put(m[1], m[0]);
            }
            
    }

    public void printTime() {       // Metodo para imprimir el tiempo de ejecucion de la hebra.
        System.out.printf("morse time : %d\n", fin-inicio);
    }


    // Crearemos el diccionario morse a partir del txt morseabc, y luego lo usaremos para traducir cada letra, asi generando una palabra por fila.
    @Override
    public void run() {
        try {

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
