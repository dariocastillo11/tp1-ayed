#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Valor;       // clase abstracta para los otros que heredan
class ClaveValor;  // un par con una string y un valor de cualquiera de los que siguen
class ValorString; // cualquier texto entre dos comillas
class ValorLista;  // cualquier cantidad de valores dentro de []
class ValorObjeto; // cualquier cantidad de pares entre {} separado por ,

template <class T>
class Nodo
{
private:
    T dato;
    Nodo *next;

public:
    Nodo() { next = NULL; };
    Nodo(T a)
    {
        dato = a;
        next = NULL;
    };
    void set_dato(T a) { dato = a; };
    void set_next(Nodo *n) { next = n; };
    T get_dato() { return dato; };
    Nodo *get_next() { return next; };
    bool es_vacio() { return next == NULL; }
};

template <class T>
class Lista
{
private:
    Nodo<T> *czo;
    void addO(T d, Nodo<T> *ant);
    void borrarD(T d, Nodo<T> *ant);

public:
    Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T> *n) { czo = n; };
    //~Lista(void);
    void add(T d); // sumar nodos a la lista
    bool esvacia(void);
    T cabeza(void);     // retorna el dato del primer nodo
    Lista *resto(void); // retorna el puntero al "resto" de la lista
                        // resto= lo que queda de la lista sin la cabeza
    string toPrint(string p);
    void impre(void);
    T suma(T i);
    int size();
    bool esta(T d);                            // detecta si d esta en la lista
    void borrarDato(T d) { borrarD(d, NULL); } // borra el nodo que contiene d
    void borrar(void);                         // borra la cabeza
    void borrar_last();                        // borra el ultimo
    void concat(Lista<T> *l1);                 // le transfiere los datos de l1 a this
    Lista<T> *copy(void);                      // hace una copia de la lista
    void tomar(int n);                         // deja "vivos" los n primeros nodos y borra el resto
    void addOrdenado(T d) { addO(d, NULL); };  // sumar nodos a la lista Ordenados de menor a MAYOR
    T last();                                  // retorna el dato del ultimo nodo
};
template <class T>
T Lista<T>::last()
{
    if (!this->esvacia())
    {
        if (this->resto()->esvacia())
            return this->cabeza();
        return this->resto()->last();
    }
    return NULL;
}
template <class T>
void Lista<T>::add(T d) // 100
{
    Nodo<T> *nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}
template <class T>
bool Lista<T>::esvacia(void)
{
    return czo->es_vacio();
}
template <class T>
T Lista<T>::cabeza(void)
{
    if (this->esvacia())
    {
        throw std::runtime_error("Error, Cabeza de lista vacia");
    }
    return czo->get_dato();
}

template <class T>
Lista<T> *Lista<T>::resto(void)
{
    Lista *l = new Lista(czo->get_next());
    return (l);
}

template <class T>
string Lista<T>::toPrint(string p)
{
    if (this->esvacia())
    {
        return p;
    }
    else
    {
        // std::ostringstream stm;
        ostringstream stm;
        stm << this->cabeza() << "-" << this->resto()->toPrint(p) << endl;
        // cout<<endl<<" stm.str()= "<<stm.str()<<endl;
        return stm.str();
    }
}

template <class T>
T Lista<T>::suma(T i)
{ // cout<<" i al entrar= "<<i<<endl;
    if (this->esvacia())
    {
        return i;
    }
    else
    {

        return this->resto()->suma(i + this->cabeza());
    }
}

template <class T>
int Lista<T>::size()
{
    if (this->esvacia())
        return 0;
    return 1 + this->resto()->size();
}

