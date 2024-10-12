
//Client

var name= prompt("What's your name?");
while(name ===""){
    name = prompt("You have to choose a name. \n What's your name?")
}

// Query DOM
var message = document.getElementById('message'),
   sender   = document.getElementById('sender'),
   btn      = document.getElementById('send'),
   output   = document.getElementById('output'),
   feedback = document.getElementById('feedback');

sender.innerHTML=name;  
sender.value=name;

// Invio richiesta di connessione al server
var webSocket = io.connect();
// - - - - - - - - - -



// - - - - - - - - - -
// Messages EVENT:
// - - - - - - - - - -

function sendMessage(){
   if (message.value!="" ){  
      webSocket.emit('typingStopped', {
         sender: sender.value
      });  
      webSocket.emit('message', {
       message: message.value,
       sender: sender.value,
      });
      message.value = "";
  }
};
// Listen for the event to send the message
btn.addEventListener('click', sendMessage);



// Per ricevere i messaggi (Web-Socket)
webSocket.on('UploadChat', function(data){
   feedback.innerHTML = ''; // feedback per mettere i messaggi uno sotto l'altro
   output.innerHTML += '<p><strong>' + data.sender + ': </strong>' + data.message + '</p>';
});
// - - - - - - - - - -




// - - - - - - - - - -
// isTyping EVENT:
// - - - - - - - - - -

function isTyping(event) {
   // Invia un evento 'typing' -> server
   webSocket.emit('typing', {
      sender: sender.value,     
   });

   // Se viene premuto il tasto Invio, invia il messaggio
   if (event.keyCode === 13) {
      event.preventDefault(); // Impedisce il cambio di riga
      sendMessage();
   }
}
// Attivazione isTyping
message.addEventListener("keydown", isTyping);

let whoWrite = document.getElementById('isTpg'); // nome utente sopra ai messaggi

// Gestione evento server -> typing.
webSocket.on('typing', function(data){
   // Cancella il contenuto dell'elemento che mostra il messaggio di scrittura
   whoWrite.innerHTML = '';
   // Aggiungi il messaggio di scrittura all'elemento
   whoWrite.innerHTML += '<p><strong>' + data.sender + ' sta scrivendo...' + '</strong></p>';
});


let timeoutId;

// Attivazione clear-isTyping
message.addEventListener("keyup", function() {
   // Cancella il timeout precedente
   clearTimeout(timeoutId);
   // Imposta un timeout per rimuovere il messaggio di scrittura dopo 1 secondo di inattività
   timeoutId = setTimeout(function() {
      webSocket.emit('typingStopped', {
         sender: sender.value
      });
   }, 3000);
});

// Ascolta l'evento 'typingStopped' dal server e rimuovi il messaggio di scrittura
webSocket.on('typingStop', function(data){
   // Cancella il contenuto dell'elemento che mostra il messaggio di scrittura
   whoWrite.innerHTML = '';
});
// - - - - - - - - - -


