import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

class ClientREST {
    public static void main(String args[]) {
        RESTAPI service1 = new RESTAPI("127.0.0.1");

        if (args.length < 3) {
            System.out.println("USAGE: java ClientREST tipofunzione op1 op2");
        } else if (args[0].equals("calcola-somma")) {
            System.out.println("Risultato: " + service1.calcolaSomma(Float.parseFloat(args[1]), Float.parseFloat(args[2])));
        } else if (args[0].equals("numeri-primi")) {
            int[] result = service1.numeriPrimi(Float.parseFloat(args[1]), Float.parseFloat(args[2]));
            System.out.print("Risultato: ");
            for (int i : result) {
                System.out.print(i + " ");
            }
            System.out.println();
        }
    }
}

class RESTAPI {
    String server;  

    RESTAPI(String remoteServer) {
        server = new String(remoteServer);
    }
    
    float calcolaSomma(float val1, float val2) {
        URL u = null;
        float risultato = 0;
        int i;

        try {
            // ogetto URL -> u
            u = new URL("http://" + server + ":8000/calcola-somma?param1=" + val1 + "&param2=" + val2);
            System.out.println("URL aperto: " + u);
        } catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
            return risultato;
        }

        try {
            // Apre connessione
            HttpURLConnection c = (HttpURLConnection) u.openConnection();
            c.connect();
            // Legge la risposta
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            System.out.println("Lettura dei dati...");
            String s;
            while ((s = b.readLine()) != null) {
                // Stampa ogni riga
                System.out.println(s);
                // Se le riga contiene "somma", il valore è convertito in float
                if ((i = s.indexOf("somma")) != -1)
                    risultato = Float.parseFloat(s.substring(i + 7));
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        return risultato;
    }

    int[] numeriPrimi(float val1, float val2) {
        URL u = null;
        int[] risultato = new int[200];
        int i;

        try {
            // ogetto URL -> u
            u = new URL("http://" + server + ":8000/numeri-primi?param1=" + val1 + "&param2=" + val2);
            System.out.println("URL aperto: " + u);
        } catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
            return risultato;
        }

        try {
            // Apre connessione
            HttpURLConnection c = (HttpURLConnection) u.openConnection();
            c.connect();
            // Legge la risposta
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            System.out.println("Lettura dei dati...\n");
            String s;
            while ((s = b.readLine()) != null) {
                // Stampa ogni riga
                // System.out.println(s);

                // Se le riga contiene "numeri-primi", prende le parte dopo i : e toglie [] dell'array 
                // infine converte le stringhe in interi e stamp
                if (s.contains("numeri-primi")) {
                    String[] parts = s.split(":");
                    String[] numbers = parts[1].replaceAll("\\[|\\]|\\s", "").split(",");
                    risultato = new int[numbers.length];
                    for (i = 0; i < numbers.length; i++) {
                        risultato[i] = Integer.parseInt(numbers[i]);
                    }
                    return risultato;
                }
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        // Gestione dell'errore o ritorno di un risultato di default
        return risultato; // o qualsiasi altro valore di default appropriato
    }
}