template <class T>
void Lista<T>::borrar(void)
{ // borra el nodo cabeza
    if (!this->esvacia())
    {
        Nodo<T> *tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}

template <class T>
void Lista<T>::borrar_last()
{ // borra el ultimo nodo
    if (!this->esvacia())
    {
        if ((czo->get_next())->get_next() == NULL)
        {
            delete czo->get_next();
            czo->set_next(NULL);
        }
        else
            this->resto()->borrar_last();
    }
}

template <class T>
void Lista<T>::concat(Lista<T> *l1)
{ // le transfiere los datos de l1 a this
    if (!(l1->esvacia()))
    {
        this->concat(l1->resto());
        this->add(l1->cabeza());
    }
}

template <class T>
Lista<T> *Lista<T>::copy(void)
{
    Lista<T> *aux = new Lista();
    aux->concat(this);
    return aux;
}

template <class T>
void Lista<T>::tomar(int n)
{ // deja "vivos" los n primeros nodos y borra el resto
    if (this->size() > n)
    {
        this->borrar_last();
        this->tomar(n);
    }
}

template <class T>
void Lista<T>::impre(void)
{
    Nodo<T> *aux;
    aux = czo;
    while (aux->get_next() != NULL)
    {
        cout << aux->get_dato() << endl;
        aux = aux->get_next();
    }
}

template <class T>
void Lista<T>::addO(T d, Nodo<T> *ant)
{
    if (this->esvacia())
    { // el primero
        this->add(d);
    }
    else
    {
        if (d < czo->get_dato())
        {
            if (ant == NULL)
            { // al principio
                this->add(d);
            }
            else
            { // entre medio
                Nodo<T> *nuevo = new Nodo<T>(d);
                nuevo->set_next(ant->get_next());
                ant->set_next(nuevo);
            }
        }
        else
        {
            if ((czo->get_next())->get_next() == NULL)
            { // al final
                Nodo<T> *nuevo = new Nodo<T>(d);
                nuevo->set_next(czo->get_next());
                czo->set_next(nuevo);
            }
            else
                this->resto()->addO(d, czo);
        }
    }
}

template <class T>
bool Lista<T>::esta(T d)
{ // busca d en la lista
    if (this->esvacia())
        return false;
    if (this->cabeza() == d)
        return true;

    return this->resto()->esta(d);
}

template <class T>
void Lista<T>::borrarD(T d, Nodo<T> *ant)
{
    if (!this->esvacia())
    {
        if (d == this->cabeza())
        {
            if (ant == NULL)
            { // al principio
                this->borrar();
            }
            else
            { // entre medio
                ant->set_next(czo->get_next());
                delete czo;
            }
        }
        else
            this->resto()->borrarD(d, czo);
    }
}
//------------^todo lo de listas^---------------------------------

//-------------------------------------------------->pila<----------------------------------------------------------------------
template <class T>
class Pila : public Lista<T>
{
public:
    Pila() { Lista<T>(); };
    void apilar(T d) { this->add(d); };           // agrega un bloque a la pila
    T tope(void) { return this->cabeza(); };      // la pila que esta mas arriba
    void desapilar(void) { this->borrar(); };     // elimina el bloque de mas arriba
    bool pilavacia() { return this->esvacia(); }; // devuelve si es o no vacia la pila
};

//---------------------------------------------------pila--------------------------------------------------------------------------

//-------------------------------------------------->cola<----------------------------------------------------------------------
template <class T>
class Cola : public Lista<T>
{
public:
    Cola(void) { Lista<T>(); };
    T tope() { return this->last(); };
    bool colavacia(void) { return this->esvacia(); };
    void encolar(T a) { this->add(a); };
    void desencolar(void) { this->borrar_last(); };
    T ultimo(void) { return this->cabeza(); };
    string imprimir(string s) { return this->toPrint(s); };
};

//---------------------------------------------------cola--------------------------------------------------------------------------

struct charPos
{
    char caracter;
    int pos;
};

class Valor
{
public:
    virtual ~Valor() {}
    virtual string toString() =0 ;
};
void printError(int posicion, string texto)
{
    int inicio;
    int fin;

    if (posicion < 20)
    {
        inicio = 0;
    }
    else
    {
        inicio = posicion - 20;
    }
    if (posicion + 20 < texto.length())
    {
        fin = posicion + 20;
    }
    else
    {
        fin = texto.length();
    }

    int preFlecha = inicio;
    int postFlecha = fin;
    int posCopia = posicion;

    for (; inicio < posicion; inicio++)
    {
        cout << texto[inicio];
    }
    cout << texto[posicion];
    posicion++;
    
    for (; posicion < fin; posicion++)
    {
        cout << texto[posicion];
    }
    cout << endl;

    for (; preFlecha < posCopia; preFlecha++)
    {
        cout << '_';
    }
    cout << "^";
    posicion++;
    for (; posCopia < fin; posCopia++)
    {
        cout << '_';
    }
    cout << endl;
    exit(0);
}


class ValorString : public Valor
{ // detecta un valor entre comillas
private:
    string valor;

public:
    ValorString() { valor = ""; };
    ValorString(string texto, int &posicion){
        {int inicio = posicion;
    Pila<char> *p1 = new Pila<char>();
    p1->apilar('"');
    for (; texto[posicion] != '\0'; (posicion)++)
    {
        if (texto[posicion] == '"')
        {
            p1->desapilar();
            break;
        }
        else
        {
            valor += texto[posicion];
        }
    }
    if (!p1->pilavacia())
    {
        cout << "cierre comillas no encontrado para: " << inicio << endl;
        printError(inicio, texto);
    }
    (posicion)++; // saltar el ultimo "
}
}
;
~ValorString(){};

string toString() { return "\"" + valor + "\""; };
};

class ValorLista : public Valor
{
private:
    Cola<ValorString *> valores;

public:
    ValorLista(string texto, int &posicion)
    {
        {
            Pila<charPos> *p1 = new Pila<charPos>();
            int posTemp;
            p1->apilar({'[', posicion});
            p1->apilar({',', posicion});
            int inicio = posicion;
            bool cont = true;
            for (; texto[posicion] != '\0' && cont; (posicion)++)
            {
                switch (texto[posicion])
                {

                case '"':
                {
                    p1->apilar({'"', posicion});
                    (posicion)++;
                    valores.add(new ValorString(texto, posicion));
                    posicion--;
                    break;
                }

                case ',':
                    p1->apilar({',', posicion});
                    break;

                case ']':
                    cont = false;
                    p1->apilar({']', posicion});
                    break;

                case ' ':
                case '\n':
                case '\t':
                    break;

                default:
                    cout << "error texto fuera de expresion en posicion: " << posicion << endl;
                    printError(posicion, texto);
                    cont = false;
                    break;
                }
            }
            if (p1->tope().caracter != ']')
            {
                cout << "error no hay cierre (]) para la lista abierta en: " << inicio << endl;
                printError(inicio, texto);
            }
            else
            {
                p1->desapilar();
            }

            while (!p1->esvacia())
            {
                switch (p1->tope().caracter)
                {
                case '"':
                    posTemp =  p1->tope().pos;
                    p1->desapilar();
                    
                    if (p1->tope().caracter == ',')
                    {
                        p1->desapilar();
                    }
                    else
                    {
                        cout << ", faltante antes de expresion: " << posTemp << endl;
                        printError(posTemp, texto);
                    }
                    break;
                case ',':
                {
                    int p = p1->tope().pos;
                    cout << ", de mas en: " << p << endl;
                    printError(p, texto);
                    p1->desapilar();
                }
                break;
                case '[':
                    p1->desapilar();
                    break;
                default:
                    break;
                }
            }
        }
    }

    ~ValorLista(){};

    string toString()
    {
        string out = "[";
        while (!valores.esvacia())
        {
            out += valores.tope()->toString();
            valores.desencolar();
            if (!valores.esvacia())
            {
                out += ",";
            }
        }
        out += ']';
        return out;
    };
};

class ValorObjeto : public Valor
{
private:
    Cola<ClaveValor *> paresValor;

public:
    ValorObjeto(string texto, int &posicion);
    ~ValorObjeto() { cout << "temporario"; };
    string toString();
};

class ClaveValor
{
private:
    ValorString *clave;
    Valor *valor;

public:
    ClaveValor(string texto, int &posicion)
    {
        int inicio = posicion;
        for (; texto[posicion] != '\0'; (posicion)++)
        {
            if (texto[posicion] == '"')
            {
                (posicion)++;
                clave = new ValorString(texto, posicion);
                break;
            }
            else if (!(texto[posicion] == ' ' || texto[posicion] == '\t' || texto[posicion] == '\n'))
            {
                cout << "caracteres inesperados fuera de estructura reconocida en: " << posicion << " despues de: " << inicio << endl;
                printError(posicion, texto);
            }
        }
        // buscar el :
        {
            int inicio = posicion;
            Pila<char> *p1 = new Pila<char>();
            for (; texto[posicion] != '\0'; (posicion)++)
            {
                if (texto[posicion] == ':')
                {
                    p1->apilar(texto[posicion]);
                    break;
                }
                else
                {
                    if (texto[posicion] == ' ' || texto[posicion] == '\t' || texto[posicion] == '\n')
                    {
                    }
                    else
                    {
                        cout << "texto no valido despues de asignacion de clave: " << inicio << endl;
                        printError(inicio, texto);
                    };
                }
            }
            if (p1->tope() != ':')
            {
                cout << "no hay asignacion (:) para valor despues de: " << inicio << endl;
                printError(inicio, texto);
            };
            (posicion)++;
        }
        // determinar el tipo de valor
        {
            int inicio = posicion;
            bool asignado = false;
            bool cont = true;
            for (; texto[posicion] != '\0' && cont; (posicion)++)
            {
                switch (texto[posicion])
                {
                case '"':
                    (posicion)++;
                    valor = new ValorString(texto, posicion);
                    asignado = true;
                    cont = false;
                    break;
                case '{':
                    (posicion)++;
                    valor = new ValorObjeto(texto, posicion);
                    asignado = true;
                    cont = false;
                    break;
                case '[':
                    (posicion)++;
                    valor = new ValorLista(texto, posicion);
                    asignado = true;
                    cont = false;
                    break;
                case ' ':
                case '\t':
                case '\n':
                    break;

                default:
                    cout << texto[posicion] << endl;
                    cout << "error texto fuera de expresion string en posicion: " << posicion << endl;
                    printError(posicion, texto);
                break;
                }
            }
            posicion--;
            posicion--;
            if (!asignado)
            {
                cout << "valor para asignar no encotrado despues de: " << inicio<<endl;
                printError(inicio, texto);
            }
        }
    }

    string toString() { return (clave->toString() + ":" + valor->toString()); }
};

ValorObjeto::ValorObjeto(string texto, int &posicion)
{
    Pila<charPos> *p1 = new Pila<charPos>();
    p1->apilar({'{', posicion});
    p1->apilar({',', posicion});
    int posTemp;
    int inicio = posicion;
    bool cont = true;

    // encontrar expresiones y apilar simbolos estructurales
    for (; texto[posicion] != '\0' && cont; (posicion)++)
    {
        switch (texto[posicion])
        {
        case '"':
        {
            p1->apilar({'"', posicion});
            paresValor.add(new ClaveValor(texto, posicion));
        }
        break;
        case ',':
        {
            p1->apilar({',', posicion});
        }
        break;

        case '}':
        {
            p1->apilar({'}', posicion});
            cont = false;
        }
        break;
        case ' ':
            break;
        case '\n':
            break;
        case '\t':
            break;

        default:
            cout << "error texto en expresion objeto fuera de asignacion clave:valor en posicion: " << posicion << endl;
            printError(posicion, texto);
            cont = false;
            break;
        }
    }
    if (p1->tope().caracter != '}')
    {
        cout << "error no hay cierre (}) para el objeto iniciado en: " << inicio << endl;
        printError(inicio-1, texto);
    }
    else
    {
        p1->desapilar();
    }

    // revisar que simbolos estructurales esten en order y cantidad correctos
    while (!p1->esvacia())
    {
        switch (p1->tope().caracter)
        {
        case '"':
            posTemp =  p1->tope().pos;
            p1->desapilar();
            if (p1->tope().caracter == ',')
            {
                p1->desapilar();
            }
            else
            {
                cout << ", faltante antes de: " << posTemp << endl;
                printError(posTemp, texto);
            }
            break;
        case ',':
        {
            int p = p1->tope().pos;
            cout << ", de mas en: " << p << endl;
            printError(p, texto);
            p1->desapilar();
        }
        break;
        case '{':
            p1->desapilar();
            break;
        default:
            break;
        }
    }
};

string ValorObjeto::toString()
{
    {
        string out = "{";
        while (!paresValor.esvacia())
        {
            out += paresValor.tope()->toString();
            paresValor.desencolar();
            if (!paresValor.esvacia())
            {
                out += ",";
            }
        }
        out += '}';
        return out;
    };
};


string analizarJSON(string texto)
{

    int posicion = 0;

    ValorObjeto *valor;
    bool cont = true;
    for (; texto[posicion] != '\0' && cont; posicion++)
    {
        switch (texto[posicion])
        {
        case '{':
            cont = false;
            posicion++;
            valor = new ValorObjeto(texto, posicion);
            break;
        case ' ':
            break;
        case '\n':
            break;
        case '\t':
            break;
        default:
            cout << "error texto fuera de expresion entre {} en: " << posicion << endl;
            printError(posicion, texto);
            break;
        }
    }
    posicion--;

    for (; texto[posicion] != '\0'; posicion++)
    {
        switch (texto[posicion])
        {
        case ' ':
            break;
        case '\n':
            break;
        case '\t':
            break;
        default:
            cout << "error texto fuera de expresion entre {} en: " << posicion << endl;
            printError(posicion, texto);
            break;
        }
    }
    return valor->toString();
}

int main()
{
    string c;
    string salida;
    // leer el texto de un txt de entrada
    ifstream file("expresion.txt");
    if (file.is_open())
    { // si se pudo abrir

        string line;
        while (getline(file, line))
        {              // leer linea a linea
            c += line; // pegar la linea
            c += '\n'; // añadir un newline
        }
        file.close();
        salida = analizarJSON(c);
        cout << salida << endl;
        ofstream outputFile("salida.txt");
        outputFile<<salida;
        outputFile.close();
    }
    else
    {
        cerr << "No se pudo abrir el documento de texto" << endl;
    }
    exit(0);
}
