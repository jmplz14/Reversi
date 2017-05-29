#include "tablero.h"
#include "jugador.h"
#include <iostream>
#include <assert.h>
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
bool Jugador::escogerPosicion(std::istream& is, std::ostream& os, Tablero& tablero){
	assert ( !tablero.estadoTablero() && tablero.turnoActual() == turno );
	//no tengo que hacer comprobacion de si se hay una posicion libre en la que poder colocar
	//la ficha porque si nuestra clase tablero si no puediera mover ningun jugador finalizacia el tablero
	int cols = tablero.getCols(); 
	int fils = tablero.getFils();
	int fil_valida, numero_posibilidades = 0;
	char col_valida = 'a';
	bool encontrada,estado;
	
	for (int i = 0 ; i < fils && numero_posibilidades < 2; i++){
		for(int j = 0; j < cols && numero_posibilidades < 2 ; j++){
			encontrada=tablero.posibilidadMovimiento(turno);
			if (encontrada){
				fil_valida = i;
				col_valida = j;
				numero_posibilidades++;
			}
		}
	}
	//como minimo siempre tedremos un movimiento puesto que sino nuestra clase tablero no lo pondria como turno actual y 		pasaria al otro jugador.
	if (numero_posibilidades == 1){
		tablero.colocarFicha(col_valida, fil_valida);
		os << nombre << ", solo tenia un movimiento valido("<< col_valida << fil_valida <<")";
		estado = true;			
	}else{
		estado = dialogoEscoger(is, os, tablero);
			
	}
	return estado;
}	
bool Jugador::dialogoEscoger(std::istream& is,std::ostream& os, Tablero& tablero){
	bool estado;
	int fil;
	char col_max = 'a',col;
	col_max += tablero.getCols()-1; 
	os << std::endl << nombre << ", escoja una columan (letra a-" << col_max << ") y una fila (0-" << tablero.getFils()-1 << "): ";
	is >> col;
	is >> fil;
	if(is){
		estado = tablero.consultarPosicion(col,fil);

		while (!estado && is){
			os << "Introduza una posicion valida: ";
			is >> col;
			is >> fil;
			estado = tablero.consultarPosicion(col,fil);
		}
		
		if(estado && is){
			tablero.colocarFicha(col, fil);
		}else{
			estado = false;
		}
	}
	return estado;
	
}
void Jugador::setTurno(int n){
	assert( n == 1 || n == 2);
	turno = n;
}	
	
			
			
			
			
			
			
			
			