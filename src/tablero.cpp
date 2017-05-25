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

int Tablero::getPosicion(char col, int fil) const {
	int entero_cols = transformarCharCol( col );
	return matriz.getPosition( fil, col);
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
bool Tablero::comprobarCoordenadas (int fil, int col ) const { 
	return (fil >= 0 && fil < getFils() ) && ( col >= 0 && col < getCols() );
}
bool Tablero::comprobarFichaOpuesta(int ficha, int posicion) const{
	return posicion != 0 && posicion != ficha;
}

bool Tablero::recorrerMatrizCompro (int fil , int i_fils, int col , int i_cols, int ficha ) const{
	bool estado = false , dentro, opuesta;
	int posicion;
	
	//se comprueba que la primera casilla no es ni una ficha igual ni esta vacia.
	fil += i_fils; 
	col += i_cols;
	dentro = comprobarCoordenadas( fil, col );
	
	if (dentro){
		do{
			
			posicion = getPosicion( fil, col );
			opuesta = comprobarFichaOpuesta(ficha, posicion );
			fil += i_fils; 
			col += i_cols;
			dentro = comprobarCoordenadas( fil, col );
			
		}while (dentro && opuesta);
			estado = posicion == ficha ? true : false;
	}
	return estado;
}
bool Tablero::comprobarDiaSupIzq(int fil , int col, int ficha) const {
	return recorrerMatrizCompro( fil, -1 , col, -1, ficha ); 
}

bool Tablero::comprobarDiaSupDer(int fil , int col, int ficha) const{
	return recorrerMatrizCompro( fil, -1 , col, 1, ficha ); 
}

bool Tablero::comprobarDiaInfIzq(int fil , int col, int ficha) const{
	return recorrerMatrizCompro( fil, 1 , col, -1, ficha ); 
}

bool Tablero::comprobarDiaInfDer(int fil , int col, int ficha) const{
	return recorrerMatrizCompro( fil, 1 , col, 1, ficha ); 
}

bool Tablero::comprobarRecIzq(int fil , int col, int ficha) const{
	return recorrerMatrizCompro( fil, 0 , col, -1, ficha ); 
}
bool Tablero::comprobarRecDer(int fil , int col , int ficha) const{
	return recorrerMatrizCompro( fil, 0 , col, 1, ficha ); 
}

bool Tablero::comprobarRecSup(int fil , int col , int ficha) const{
	return recorrerMatrizCompro( fil, -1 , col, 0, ficha ); 
}

bool Tablero::comprobarRecInf(int fil , int col , int ficha) const{
	return recorrerMatrizCompro( fil, 1 , col, 0, ficha ); 
}



bool Tablero::comprobarDiagonales(int fil, int col, int ficha) const{
	bool estado = false;
	
	//diagonal superior hacia la derecha la fila -1 a la columna +1
	estado = comprobarDiaSupDer( fil, col, ficha ); 
	
	//diagonal superior hacia la izquierda la fila -1 a la columna -1
	if( !estado )  
		estado = comprobarDiaSupIzq( fil, col, ficha ); 			
	
	//diagonal inferior hacia la derecha la fila +1 a la columna +1
	if( !estado )  
		estado = comprobarDiaInfDer( fil, col, ficha ); 
	
	//diagonal inferior hacia la izquierda la fila +1 a la columna -1
	if( !estado )  
		estado = comprobarDiaInfIzq( fil, col, ficha ); 
	
	return estado;
}

bool Tablero::comprobarRectas(int fil, int col, int ficha) const{
	bool estado = false;
	
	// superior a la fila -1 la columna siempre igual
	estado = comprobarRecSup( fil, col, ficha ); 
	
	// inferior a la fila 1 la columna siempre igual
	if( !estado )  
		estado = comprobarRecInf( fil, col, ficha ); 			
	
	//derecha la fila siempre igual a la columna 1
	if( !estado )  
		estado = comprobarRecDer( fil, col, ficha ); 
	
	//izquierda la fila siempre igual a la columna -1
	if( !estado )  
		estado = comprobarRecIzq( fil, col, ficha ); 
	
	return estado;
}


bool Tablero::consultarPosicion(char col, int fil) const{
	int entero_col = transformarCharCol(col), ficha;
	bool estado = false;
	if ( getPosicion( col , fil ) == 0){
		ficha = turnoActual();
		estado = comprobarDiagonales( fil, entero_col, ficha );
		if ( !estado )
			estado = comprobarRectas( fil, entero_col, ficha );
				
	}
	
	return estado;
}


















