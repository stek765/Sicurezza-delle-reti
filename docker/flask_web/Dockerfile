# Utilizza un'immagine di base leggera di Alpine
FROM python:3.9-alpine

# Imposta l'ambiente Python per evitare problemi di buffering con stdout/stderr
ENV PYTHONUNBUFFERED=1

# Crea un virtual environment e installa le dipendenze
RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"

# Imposta il working directory
WORKDIR /app

# Copia il file requirements.txt nella directory di lavoro
COPY requirements.txt /app/

# Installa le dipendenze all'interno del virtual environment
RUN pip install --no-cache-dir -r requirements.txt

# Copia il resto del codice nell'immagine Docker
COPY . /app

# Comando di default per avviare l'applicazione
CMD ["python", "app.py"]
