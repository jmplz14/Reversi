#include "tablero.h"
#include "jugador.h"
#include <iostream>
#include <assert.h>
Jugador::Jugador(const char datos[], int ficha) {
	int cont = 0;
	while (datos[cont] == ' ' || datos[cont] != '\0')
		cont++;
	assert( (ficha == 1 || ficha == 2) && datos[cont] != '\0');
	for (int i = 0; datos[cont] != '\0' && i < 50; i++, cont++ ){
		nombre[i]=datos[cont];
	}
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