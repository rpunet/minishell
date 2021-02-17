# shell_exercices


Ejercicios de prueba para conocer las funciones para minishell.

---Instrucciones---
1. Cambiar la ruta en la variable LIBFT_PATH del Makefile con la dirección de tu libft, y la ruta del header de la libft en los archivos echo.c , export.c  y kill.c 
2. 
      - make echo :   ejecuta una microminishell que solo responde al comando 'echo +  1 argumento'
      - make export:  ejecuta un programa para visualizar las variables de entorno que recoge main
      - make kill:    manejar señales, abrir otro terminal y ejecutar "ps u" para ver lista de procesos, ejecutar "kill -SIGALRM + (num de proceso que tenga kill)"
                      en la ejecución veremos como se recibe la señal de SIGALRM y se imprime su código de señal (14), mediante la función "mysighanler"
      - ma
