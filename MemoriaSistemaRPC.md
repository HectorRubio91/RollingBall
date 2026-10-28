Memoria de Practica 1 - Sistema RPC
=
## 1. Objetivo del proyecto
 
El proyecto consiste en implementar un sistema de llamadas a procedimientos remotos. La idea es poder ejecutar funciones externas a la maquina, 
pero como si se tratase de una llamada a función normal, sin tener que gestionar manualmente toda la comunicación desde el programa principal. 
El sistema utiliza dos máquinas AWS EC2: una actúa como servidor y contiene los procedimientos que se pueden ejecutar, mientras que la otra actúa como cliente y solicita su ejecución.
La comunicación se realiza mediante sockets TCP y mensajes JSON

## 2. Arquitectura y organización del proyecto

El proyecto está dividido en varios módulos para separar las responsabilidades. Cada archivo tiene una función concreta, lo que facilita entender el sistema, encontrar errores y añadir nuevas funcionalidades sin tener que modificar todo el código.

La estructura general es la siguiente:

practica_rpc/

├── client/

  ─ client_example.py

  ─ rpc_client.py

├── server/

  ─ server.py

  ─ procedures.py

  ─ rpc_server.py

├── common/

  ─ protocol.py

├── tests/

  ─ test_rpc.py
    
└── README.md

### - Cliente

El cliente contiene dos archivos principales.

* client_example.py es el programa que se ejecuta para probar el sistema. Realiza llamadas a los procedimientos disponibles y muestra los resultados.

* rpc_client.py contiene la clase RPCClient. Su función es ocultar los detalles de la comunicación. El programa principal solo necesita indicar el nombre del procedimiento y sus argumentos mediante call(). Esta clase prepara la petición, establece la conexión TCP, envía el mensaje, recibe la respuesta y devuelve el resultado o comunica un error.

De esta forma, el código que utiliza el cliente no necesita conocer los detalles del protocolo ni gestionar directamente los sockets.

### - Servidor

El servidor se divide en tres archivos.

* server.py es el punto de entrada del servidor. Abre el socket TCP, escucha en el puerto configurado, acepta conexiones y delega su atención a un pool de hilos.

* rpc_server.py contiene la clase RPCServer. Registra los procedimientos disponibles y decide qué función debe ejecutarse cuando llega una petición. Esta parte se conoce como dispatcher.

* procedures.py contiene las funciones que se pueden ejecutar remotamente: suma, multiplicación, potencia, una tarea lenta, comprobación de paridad y cálculo de la raíz cuadrada.

La separación permite cambiar la forma de comunicación sin tener que modificar las operaciones matemáticas, o añadir procedimientos nuevos sin reescribir el servidor TCP.

### Protocolo común

El archivo common/protocol.py contiene las funciones utilizadas por el cliente y el servidor para enviar y recibir mensajes JSON. Ambos utilizan las mismas reglas,
de modo que interpretan los mensajes de la misma forma.

### Pruebas

El archivo tests/test_rpc.py contiene pruebas automatizadas para comprobar el protocolo, el funcionamiento del dispatcher y la gestión de algunos errores. 
Estas pruebas permiten detectar problemas en la lógica del sistema antes de realizar pruebas completas entre las dos máquinas.

## 3. Protocolo de comunicación

La comunicación utiliza TCP, que proporciona un canal fiable y ordenado de bytes, pero no conserva los límites de los mensajes de la aplicación. 
Por este motivo, el proyecto necesita definir cómo saber dónde termina cada mensaje.

Una petición tiene esta estructura:

{
  "function": "sumar",
  "args": [4, 7]
}

Si se produce un error, el servidor devuelve una respuesta como:

{
  "status": "error",
  "error": "PROCEDURE_NOT_FOUND"
}

El encabezado permite al receptor conocer cuántos bytes tiene que leer para reconstruir el mensaje completo, incluso cuando TCP entrega los datos en varios fragmentos. 
Las funciones _recv_exact(), send_json() y recv_json() se encargan de esta tarea.
También existe un límite para el tamaño de los mensajes, con el objetivo de evitar recibir peticiones excesivamente grandes.

## 4. Procedimientos y gestión de errores

Los procedimientos están separados de la comunicación. Cada función realiza una operación concreta y devuelve su resultado. El servidor registra estas funciones mediante RPCServer.register(), por lo que solo se pueden ejecutar remotamente las que están registradas.

Actualmente, el sistema incluye seis procedimientos:

* sumar(a, b): suma dos números.
* multiplicar(a, b): multiplica dos números.
* potencia(a, b): calcula una potencia.
* tarea_lenta(segundos): espera el tiempo indicado y lo devuelve.
* es_par(numero): indica si un número es par.
* raiz_cuadrada(numero): calcula la raíz cuadrada de un número no negativo.

El dispatcher comprueba el formato de la petición, busca la función y gestiona los errores que se puedan producir. Por ejemplo, puede indicar que la petición es incorrecta, que el procedimiento no existe, 
que los argumentos no son válidos o que se ha producido un error durante la ejecución.

Por su parte, el cliente distingue entre los errores comunicados por el servidor y los problemas de comunicación, como una conexión fallida o un timeout. 
Esto permite que el programa que utiliza RPC pueda reaccionar ante los errores sin tener que conocer los detalles internos del servidor.

## 5. Concurrencia y timeouts

El servidor utiliza ThreadPoolExecutor, con un máximo de veinte hilos de trabajo. Cuando llega una conexión, el hilo principal acepta al cliente y entrega su atención al pool.

Esto permite atender varias conexiones de forma simultánea. Por ejemplo, mientras un cliente ejecuta tarea_lenta(10), otro cliente puede solicitar una suma sin tener que esperar a que termine la tarea lenta.

El número máximo de hilos limita cuántas conexiones pueden atenderse simultáneamente. No significa que todas las conexiones pendientes se procesen de inmediato si todos los trabajadores están ocupados.

El sistema también configura timeouts en los sockets. Estos limitan el tiempo de espera durante las operaciones de comunicación, 
evitando que un cliente o servidor permanezca bloqueado indefinidamente esperando datos. 
Sin embargo, un timeout de socket no cancela automáticamente una función que ya se está ejecutando. La duración de tarea_lenta se limita por separado.
