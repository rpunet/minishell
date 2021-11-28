/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TODOs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:52:53 by jcarrete          #+#    #+#             */
/*   Updated: 2021/11/27 20:56:26 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//*		No interpretar comillas sin cerrar o caracteres especiales no especificados como \ o ;.
//*		No usar más de una variable global, piensa por qué y prepárate para explicar el uso que le das.
//*		Mostrar una entrada que espere introducir un comando nuevo.

//*		Tener un historial funcional.

//*		Busca y ejecuta el ejecutable correcto (basado en la variable PATH o mediante el uso de rutas relativas o absolutas).
//*		Implantar los builtins

//TODO	Unificar los builtins y llamar con punteros de funcion?
//TODO	Ver que se puedan redirigir bien los builtins con las tuberias

//!		HACER PRUEBAS CON BUILTINS Y DISTINTAS COMBINACIONES

//*		’ inhibiendo toda interpretación de una secuencia de caracteres
//*		" inhibiendo toda interpretación de una secuencia de caracteres excepto $

//TODO	< debe redirigir input.
//TODO	> debe redirigir output.
//TODO	“<<” debe leer del input de la fuente actual hasta que una línea que contenga solo el delimitador aparezca. No necesita actualizar el historial.
//TODO	“>>” debe redirigir el output en modo append
//!		Estan metidos en el lexer pero no en el parser

//*		Pipes. El output de cada comando en la pipeline se conecta a través de un pipe al input del siguiente comando

//*		Las variables de entorno ($ seguidos de caracteres) deberán expandirse a sus valores
//TODO	$? deberá expandirse al estado de salida del comando más reciente ejecutado en la pipeline

//TODO	ctrl-C ctrl-D ctrl-\ deberán funcionar como en bash
//TODO	Cuando sea interactivo: ctrl-C imprime una nueva entrada en una línea nueva.
//TODO	Cuando sea interactivo: ctrl-D termina el shell.
//TODO	Cuando sea interactivo: ctrl-\ no hace nada

