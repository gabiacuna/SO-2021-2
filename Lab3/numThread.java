import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class numThread extends Thread {

    static long inicio;
    static long fin;

    // Constructor de numThread, recibe el tiempo de inicio de la ejecucion como parametro.
    public numThread(long i){
        super();
        inicio = i;
    }

    //  Metodo para imprimir el tiempo de ejecucion total
    public void printTime() {
        System.out.printf("num time : %d\n", fin-inicio);
    }

    // Para la ejecucion, primero creamos una lista de todos los numeros en "numeros.txt", y luego vemos cada par posible de estos, revisando desde la posicion actual hasta el final del arreglo
    // se termina el programa cuando encuentre un par de numeros, no necesariamente consecutivos, los cuale sumen 65, se imprimira este par.
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
                        System.out.printf("%d %d\n", numeros[i], numeros[j]);
                        fin = System.currentTimeMillis();
                        return;
                    }
        }
    }

    // Main de prueba, corre solo este thread
    public static void main(String[] args) {
        long start_time = System.currentTimeMillis();
        numThread h2 = new numThread(start_time);

        h2.start();

        try {
            h2.join();
        } catch (Exception e) {
            System.out.println("error");
        } finally {
            h2.printTime();
        }
    }
}