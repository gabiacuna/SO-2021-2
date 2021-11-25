import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class palThread extends Thread {
    
    static long inicio;
    static long fin;

    // Contructor de palThread, recibe el tiempo de inicio de ejecucion.
    public palThread(long i){
        super();
        inicio = i;
    }

    //  Imprime el tiempo de ejecucion 
    public void printTime() {
        System.out.printf("pal time : %d\n", fin-inicio);
    }

    //  Para la ejecución, recorremos todas las palabras de txt, fila por fila, y cuando encontremos "eiffel", imprimimos la palabra, y cerramos los archivos y retornamos.
    public void run() {
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
                  fin = System.currentTimeMillis();
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

    // Main de prueba para palThreads.
    public static void main(String[] args) {
        long start = System.currentTimeMillis();
        palThread h1 = new palThread(start);
        h1.start();
    }
}