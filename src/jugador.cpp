#include "tablero.h"
#include "jugador.h"
#include <iostream>
#include <assert.h>
Jugador::Jugador(const char datos[], int ficha) {
	assert( (ficha == 1 || ficha == 2) && datos[0] != '\0');
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
	}
	nombre[cont] = '\0';
}
const char* Jugador::getNombre() const{
	//const char* inicio = nombre;
	return nombre;
}
void Jugador::escogerPosicion(std::istream& is, std::ostream& os, Tablero& tablero){
	assert ( tablero.estadoTablero() && tablero.turnoActual() != turno );
	//no tengo que hacer comprobacion de si se hay una posicion libre en la que poder colocar
	//la ficha porque si nuestra clase tablero si no puediera mover ningun jugador finalizacia el tablero
	int cols = tablero.getCols(); 
	int fils = tablero.getFils();
	int fil_valida, numero_posibilidades = 0;
	char col_valida = 'a';
	bool estado;
	
	for (int i = 0 ; i < fils && numero_posibilidades < 2; i++){
		for(int j = 0; i < cols && numero_posibilidades < 2 ; j++){
			estado=tablero.posibilidadMovimiento(turno);
			if (estado){
				fil_valida = i;
				col_valida += j;
				numero_posibilidades++;
			}
		}
	}
	if (numero_posibilidades == 1){
		tablero.colocarFicha(col_valida, fil_valida);
				
	}else{
		dialogoEscoger(is, os, tablero);
	}
	tablero.escribir(os);	
	
}	
void Jugador::dialogoEscoger(std::istream& is,std::ostream& os, Tablero& tablero){
	bool estado;
	int fil;
	char col_max = 'a',col;
	col_max += tablero.getCols(); 
	os << std::endl << nombre << ", escoja una columan (letra a-" << col_max << ") y una fila (0-" << tablero.getFils() << "): ";
	is >> col;
	is >> fil;
	estado = tablero.consultarPosicion(col,fil);

	while (!estado){
		os << "Introduza una posicion valida: ";
		is >> col;
		is >> fil;
		estado = tablero.consultarPosicion(col,fil);
	}
	tablero.colocarFicha(col, fil);

	
}
	
	
			
			
			
			
			
			
			
			