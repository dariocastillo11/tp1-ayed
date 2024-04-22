#include <iostream>
using namespace std;


//CLASE PILA
template <class T> class Nodo {
private:
    T dato;
    Nodo* next;
public:
    Nodo() { next = NULL; };
    Nodo(T a) { dato = a; next = NULL; };
    void set_dato(T a) { dato = a; };
    void set_next(Nodo* n) { next = n; };
    T get_dato() { return dato; };
    Nodo* get_next() { return next; };
    bool es_vacio() { return next == NULL; }
};

template <class T> class Lista {
private: Nodo<T>* czo;
       void addO(T d, Nodo<T>* ant);
       void borrarD(T d, Nodo<T>* ant);
public:
    Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T>* n) { czo = n; };
    //~Lista(void);
    void add(T d); //sumar nodos a la lista
    bool esvacia(void);
    T cabeza(void); //retorna el dato del primer nodo
    Lista* resto(void); //retorna el puntero al "resto" de la lista
                        //resto= lo que queda de la lista sin la cabeza
    string toPrint(string p);
    void impre(void);
    T suma(T i);
    int size();
    bool esta(T d);// detecta si d esta en la lista
    void borrarDato(T d) { borrarD(d, NULL); }//borra el nodo que contiene d
    void borrar(void); //borra la cabeza
    void borrar_last();//borra el ultimo
    void concat(Lista<T>* l1);// le transfiere los datos de l1 a this
    Lista<T>* copy(void);// hace una copia de la lista
    void tomar(int n);//deja "vivos" los n primeros nodos y borra el resto
    void addOrdenado(T d) { addO(d, NULL); }; //sumar nodos a la lista Ordenados de menor a MAYOR

};

template <class T>
void Lista<T>::add(T d) //100
{
    Nodo<T>* nuevo = new Nodo<T>(d);
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
    if (this->esvacia()) {
        cout << " Error, Cabeza de lista vacia";
        return NULL;
    }
    return czo->get_dato();
}

template <class T>
Lista<T>* Lista<T>::resto(void)
{
    Lista* l = new Lista(czo->get_next());
    return (l);
}

template <class T>
string Lista<T>::toPrint(string p)
{
    if (this->esvacia()) {
        return p;
    }
    else {
        //std::ostringstream stm;
        ostringstream stm;
        stm << this->cabeza() << "-" << this->resto()->toPrint(p) << endl;
        //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
        return stm.str();
    }
}

template <class T>
T Lista<T>::suma(T i)
{    //cout<<" i al entrar= "<<i<<endl;
    if (this->esvacia()) {
        return i;
    }
    else {

        //cout<<"this->cabeza()= "<<this->cabeza()<<endl;   
        return this->resto()->suma(i + this->cabeza());
    }
}

template <class T> int Lista<T>::size()
{
    if (this->esvacia()) return 0;
    return 1 + this->resto()->size();
}

