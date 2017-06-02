#include "tablero.h"
#include "jugador.h"
#include <iostream>
#include <limits>
using namespace std;
void limpiarCin(std::istream& is){
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(),'\n');
}
bool iniciarPartida(istream& is, ostream& os, Tablero& t,const Jugador& j1 , const Jugador& j2){
	bool parada=false;
	t.escribir(cout);	
	while(!parada && !t.estadoTablero()){
		
		
		if(t.turnoActual() == 1){
			os << "Turno del jugador 1(o)" << endl;
			parada=j1.escogerPosicion(is,os,t);
		}else{
			
			os << "Turno del jugador 2(x)"<< endl;
			parada=j2.escogerPosicion(is,os,t);							
		}
		
	}
	return parada;
}
void mostrarResultadosJugador(ostream& os, const Jugador& j){
	os << j.getNombre() << ": " << j.getGanadas() << " ganadas que acumulan " << j.getPuntos() << endl ;
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
void resultadosFinales(ostream& os, Jugador& j1, Jugador& j2, int n_partidas){
	os << "Resultados finales:" << endl;
	mostrarResultadosJugador(os,j1);
	mostrarResultadosJugador(os,j2);
	cout << n_partidas - j1.getGanadas() - j2.getGanadas() << " empatadas" << endl;
}
int main(){
	char n1[50], n2[50], nueva_partida;
	int fil ,col, ganador, n_partidas = 0;
	bool estado = true, parada;
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
			cin.getline(n1,numeric_limits<streamsize>::max());
			if (cin){
				Jugador j1(n1,1);
				cout << "Introduzca el nombre del jugador 2: ";
				cin.getline(n2,numeric_limits<streamsize>::max());
				if (cin){	
					Jugador j2(n2,2);
					do{
						
						parada = iniciarPartida(cin,cout,t,j1,j2);
							cout << "Fin de la partida: ";
						if (!parada){
							obtenerResultadosPartida(cout,t,j1,j2);
							n_partidas++;
							cout << "Introduzca una s para volver a jugar o una n para terminar y ver los resultados: ";
							cin >> nueva_partida;
							while (nueva_partida != 's' && nueva_partida != 'n' || !cin){
								limpiarCin(cin);							
								cout << "Error introduzca s o n: ";
								cin >> nueva_partida;
							}
						}
						t.vaciarTablero();
						
					}while(!parada && nueva_partida == 's');
					
						resultadosFinales(cout,j1, j2, n_partidas);
				
					
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
	
	
	
	
	
	
	
	
	
	