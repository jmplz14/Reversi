#ifndef _JUGADOR_H
#define _JUGADOR_H 
#include "tablero.h"
class Jugador{
	private:
		char *nombre;
		int puntos, turno, p_ganadas;
		void limpiarEntrada(std::istream& is) const;		
		bool dialogoEscoger(std::istream& is, std::ostream& os, Tablero& tablero) const;
	public:
		Jugador(const char datos[], int ficha);
		~Jugador();
		Jugador(const Jugador& j);
		Jugador& operator=(const Jugador& j);
		int getPuntos() const;
		int getTurno() const;
		int getGanadas() const;
		void setTurno(int n);
		void sumarPuntuacion(const Tablero& tablero);
		void cambiarNombre(const char datos[]);
		const char* getNombre() const;
		bool escogerPosicion(std::istream& is, std::ostream& os, Tablero &tablero) const;
		
};

#endif