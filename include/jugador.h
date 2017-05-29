#ifndef _JUGADOR_H
#define _JUGADOR_H 
#include "tablero.h"
class Jugador{
	private:
		char nombre[50];
		int puntos, turno, p_ganadas;
	
		bool dialogoEscoger(std::istream& is, std::ostream& os, Tablero& tablero);
	public:
		Jugador(const char datos[], int ficha);
		int getPuntos() const;
		int getTurno() const;
		void setTurno(int n);
		void sumarPuntuacion(const Tablero& tablero);
		void cambiarNombre(const char datos[]);
		const char* getNombre() const;
		bool escogerPosicion(std::istream& is, std::ostream& os, Tablero &tablero);
		
};

#endif