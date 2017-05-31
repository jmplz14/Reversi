#include "tablero.h"
#include "jugador.h"
#include <iostream>
#include <limits>
using namespace std;

void iniciarPartida(istream& is, ostream& os, Tablero& t,const Jugador& j1 , const Jugador& j2){
	int turno_anterior, turno;
	t.escribir(cout);
	turno_anterior =t.turnoActual();
	if( turno_anterior == 1){
			os << "Turno del jugador 1(o)" << endl;
			j1.escogerPosicion(is,os,t);
			t.escribir(cout);		
		}else{
			os << "Turno del jugador 2(x)"<< endl;
			j2.escogerPosicion(is,os,t);							
			t.escribir(cout);							
		}
	
	while(!t.estadoTablero()){
		turno = t.turnoActual();
		
		if(turno == 1){
			if (turno_anterior == turno)
				cout << j2.getNombre() << " (turno 2)no tiene ningun movimiento posible, tiene que pasar turno." << endl;
	
			os << "Turno del jugador 1(o)" << endl;
			j1.escogerPosicion(is,os,t);
			t.escribir(cout);		
		}else{
			if (turno_anterior == turno)
				cout << j1.getNombre() << " /turno 1)no tiene ningun movimiento posible, tiene que pasar turno." << endl;
			
			os << "Turno del jugador 2(x)"<< endl;
			j2.escogerPosicion(is,os,t);							
			t.escribir(cout);							
		}
		turno_anterior = turno ;
		
	}
}
void mostrarResultadosJugador(ostream& os, const Jugador& j){
	os << j.getNombre() << ": " << j.getGanadas() << "ganadas que acumlan " << j.getPuntos() << endl ;
}
void obtenerResultadosPartida(ostream& os, const Tablero& t , Jugador& j1, Jugador& j2){
	int ganador;
	ganador = t.obtenerGanador();
	j1.sumarPuntuacion(t);
	j2.sumarPuntuacion(t);
	if (ganador == 1){
		os << "Ganador: Jugador 1" << endl;
	}else if(ganador == 2){
		os << "Ganador: Jugador 2" << endl;
	}else{
		os << "¡¡¡Hay un empatee!!!"<< endl;
	}
	os << "Resultados tras esta partida:" << endl ;
	mostrarResultadosJugador(os,j1);
	mostrarResultadosJugador(os,j2);
	 
}
int main(){
	char n1[50], n2[50];
	int fil ,col, ganador;
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
				cin.getline(n2,50);
				if (cin){	
					Jugador j2(n2,2);

					iniciarPartida(cin,cout,t,j1,j2);
					cout << "Fin de la partida: ";
					obtenerResultadosPartida(cout,t,j1,j2);
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
	
	
	
	
	
	
	
	
	
	