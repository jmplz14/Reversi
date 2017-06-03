#ifndef _JUGADOR_H
#define _JUGADOR_H 
#include "tablero.h"
#include <iostream>
class Jugador{
	private:
		char *nombre;
		int puntos, turno, p_ganadas;
		void limpiarEntrada(std::istream& is) const;		
		bool dialogoEscoger(std::istream& is, std::ostream& os, Tablero& tablero) const;
	public:
		Jugador(const char datos[], int ficha = 1);
		~Jugador();
		Jugador(const Jugador& j);
		Jugador& operator=(const Jugador& j);
		int getPuntos() const;
		int getTurno() const;
		int getGanadas() const;
		void setPuntos(int n);
		void setGanadas(int n);
		void setTurno(int n);
		void sumarPuntuacion(const Tablero& tablero);
		void cambiarNombre(const char datos[]);
		const char* getNombre() const;
		bool escogerPosicion(std::istream& is, std::ostream& os, Tablero &tablero) const;
		friend std::ostream& operator<< (std::ostream& os, const Jugador& j);
		friend std::istream& operator>> (std::istream& is, Jugador& j);
		
};

#endif