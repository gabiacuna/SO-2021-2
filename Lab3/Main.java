public class Main {
    public static void main(String[] args) {
        long start_time = System.currentTimeMillis();

        palThread h1 = new palThread(start_time);
        numThread h2 = new numThread(start_time);
        morseThread h3 = new morseThread(start_time);

        h1.start();
        h2.start();
        h3.start();

        try {
            h1.join();
            h2.join();
            h3.join();
        } catch (Exception e) {
            System.out.println("error");
        } finally {
            h1.printTime();
            h2.printTime();
            h3.printTime();
        }
    }
}
