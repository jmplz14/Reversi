#include "tablero.h"
#include "jugador.h"
#include <iostream>
using namespace std;
int main(){
	char n1[50], n2[50];
	int fil ,col;
	bool estado = true;
	cout << "Introduzca el numero de filas(4-10): ";
	cin >> fil;
	while( (fil > 10 || fil < 4 ) && cin){
		cout << "Introduzca el numero de filas(4-10) correctas: ";
		cin >> fil;
	}
	if (cin){
		cout << "Introduzca el numero de columnas(4-10): ";
		cin >> col;
		while((col > 10 || col < 4) && cin){
			cout << "Introduzca el numero de columnas(4-10) correctas: ";
			cin >> col;
		}
		if (cin){
			Tablero t(fil,col);
			cout << "Introduzca el nombre del jugador 1: ";
			cin.ignore();
			cin.getline(n1,50);
			if (cin){
				Jugador j1(n1,1);
				cout << "Introduzca el nombre del jugador 2: ";
				cin.ignore();
				cin.getline(n2,50);
				if (cin){	
					Jugador j2(n2,2);
					t.escribir(cout);
					while(!t.estadoTablero() && estado && cin){
						if(t.turnoActual() == 1){
							cout << "Turno del jugador 1(o)" << endl;
							estado = j1.escogerPosicion(cin,cout,t);
							t.escribir(cout);		
						}else{
							cout << "Turno del jugador 2(x)"<< endl;
							estado = j2.escogerPosicion(cin,cout,t);							
							t.escribir(cout);							
						}
					}
					if(t.estadoTablero()){
						cout << "Fin de la partida";
					}else{
						cout << "Error durante la partida" << endl;
					}
				}else{
					cout << "Error al introducir los datos del jugador2;" << endl;
				}
			
			}else{
				cout << "Error al introducir los datos del jugador 1" << endl;
			}

		}else{
			cout << "Error al introducir los datos de la columna" << endl;			
		}
	}else {
		cout << "Error al introducir los datos de la fila" << endl;
	}

}
	
	
	
	
	
	
	
	
	
	