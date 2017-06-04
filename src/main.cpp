#include "tablero.h"
#include "jugador.h"
#include "matriz.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cstring>
using namespace std;
char const cabecera[22] = "#MP-SUPER-REVERSI-1.0" ;
void limpiarCin(std::istream& is){
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(),'\n');
}
char dialogoSalvar(istream& is, ostream& os){
	char guardar;
	os << endl << "¿Quiere guardar la partida (s o n)? ";
	is >> guardar; 
	while ( (guardar != 's' && guardar != 'n') || !is){
		limpiarCin(is);							
		os << "Error introduzca s o n: ";
		is >> guardar;
	}
	return guardar;
}

void salvar(istream& is, ostream& os, const Tablero& t, const Jugador& j1, const Jugador& j2, int n_partidas ){
	const int tamano=255;
	char fichero[tamano];
	std::ofstream f;
	os << "Introduzca el nombre del archivo: ";
	is.ignore();
	is.getline(fichero, tamano , '\n');
	f.open(fichero);
	while(!f){
		limpiarCin(cin);
		os << "Introduzca un nombre de archivo valido: ";
		cin.getline(fichero, tamano , '\n');
		f.open(fichero);
	}
	f << cabecera << std::endl;
	f << t << std::endl;
	f << j1 << std::endl;
	f << j2 << std::endl;
	f << n_partidas << std::endl;
	
}
bool cargar(Tablero& t, Jugador& j1, Jugador& j2, char fichero[], int& partidas ){
	bool estado = true;
	int const tamano=1024;
	char cabecera_f[tamano];
	
	ifstream f(fichero);
	if (f){
		f.getline(cabecera_f, tamano , '\n');
		if(strcmp(cabecera_f, cabecera) == 0){
			f >> t;
			f >> j1;
			f >> j2;
			f >> partidas;
		}else{
			estado = false;
		}
		f.close();
	}else{
		estado=false;
	}
	
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
	os << j.getNombre() << ": " << j.getGanadas() << " ganadas que acumulan " << j.getPuntos() << " puntos"<< endl ;
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
int main(int argc, char* argv[]){
	
	int const tamano=1024;
	char n1[tamano], n2[tamano], nueva_partida, guardar;
	int fil ,col, ganador, n_partidas = 0;
	bool estado = true, parada;
	cout << n_partidas;
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
			cin.getline(n1,tamano,'\n');
			if (cin){
				Jugador j1(n1,1);		
				cout << "Introduzca el nombre del jugador 2: ";
				cin.getline(n2,tamano,'\n');
				
//				cin.getline(n2,numeric_limits<streamsize>::max());
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
							while ( (nueva_partida != 's' && nueva_partida != 'n') || !cin){
								limpiarCin(cin);							
								cout << "Error introduzca s o n: ";
								cin >> nueva_partida;
							}
						}else{
							guardar = dialogoSalvar(cin,cout);
							if (guardar == 's'){
								salvar(cin,cout,t,j1,j2,n_partidas);
							}						
							
						
						}
						t.vaciarTablero();
									
					}while(!parada && nueva_partida == 's');
					//Se deja que se muestren los resultados aunque se paren o se muestren
					//para ver como iva la partida
					resultadosFinales(cout,j1, j2, n_partidas);
					guardar = dialogoSalvar(cin,cout);
					if (guardar == 's'){
							salvar(cin,cout,t,j1,j2,n_partidas);
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
	
	
	
	
	
	
	
	
	
	