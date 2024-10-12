# Sicurezza-delle-reti

Questa repository raccoglie esempi e spiegazioni pratiche su vari argomenti legati alla sicurezza delle reti, ai protocolli di comunicazione e alle tecnologie utilizzate nell'ambito delle reti e delle applicazioni distribuite. Gli argomenti trattati spaziano dall'uso di socket, alla crittografia, fino alle architetture REST e l'utilizzo di strumenti di analisi di rete come Wireshark.

## Contenuti della Repository

### 1. Socket e WebSocket
   - Introduzione ai socket e al loro utilizzo per stabilire comunicazioni tra client e server.
   - Differenze tra **socket TCP** e **socket UDP**.
   - Utilizzo dei **WebSocket** per le comunicazioni real-time via browser.
     
<img width="1308" alt="webchat" src="https://github.com/user-attachments/assets/6014e83e-802b-4be4-88fa-7ac52b3056a2">


### 2. Protocolli TCP e UDP
   - Approfondimento sui protocolli di trasporto **TCP** (Transmission Control Protocol) e **UDP** (User Datagram Protocol).
   - Analisi delle caratteristiche e dei casi d'uso di entrambi i protocolli.

### 3. API e Architettura REST
   - Creazione e gestione di **API** utilizzando l'architettura **REST**.
   - Buone pratiche per la progettazione di API scalabili e sicure.
   - Metodi HTTP principali (GET, POST, PUT, DELETE) e la gestione delle risposte.
<img width="1138" alt="Screenshot 2024-10-12 alle 13 07 20" src="https://github.com/user-attachments/assets/6b196167-3ea9-4b70-8ef0-c7bc39292e94">

### 4. Docker
   - Esempi di utilizzo di **Docker** per il deploy di applicazioni in ambienti isolati e portabili.
   - Configurazione di container per eseguire servizi di rete in maniera sicura ed efficiente.

### 5. Wireshark
   - Introduzione all'uso di **Wireshark**, uno strumento per l'analisi del traffico di rete.
   - Cattura e analisi dei pacchetti TCP/UDP per diagnosticare problemi di rete e valutare la sicurezza delle comunicazioni.

### 6. MQTT - Pub/Sub
   - Esempi e spiegazioni del protocollo **MQTT** (Message Queuing Telemetry Transport), utilizzato per la comunicazione **pub/sub** (publish/subscribe) in sistemi IoT.
   - Configurazione di un broker MQTT e gestione delle connessioni con i client.

### 7. Crittografia e Sicurezza
   - Introduzione alla **crittografia** e al suo ruolo nella sicurezza delle reti.
   - Differenze tra crittografia **simmetrica** (es. AES) e **asimmetrica** (es. RSA).
   - Esempi pratici di crittografia con chiavi pubbliche e private.

### 8. Proprietà della Crittografia Asimmetrica (RSA)
   - Discussione delle proprietà garantite dall'algoritmo **RSA**:
     - **Confidentiality (Confidenzialità)**: RSA assicura la protezione dei dati, consentendo di crittografare i messaggi con la chiave pubblica, garantendo che solo il detentore della chiave privata possa decifrarli.
     - **Integrity (Integrità)**: RSA può essere utilizzato per garantire che i dati non vengano alterati, tramite l'uso di firme digitali, che verificano che il messaggio non sia stato modificato durante il trasferimento.
     - **Authentication (Autenticazione)**: RSA permette l'autenticazione tramite la firma digitale, dove il mittente firma il messaggio con la propria chiave privata, permettendo ai destinatari di verificare l'identità del mittente con la chiave pubblica.



