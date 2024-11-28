# Algoritmos y Estructuras de Datos
# Enunciado Primer Parcial A˜no 2024

# Realizar un programa que eval´ue un archivo de formato JSON-AYED.

  Una expresi´on de este tipo es una expresi´on delimitada por llaves que internamente tiene subexpresiones separadas por coma, donde una subexpresi´on
es alguna de las siguientes:
Un par (llave : valor), ambos strings delimitados por comillas dobles
(”nombre”: “Carlos”)
Un par (”llave”: lista) de strings separados por coma y delimitados por
corchetes ([”string1”,..,”stringX”])
Un par (llave : subexpresion) recursivamente definida delimitada por
llaves ({})
Un ejemplo de esto es:
{
"nombre":‘‘Carlos",
"apellido":‘‘Garciarena",
"domicilio": {
‘‘calle":"San martin",
‘‘altura":‘‘33",
‘‘cuidad":‘‘Jujuy",
"telefonos":["351-4555666","351-5012789"]
},
"conyuge":"Ana Castro",
"hijos":["Ana Garciarena","Lucas Garciarena"]
}
Ud. deber´a desarrollar un programa que lea un archivo de texto que tenga
una sola expresi´on JSON-AYED, validar que sea correctamente escrita, e
imprimirla en otro archivo eliminando los espacios entre expresiones, saltos
1
de linea y tab que tenga el archivo de entrada, o bien, si no es correcta la
expresi´on de entrada, indicar donde se produjo el error en la expresi´on de
entrada.
Para el desarrollo debe basarse en los siguientes lineamientos:
Debe leer los caracteres del archivo de entrada uno a uno.
Debe utilizar estructuras de pilas y colas con ciertas especificaciones.
El archivo de salida no tiene espacios, tabs ni saltos de linea.
Debe utilizar una clase para cada tipo de componente de una expresi´on
JSON-AYED:
1. Expresi´on entre llaves ( expresi´on JSON-AYED)
2. Expresi´on llave : valor
3. Expresi´on llave : expresi´on JSON-AYED
4. Expresi´on llave : expresi´on lista de strings
   
  Cada uno de estos componentes debe tener una pila que se utilice en
la evaluaci´on de la correctitud de la expresi´on. Adicionalmente la lista de
strings debe tener una cola donde se almacenen los valores que tiene dicha
expresi´on.

  Para evaluar la expresi´on de entrada, al ir leyendo uno a uno los caracteres
del archivo se entran en ciertos “modos”de avance del proceso que definen la
validez del pr´oximo caracter a leer, por ejemplo, el validador de la expresi´on
JSON-AYED tiene una pila que esta vac´ıa al inicio de la lectura, por lo cuanto
sabe que el pr´oximo car´acter debe ser una llave que abre, y cuando lee una
llave que cierra determina que la expresi´on termin´o y tiene la pila vac´ıa. Otro
ejemplo es para leer un string, que comienza con una comilla doble, siguen
caracteres alfanum´ericos y espacios y debe terminar con otra comilla doble.

  Se aconseja que cada ”modo”tenga su propia pila para evaluaci´on. Al
cambiar de modo se activa su tipo de pila de evaluaci´on y al volver al modo
anterior se restablece el de llamada.

  Cada clase a su vez debe tener un buffer de almacenamiento donde guardar el contenido que tiene cada instancia de la respectiva clase y que se
utiliza luego al hacer la impresi´on de la expresi´on le´ıda por medio de un
m´etodo print que llame a los print de los objetos almacenados en el buffer.
Deber´a codificar la soluci´on usando Clases de C++, con m´etodos que
respeten el comportamiento definido en esta especificaci´on. Lo que no est´a
2
especificado aqu´ı es de libre elecci´on. Podr´a utilizar el c´odigo dado en clases
pr´acticas ajustando el tipo de dato contenido en cada estructura al tipo
respectivo a la clase a la cual pertenece.
