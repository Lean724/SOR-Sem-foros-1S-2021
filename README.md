# Reentrega Trabajo Práctico Semáforos.

#### Introduccion:
Luego de las devoluciones realizadas por los docentes, tuve que ponerme a revisar conceptos que no entendia, empece por enteder como armar un readme, debido a que el anterior estaba hecho practicamente "asi no mas" luego tuve que pedir acceso al repoUNGS debido a que no visualizaba los videos. Siguiendo los videos de Howto, plantie el ejercicio utilizando los conceptos de paralelimso y secuencia que se dieron en los 3 ejercicios del howto, ya con el tercero, me di cuenta previamente habia encarado el ejercicio pensando en los equipos y no en las tareas que se deben realizar, sumado a que no entendia los threads, hizo que el resultado fuera totalmente distinto al esperado.

****
### Esquema de semaforos:

Basandome en el Howto del repo, tome en cuenta que los equipos son 4 y los semaforos van directo a las acciones.
Al tener 8 acciones, obtengo 8 semaforos.

Entonces: 

p()->wait() 
v()->signal(). 

Equipo 1
Equipo 2
Equipo 3
Equipo 4


- S_1=0  -->semaforoCortar
- S_2=0  -->semaforoArmar      
- S_3=0  -->semaforoMezclarIngredientes     
- S_4=0  -->semaforoUsarElemento
- S_5=0  -->semaforoParaCocinar
- S_6=0  -->semaforoParaHornear
- S_7=0  -->semaforoAgregar
- S_8=0  -->semaforoEmpanar

No obstante, como hay algunas cosas como por ejemplo el horno que no pueden ser ocupados por mas de un equipo, entonces tuve dificultades para que se pudiera seguir la receta con solo estos 8 semaforos.
Basado en el tercer Howto de semaforos, utilizo 3 semaforos auxiliares, para poder coordinar los equipos que solamente pueden ocupar el horno o realizar una sola accion.

- semaforoAUX1=1
- semaforoAUX2=1
- semaforoAUX3=2

### Escribir y leer archivos

La realidad es que nunca programe en C y en los videos del Howto (en la parte de las aclaraciones del tp) decia que debiamos buscar una manera de leer archivos, con lo cual me base en la web [Aprender a Programar](https://www.aprenderaprogramar.com/index.php?option=com_content&view=article&id=936:escribir-guardar-datos-en-ficheros-o-archivos-en-lenguaje-c-fputc-putc-fputs-fprintf-ejemplos-cu00537f&catid=82&Itemid=210)

#### Conclusion:

La primera conclusion que saco, es que si bien el tp fue (par mi que nunca programe en c) bastante complejo, ayuda a comprender mucho mas como funcionan los semaforos, porque si bien los ejercicios vistos en clase o los que estan en el repo sirven para tener una noción basica, es distinto ponerse a programarlo y ver por ejemplo que S_6 se ejecuta a diestra y siniestra cuando tiene que tener una restriccion, entonces sabes que te falto un semaforo auxiliar. 
