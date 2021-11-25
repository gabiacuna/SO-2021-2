public class Main {
    public static void main(String[] args) {
        long start_time = System.currentTimeMillis();

        //  Creamos los threads, con el tiempo de inicio en milisegundos.
        palThread h1 = new palThread(start_time);
        numThread h2 = new numThread(start_time);
        morseThread h3 = new morseThread(start_time);

        //  Lo ejecutamos con start para que sean concurrentes.
        h1.start();
        h2.start();
        h3.start();

        try {
            //  Esperamos a que todos terminen con join
            h1.join();
            h2.join();
            h3.join();
        } catch (Exception e) {
            System.out.println("error");
        } finally {
            // Finalmente, imprimimos los tiempos de ejecucion de cada uno.
            h1.printTime();
            h2.printTime();
            h3.printTime();
        }
    }
}
