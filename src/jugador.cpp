#include "tablero.h"
#include "jugador.h"
#include <iostream>
#include <assert.h>
#include <limits>
Jugador::Jugador(const char datos[], int ficha) {
	assert( (ficha == 1 || ficha == 2) );
	cambiarNombre(datos);
	p_ganadas = 0;
	puntos = 0;
	turno = ficha;
}
void Jugador::sumarPuntuacion(const Tablero& tablero){
	int puntuacion = tablero.obtenerPuntuacion(turno) ,  ganador =tablero.obtenerGanador() ;
	puntos += puntuacion;
	p_ganadas = ganador == turno ? p_ganadas + 1 : p_ganadas;
	
}
int Jugador::getGanadas() const{
	return p_ganadas;
}
int Jugador::getPuntos() const{
	return puntos;
}
int Jugador::getTurno() const{
	return turno;
}
void Jugador::cambiarNombre(const char datos[]){
	int cont = 0;
	while (datos[cont] != '\0'&& cont < 49){
		nombre[cont] = datos[cont];
		cont++;
	}
	nombre[cont] = '\0';
}
const char* Jugador::getNombre() const{
	//const char* inicio = nombre;
	return nombre;
}
//no se hace funcion bool porque esta funcion entra en bucle siempre que la posicion insertada se erronea de modo que nunca
//se tendra una posicion invalida introducida por el usuario al final de la funcion ni tendremos ningun tipo de error
void Jugador::escogerPosicion(std::istream& is, std::ostream& os, Tablero& tablero) const {
	assert ( !tablero.estadoTablero() && tablero.turnoActual() == turno );
	//no tengo que hacer comprobacion de si se hay una posicion libre en la que poder colocar
	//la ficha porque si nuestra clase tablero si no puediera mover ningun jugador finalizacia el tablero
	int cols = tablero.getCols(); 
	int fils = tablero.getFils();
	int fil_valida, numero_posibilidades = 0;
	char col_valida = 'a',col_cont = 'a';
	
	bool encontrada;
	
	for (int i = 0 ; i < fils && numero_posibilidades < 2; i++){
		for(int j = 0; j < cols && numero_posibilidades < 2 ; j++){
			col_cont += j;
			encontrada=tablero.consultarPosicion(col_cont, i);
			if (encontrada){
				fil_valida = i;
				col_valida = col_cont;
				numero_posibilidades++;
			}
			col_cont = 'a';
		}
	}
	//como minimo siempre tedremos un movimiento puesto que sino nuestra clase tablero no lo pondria como turno actual y 		pasaria al otro jugador.
	if (numero_posibilidades == 1){
		tablero.colocarFicha(col_valida, fil_valida);
		os << nombre << ", solo tenia un movimiento valido("<< col_valida << fil_valida <<")";
	}else{
		dialogoEscoger(is, os, tablero);
			
	}
}
void Jugador::limpiarEntrada(std::istream& is) const {
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

void Jugador::dialogoEscoger(std::istream& is,std::ostream& os, Tablero& tablero) const{
	bool estado;
	int fil;
	char col_max = 'a',col;
	col_max += tablero.getCols()-1; 
	os << std::endl << getNombre() << ", escoja una columan (letra a-" << col_max << ") y una fila (0-" << tablero.getFils()-1 << "): ";
	is >> col;
	is >> fil;
	if(is){
		estado = tablero.consultarPosicion(col,fil);
	}else{
		estado = false;
		limpiarEntrada(is);
	}
	while (!estado){
		os << "Introduza una posicion valida: ";
		is >> col;
		is >> fil;
		if (is){
			estado = tablero.consultarPosicion(col,fil);			
		}else{
			estado=false;
			limpiarEntrada(is);
		}
		
	}
	// limpiamos la entrada para que en caso de que el jugador metiera una doble posicion no se guradara para el sigueinte 
	//turno y pudiera colocar una ficha en el turno del siguiente jugador;
	//con doble posicion me refiero a por ejemplo que ponga en la entrada a1b3 por lo cual en su turno se usaria la poscion a1
	//y en el siguiente se usaria la posicion b3
	//no lo hago con el is.eof() porque eso obliga a tener que introducir un ctrl+d al usuario al meter la posicion
	limpiarEntrada(is);
	tablero.colocarFicha(col, fil);
	
}
void Jugador::setTurno(int n){
	assert( n == 1 || n == 2);
	turno = n;
}	
	
			
			
			
			
			
			
			
			