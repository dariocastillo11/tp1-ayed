#include <iostream>
using namespace std;

// Clase para expresion entre { JSON-AYED }
/*
//template se usa en clases genericas objetos como parametros. a diferencia de no usarlo que es
//cuando se trabaja solo con int o string. 

template<class T> class parentesisJson{
private:
    parentesisJson() {} 
public:
};

*/
class parentesisJson{
private:
    
public:
    parentesisJson() {} //constructor
    ~parentesisJson();//destructor
};



// Clase para expresión llave : valor
class llaveValor {
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
    ~ llaveJson();
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
    T dato;
public:
    Validacion();
    ~Validacion();
    void esCorrecto(T);
    
};
//un ej
template <class T> void Validacion<T>::esCorrecto(T d) {
        cout<<"Formato JSON validado correctamente"<<endl;
        cout<<"dato: "<<d;
         };
         

int main()
{
    
    validador = new Validacion();
    string c;//en teoria no se si es correcto las variables globales en este tp
    cout << "ingrese archivo json" << endl;
    cin>>c;
    //cout<<"el valor ingresado es: "<<c<<endl;
    validador.esCorrecto(c);
    system("PAUSE");
    return EXIT_SUCCESS;

}