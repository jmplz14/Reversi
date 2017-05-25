#include "tablero.h"
#include "matriz.h"
int Tablero::transformarCharCol( char col ) const{
	return 'a' - col;
}

int Tablero::getFils() const{
	return matriz.getFils();
}
int Tablero::getCols() const{
	return matriz.getCols();
}
void Tablero::vaciarTablero(){
	int fils,cols,fils_centro,cols_centro;
	fils = getFils();
	cols = getCols();
	fils_centro =  fils / 2;
	cols_centro =  cols / 2;
	
	for ( int i = 0 ; i < fils ; i++ )
		for ( int j = 0 ; j < cols ; i++ )
			matriz.setPosition( i , j, 0 );
	
	matriz.setPosition( fils_centro, cols_centro, 2 );
	matriz.setPosition( fils_centro, cols_centro + 1, 1 );
	matriz.setPosition( fils_centro + 1, cols_centro, 1);
	matriz.setPosition( fils_centro + 1, cols_centro + 1, 2);
	
	n_fichas_colocadas = 4;
	turno_J1 = true;
	finalizado = false;
}

Tablero::Tablero(){
	int n = 8;
	matriz.setFils( n );
	matriz.setCols( n );
	n_fichas = n * n;
	vaciarTablero();
}

Tablero::Tablero(int n){
	matriz.setFils( n );
	matriz.setCols( n );
	n_fichas = n * n;
	vaciarTablero();
}

Tablero::Tablero(int fils, int cols){
	matriz.setFils( fils );
	matriz.setCols( cols );
	n_fichas = fils * cols;
	vaciarTablero();
}

int Tablero::getPosicion(char cols, int fils) const {
	int entero_cols = transformarCharCol( cols );
	return matriz.getPosition( fils, cols);
}

int Tablero::turnoActual() const{
	return turno_J1 == true ? 1 : 2;
}

bool Tablero::estadoTablero() const{
	return finalizado;	
}
int Tablero::obtenerPuntuacion( int jugador ) const{
	// no se puede tener un ganador con 0 fichas por lo que aunque se llamara con la partida sin Finalizar
	//no daria problemas para las puntuaciones de los jugadores al no sumarles puntos
	int puntuacion = 0;
	if ( estadoTablero() && ( jugador == 1 || jugador == 2 ) ){
		int fils = getFils();
		int cols =  getCols();
		
		for ( int i = 0; i < fils ; i++ )
			for ( int j = 0 ; i < cols; i++ )
				if ( matriz.getPosition( i, j ) == jugador )
					puntuacion++;
			
	}
	return puntuacion;
	
	

}

int Tablero::obtenerGanador() const{
	int ganador = -1;
	if ( estadoTablero() ){ 
		int fichas_1 = 0,fichas_2 = 0;

		fichas_1 = obtenerPuntuacion(1);
		fichas_2 = n_fichas_colocadas - fichas_1;

		if (fichas_1 == fichas_2 ){
			ganador = 0;
		}else{
			ganador = fichas_1 > fichas_2 ? 1 : 2;
		}
	}

	return ganador;

}



