template <class T> void Lista<T>::borrar(void)
{ //borra el nodo cabeza
    if (!this->esvacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}

template <class T> void Lista<T>::borrar_last()
{ // borra el ultimo nodo
    if (!this->esvacia()) {
        if ((czo->get_next())->get_next() == NULL) {
            delete czo->get_next();
            czo->set_next(NULL);
        }
        else this->resto()->borrar_last();
    }
}

template <class T> void Lista<T>::concat(Lista<T>* l1)
{// le transfiere los datos de l1 a this
    if (!(l1->esvacia())) {
        this->concat(l1->resto());
        this->add(l1->cabeza());
    }
}

template <class T> Lista<T>* Lista<T>::copy(void)
{
    Lista<T>* aux = new Lista();
    aux->concat(this);
    return aux;
}

template <class T> void Lista<T>::tomar(int n)
{ //deja "vivos" los n primeros nodos y borra el resto
    if (this->size() > n) {
        this->borrar_last();
        this->tomar(n);
    }
}

template <class T> void Lista<T>::impre(void)
{
    Nodo<T>* aux;
    aux = czo;
    while (aux->get_next() != NULL) {
        cout << aux->get_dato() << endl;
        aux = aux->get_next();
    }
}

template <class T>
void Lista<T>::addO(T d, Nodo<T>* ant)
{
    if (this->esvacia()) {//el primero
        this->add(d);
    }
    else {
        if (d < czo->get_dato()) {
            if (ant == NULL) {//al principio
                this->add(d);
            }
            else {//entre medio
                Nodo<T>* nuevo = new Nodo<T>(d);
                nuevo->set_next(ant->get_next());
                ant->set_next(nuevo);
            }
        }
        else {
            if ((czo->get_next())->get_next() == NULL) {//al final
                Nodo<T>* nuevo = new Nodo<T>(d);
                nuevo->set_next(czo->get_next());
                czo->set_next(nuevo);

            }
            else this->resto()->addO(d, czo);

        }
    }
}

template <class T> bool Lista<T>::esta(T d)
{// busca d en la lista
    if (this->esvacia()) return false;
    if (this->cabeza() == d) return true;
    
    return this->resto()->esta(d);    
}

template <class T>
void Lista<T>::borrarD(T d, Nodo<T>* ant)
{
    if (!this->esvacia()) {
        if (d == this->cabeza()) {
            if (ant == NULL) {//al principio
                this->borrar();
            }
            else {//entre medio
                ant->set_next(czo->get_next());
                delete czo;
            }
        }
        else  this->resto()->borrarD(d, czo);

    }
}
//------------^todo lo de listas^---------------------------------



//-------------------------------------------------->pila<----------------------------------------------------------------------
template <class T> class Pila:public Lista<T>{
      public:
             Pila(){Lista<T>();};
             void apilar(T d){this->add(d);};//agrega un bloque a la pila
             T tope(void){return this->cabeza();};//la pila que esta mas arriba
             void desapilar(void){this->borrar();};//elimina el bloque de mas arriba
             bool pilavacia(){return this->esvacia();};//devuelve si es o no vacia la pila
};  



//---------------------------------------------------pila--------------------------------------------------------------------------

template <class T> class ParentesisJson{
private:
    Pila<string> *p1;
public:
    ParentesisJson() {*p1= new Pila<string>();}; //constructor
    ~ParentesisJson();//destructor
    void deteccionCLP(string);
};

template <class T>
void ParentesisJson<T>::deteccionCLP(string cadena){
    bool error = false;
    for(int i = 0; (i<cadena.length() && (error == false)); i++){
        if(cadena.at(i) == '(') p1->apilar(cadena.at(i));
        if(cadena.at(i) == '[') p1->apilar(cadena.at(i));
        if(cadena.at(i) == '{') p1->apilar(cadena.at(i));
        if(cadena.at(i) == '{') p1->apilar(cadena.at(i));
        if(cadena.at(i) == '"') p1->apilar(cadena.at(i));
        if(cadena.at(i) == ')') {
            if(p1->tope() == '('){
                p1->desapilar();
            }else{ error = true;}
        }
        if(cadena.at(i) == ']') {
            if(p1->tope() == '['){
                p1->desapilar();
            }else{ error = true;}
        }
        if(cadena.at(i) == '}') {
            if(p1->tope() == '{'){
                p1->desapilar();
            }else{ error = true;}
        }
        if(cadena.at(i) == '"') {
            if(p1->tope() == '"'){
                p1->desapilar();
            }else{ error = true;}
        }
    }
    if(error || (p1->pilavacia())){
        cout<<"error"<<endl;
    }else{cout<<"correcto"<<endl;}
}


/*
// Clase para expresión llave : valor
class LlaveValor {
private:
    
public:
    llaveValor() {}
    ~llaveValor();
};




// Clase para expresión llave : expresión JSON-AYED
class llaveJson {
private:
    
public: 
    llaveJson() {}
    ~llaveJson();
};



// Clase para expresión llave : expresión lista de strings
class llaveLista {
private:
    
public:
    llaveLista() {}
    ~llaveLista();
};





template<class T> class Validacion{
private:
   
public:
    Validacion();
    ~Validacion();
    void Escorrecto(T);
    
};
//un ej
template <class T> void Validacion<T>::esCorrecto(T d) {
        cout<<"Formato JSON validado correctamente"<<endl;
        cout<<"dato: "<<d;
         };
*/

int main()
{
    ParentesisJson<T> *analizador;
    analizador = new ParentesisJson();
    string c;
    getline(cin, c);
    analizador->deteccionCLP(c);

    
    /*
    validador = new Validacion();
    string c;//en teoria no se si es correcto las variables globales en este tp
    cout << "ingrese archivo json" << endl;
    cin>>c;
    //cout<<"el valor ingresado es: "<<c<<endl;
    validador.Escorrecto(c);
    */
    system("PAUSE");
    return EXIT_SUCCESS;

}
