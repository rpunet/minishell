NAME 		= echosh export kill ls ls_wc file_ls.txt ls3 microshell minishell newmicroshell
LIBFT_PATH	= ../../libftPLUS/

# regla por defecto con -o minishell para que funcione el minishel_test
default_for_test:
	@gcc microshell.c -L $(LIBFT_PATH) -lft -o minishell

# echo-shell: sólo responde ante el comando "echo" + 1 argumento
echo: clean
	@gcc echo.c -L $(LIBFT_PATH)	-lft -o echosh
	@./echosh

# export: para imprimir las variables de entorno que recoge envp
export: clean
	@gcc export.c -L $(LIBFT_PATH)  -lft -o export
	@./export

# manejar señales:
# ejecutar con make kill
# abrir otro terminal y ejecutar "ps u" para ver lista de procesos
# ejecutar "kill -SIGALRM + (num de proceso que tenga kill)"
# en la ejecución veremos como se recibe la señal de SIGALRM y se imprime su código de señal (14), mediante la función "mysighanler"
kill: clean
	@gcc kill.c -L $(LIBFT_PATH)  -lft -o kill
	@./kill

# comando:     ls desde el main, se ejecuta y termina.
ls: clean
	@gcc ls_nofork.c -o ls
	@./ls

# comando:     ls -l | wc > file_ls.txt
# 2 forks, un hijo para ls, otro para wc. Salida guardada en file_ls.txt
# se imprime un cat del archivo y el ls-l|wc real para comparar.
lswc: clean
	@gcc ls_wc.c -o ls_wc
	@./ls_wc
	@cat file_ls.txt
	@ls -l | wc

# comando:      ls -l | grep u | wc -l
# 3 forks, un hijo por proceso, la salida de cada uno se toma de entrada para el siguiente. Se cierran todos los fd.
# se compara la salida en consola del programa y del original
ls3: clean
	@gcc ls_3procesos.c -o ls3
	./ls3
	ls -l | grep u | wc -l

# microshell
micro: clean
	@gcc microshell.c -L $(LIBFT_PATH) -lft -o microshell
	@./microshell

new:  clean
	@gcc -g newmicroshell.c -L $(LIBFT_PATH) -lft -o newmicroshell
	@./newmicroshell


clean:
		@rm -f $(NAME)

