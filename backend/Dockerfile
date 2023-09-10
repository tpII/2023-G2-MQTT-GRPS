# Usamos una imagen base de Python
FROM python:3.9-slim

# Establecemos un directorio de trabajo
WORKDIR /app

# Copiamos el script y el archivo de requerimientos al contenedor
COPY backend.py .
COPY requirements.txt .

# Instalamos las dependencias
RUN pip install --no-cache-dir -r requirements.txt

# Comando para ejecutar el script cuando el contenedor se inicie
CMD ["python", "./backend.py"]
