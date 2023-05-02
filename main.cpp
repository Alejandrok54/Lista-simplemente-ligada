#include <iostream>

#include "socio.hpp"

template<class T>
class LSLSE;

template<class T>
class node {
    private:
        T data;
        node<T>* sig;
    public:
        node():sig(nullptr) {};
        friend class LSLSE<T>;
    };

template<class T>
class LSLSE {
    private:
        node<T>* lista;
    public:
        LSLSE():lista(nullptr) {};
        bool vacia()const;
        node<T>* ultimo()const;
        node<T>* primero()const;
        node<T>* anterior(node<T>* pos)const;
        void insertar(node<T>* pos, T elem);
        bool eliminar(node<T>* pos);
        node<T>* localiza(T elem);
        void localizaPorNomDom(T elem);
        node<T>* obtenerPosOrd(T elem);
        int obtenerTotaldeSocios() const;
        void imprimir()const;
        std::string toString() const;
    };

template<class T>
void LSLSE<T>::imprimir()const {
    node<T>* aux=lista;
    while(aux!=nullptr) {
        std::cout<<aux->data.toString()<<"-> ";
        aux=aux->sig;
        }
    }

template<class T>
bool LSLSE<T>::eliminar(node<T>* pos) {
    if(vacia() || pos==nullptr) {
        return false;
        }
    if(pos==lista) {
        lista=lista->sig;
        }
    else {
        anterior(pos)->sig=pos->sig;
        }
    delete pos;
    return true;
    }

template<class T>
void LSLSE<T>::insertar(node<T>* pos, T elem) {
    node<T>* aux= new node<T>;
    aux->data=elem;
    if(pos==nullptr) {
        aux->sig=lista;
        lista=aux;
        }
    else {
        aux->sig=pos->sig;
        pos->sig=aux;
        }
    }

template<class T>
node<T>* LSLSE<T>::localiza(T elem) {
    node<T>* aux(lista);
    while(aux!=nullptr and !(aux->data == elem)) {
        aux = aux->sig;
        }

    return aux;
    }

template<class T>
void LSLSE<T>::localizaPorNomDom(T elem) {
    node<T>* aux(lista);
    while(aux!=nullptr and !(aux->data.getNombreSocio() == elem.getNombreSocio() && aux->data.getDomicilio() == elem.getDomicilio())) {
        aux = aux->sig;
        }

    if(aux!=nullptr) {
        std::cout<<"Socio Encontrado"<<std::endl;
        std::cout<<aux->data.toString()<<std::endl;
        }
    else {
        std::cout<<"Socio no Encontrado"<<std::endl<<std::endl;
        }
    }

template<class T>
node<T>* LSLSE<T>::obtenerPosOrd(T elem) {
    if(vacia()){
        return nullptr;
    }

    node<T>* aux(lista);
    while(aux->data < elem) {
        if(aux->sig == nullptr)
            return aux;

        aux = aux->sig;
        }

    return aux;
    }

template<class T>
int LSLSE<T>::obtenerTotaldeSocios() const {
    int i(0);
    node<T>* aux(lista);
    while(aux!=nullptr) {
        i++;
        aux = aux->sig;
        }

    return i;
    }



template<class T>
node<T>* LSLSE<T>::anterior(node<T>* pos)const {
    if(vacia() || pos==nullptr) {
        return nullptr;
        }
    node<T>* aux=lista;
    while(aux!=nullptr && aux->sig!=pos) {
        aux=aux->sig;
        }
    return aux;
    }

template<class T>
node<T>* LSLSE<T>::primero()const {
    if(vacia()) {
        return nullptr;
        }
    return lista;
    }


template<class T>
node<T>* LSLSE<T>::ultimo()const {
    if(vacia()) {
        return nullptr;
        }
    node<T>* aux=lista;
    while(aux->sig!=nullptr) {
        aux=aux->sig;
        }
    return aux;
    }

template<class T>
bool LSLSE<T>::vacia()const {
    if(lista==nullptr)
        return true;
    return false;
    }

template<class T>
std::string LSLSE<T>::toString() const {
    std::string s;
    node<T>* aux=lista;
    s+="\nNumero\tNombre\tDomicilio\t\tAnio\n\n";
    while(aux!=nullptr) {
        s+=aux->data.toString();
        aux=aux->sig;
        }

    return s;
    }


int main() {
    LSLSE<Socio> milista;
    Socio s;
    int op, aux;
    std::string auxs;

    do {
        std::cout<<std::endl<<std::endl;
        std::cout<<"Ingrese una opcion: "<<std::endl;
        std::cout<<"1. Registrar nuevo socio "<<std::endl;
        std::cout<<"2. Dar de baja un socio "<<std::endl;
        std::cout<<"3. Generar un reporte "<<std::endl;
        std::cout<<"4. Buscar socio por nombre y domicilio "<<std::endl;
        std::cout<<"5. Total de socios registrados "<<std::endl;
        std::cout<<"6. Salir "<<std::endl;
        std::cin>>op;


        switch(op) {
            case 1:
                std::cin>>s;
                if(milista.localiza(s) == nullptr) {
                    milista.insertar(milista.obtenerPosOrd(s),s);
                    }
                else {
                    std::cout<<std::endl<<"Numero de Socio Invalido"<<std::endl;
                    }
                break;
            case 2:
                std::cout<<"Ingrese el numero de socio: "<<std::endl;
                std::cin>>aux;
                s.setNumeroSocio(aux);
                if(milista.eliminar(milista.localiza(s))) {
                    std::cout<<"Eliminado con exito"<<std::endl;
                    }
                else {
                    std::cout<<"error al eliminar\n"<<std::endl;
                    }
                break;
            case 3:
                std::cout<<milista.toString();
                std::cout<<std::endl;
                milista.imprimir();
                std::cout<<std::endl;
                break;
            case 4:
                std::cout<<"Ingrese el nombre del socio: "<<std::endl;
                std::cin>>auxs;
                s.setNombreSocio(auxs);
                std::cout<<"Ingrese el domicilio del socio: "<<std::endl;
                std::cin>>auxs;
                s.setDomicilio(auxs);
                milista.localizaPorNomDom(s);

                break;
            case 5:
                std::cout<<"Total de Socios: ";
                std::cout<<milista.obtenerTotaldeSocios()<<std::endl<<std::endl<<std::endl;
                break;
            case 6:
                break;
            }
        }while(op!=6);
    return 0;
    }
