#ifndef _TABLERO_H
#define _TABLERO_H 
#include "matriz.h"
class Tablero{
	private:
		Matriz matriz;
		bool finalizado;
		bool turno_J1;
		int n_fichas, n_fichas_colocadas;
		int transformarCharCol( char col) const;
	public:
		Tablero();
		Tablero(int fils);
		Tablero(int fils, int cols);
		int getFils() const;
		int getCols() const;
		int getPosicion(char cols, int fils) const;
		int turnoActual() const;
		bool estadoTablero() const;
		int obtenerGanador() const;
		int obtenerPuntuacion(int jugador) const;
		bool consultarPosicion(char cols, int fils) const;
		bool posibilidadMovimiento(int jugador) const;
		bool colocarFicha(char cols, int fils);
		void vaciarTablero();
	




};
#endif