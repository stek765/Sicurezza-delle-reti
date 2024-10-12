import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;

public class ClientThreadREST_es_finale {    
    private static ConcurrentHashMap<Integer, int[]> results = new ConcurrentHashMap<>();
    private static CountDownLatch latch = new CountDownLatch(2); // due thread

    public static void main(String args[]) {
        if (args.length < 3) {
            System.out.println("USAGE: java ClientThreadREST_es_finale tipofunzione op1 op2");
        } else {
            System.out.println(args[0] + " " + args[1] + " " + args[2]);
            int mid = Integer.parseInt(args[2]) / 2;

            RESTAPI service1 = new RESTAPI(1, "localhost:8001", args[0], args[1], String.valueOf(mid));
            RESTAPI service2 = new RESTAPI(2, "localhost:8002", args[0], String.valueOf(mid), args[2]);

            service1.start();
            service2.start();

            try {
                latch.await(); // Attende che entrambi i thread abbiano terminato
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // Combina i risultati in modo ordinato
            List<Integer> finalResult = new ArrayList<>();
            results.forEach((key, value) -> {
                for (int i : value) {
                    finalResult.add(i);
                }
            });

            System.out.print("Risultato finale: ");
            finalResult.forEach(num -> System.out.print(num + " "));
            System.out.println();
        }
    }

    static class RESTAPI extends Thread {
        String server, service, param1, param2;
        int threadId;

        RESTAPI(int id, String remoteServer, String srvc, String p1, String p2) {
            this.threadId = id;
            this.server = remoteServer;
            this.service = srvc;
            this.param1 = p1;
            this.param2 = p2;
            System.out.println("-> " + server + " " + service + " " + param1 + " " + param2);
        }

        public void run() {
            if (service.equals("numeri-primi")) {
                int[] result = numeriPrimi(Float.parseFloat(param1), Float.parseFloat(param2));
                results.put(threadId, result);
                latch.countDown(); // Segnala che questo thread ha terminato
            }
        }

        synchronized int[] numeriPrimi(float val1, float val2) {
            URL u = null;
            int[] risultato = new int[0];

            try {
                u = new URL("http://" + server + "/numeri-primi?param1=" + val1 + "&param2=" + val2);
                System.out.println("URL aperto: " + u);
            } catch (MalformedURLException e) {
                System.out.println("URL errato: " + u);
                e.printStackTrace();
                return risultato;
            }

            try {
                HttpURLConnection c = (HttpURLConnection) u.openConnection();
                c.connect();
                BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
                System.out.println("Lettura dei dati...");
                String s;
                while ((s = b.readLine()) != null) {
                    
                    if (s.contains("numeri-primi")) {
                        String[] parts = s.split(":");
                        if (parts.length > 1) {
                            String[] numbers = parts[1].replaceAll("\\[|\\]|\\s", "").split(",");
                            risultato = new int[numbers.length];
                            for (int i = 0; i < numbers.length; i++) {
                                if (!numbers[i].isEmpty()) {
                                    risultato[i] = Integer.parseInt(numbers[i]);
                                }
                            }
                        }
                    }
                }
            } catch (IOException e) {
                System.out.println(e.getMessage());
                e.printStackTrace();
            }

            return risultato;
        }
    }
}
