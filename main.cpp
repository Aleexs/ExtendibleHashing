#include "extendible.h"
#include <iostream>

void menu(){
    std::cout<<"\nMenu:\n";
    std::cout<<"1)Insert: \n";
    std::cout<<"2)Find: \n";
    std::cout<<"3)Remove: \n";
    std::cout<<"4)Print: \n";
    std::cout<<"0 Salir: \n";
    std::cout<<"Opcion: ";
}

int main(){
    int bucketSize = 3;
    ExtendibleHashing hashTable(bucketSize);
    int opc, valor;

    do{
        menu();
        std::cin>>opc;

        switch (opc){
            case 1:
                std::cout<<"VAlor: ";
                std::cin>>valor;
                hashTable.insert(valor);
                break;
            case 2:
                std::cout<<"Find Valor: ";
                std::cin>>valor;
                if (hashTable.find(valor)){
                    std::cout<<valor<<" encontrado\n"; //true
                } else{
                    std::cout<<valor<<" no encontrado\n";
                }
                break;
            case 3:
                std::cout<<"Remove valor: ";
                std::cin>>valor;
                hashTable.remove(valor);
                break;
            case 4:
                hashTable.print();
                break;
            case 0:
                break;
            default:
                std::cout<<"Opcion incorrecta\n";
        }
    } while (opc != 0);

    return 0;
}
