# shell_exercices


Ejercicios de prueba para conocer las funciones para minishell.


---Instrucciones---
1. Cambiar la ruta en la variable LIBFT_PATH del Makefile con la dirección de tu libft, y la ruta del header de la libft en los archivos echo.c , export.c  y kill.c 
2. 
      - **make echo** :   crea y ejecuta una microminishell que solo responde al comando 'echo +  1 argumento'
      - **make export**:  crea y ejecuta un programa para visualizar las variables de entorno que recoge main
      - **make kill**:    manejar señales, abrir otro terminal y ejecutar *ps u* para ver lista de procesos, ejecutar *kill -SIGALRM + (num de proceso que tenga kill)*; en la ejecución veremos como se recibe la señal de SIGALRM y se imprime su código de señal (14), mediante la función "mysighandler".
      - **make ls** :     crea y ejecuta un programa que hace un ls en el directorio actual
      - **make lswc**:    crea y ejecuta un programa que hace *ls -l | wc*  y tmb el comando real
      - **make ls3** :    crea y ejecuta un programa que replica *ls -l | grep u | wc -l* y compara con comando original
      - **make micro**:   crea y ejecuta una pequeña shell sencilla, sin estructuras de datos, a capón.
      - **make new**:     igual pero con estructuras de datos simples, pipes mejorados y algunos builtins
      - **tree**:         crea y ejecuta un programa que construye un árbol binario a partir de un array, y luego recorre y consulta con distintos métodos (recursivos)
      - **tree_stak**:    programa que construye el mismo árbol pero que utiliza una pila creada mediante lista enlazada para recorrerlo in-order.
3. Más detalles comentados en el Makefile
