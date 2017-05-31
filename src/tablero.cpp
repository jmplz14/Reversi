#include "tablero.h"
#include "matriz.h"
#include <assert.h>
int Tablero::transformarCharCol( char col ) const{
	return col - 'a';
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
	fils_centro =  fils / 2 - 1;
	cols_centro =  cols / 2 - 1;
		
	for ( int i = 0 ; i < fils ; i++ )
		for ( int j = 0 ; j < cols ; j++ )
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
	assert( n >= 4 && n <= 10);
	matriz.setFils( n );
	matriz.setCols( n );
	n_fichas = n * n;
	vaciarTablero();
}

Tablero::Tablero(int fils, int cols){
	assert(fils >= 4 && fils <= 10 && cols >=4 && cols <= 10 );
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
	assert ( estadoTablero() );
	
	int ganador, fichas_1 = 0,fichas_2 = 0;

	fichas_1 = obtenerPuntuacion(1);
	fichas_2 = n_fichas_colocadas - fichas_1;

	if (fichas_1 == fichas_2 ){
		ganador = 0;
	}else{
		ganador = fichas_1 > fichas_2 ? 1 : 2;
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
		posicion = matriz.getPosition( fil, col );
		opuesta = comprobarFichaOpuesta(ficha, posicion );
		if (opuesta){
			fil += i_fils; 
			col += i_cols;
			dentro = comprobarCoordenadas( fil, col );
			// se hacen la primera comprobacion para para ver que la primera ficha sea la del oponente
			if(dentro){	
				do{

					posicion = matriz.getPosition( fil, col );
					opuesta = comprobarFichaOpuesta(ficha, posicion );
					fil += i_fils; 
					col += i_cols;
					dentro = comprobarCoordenadas( fil, col );
				}while (dentro && opuesta);
				// si no se hace la primera comprobacion anteriror no podria mirar aqui si el estado es verdad o falso 
				//si la fiecha es distinta o igual a si misma al salir del bucle
				estado = posicion == ficha ? true : false;
				
			}
		}
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



bool Tablero::comprobarLineas(int fil, int col, int ficha) const{
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
	// superior a la fila -1 la columna siempre igual
	if(!estado)
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
	if ( !estadoTablero() && comprobarCoordenadas(fil , entero_col) ){
		
		if ( matriz.getPosition( fil, entero_col ) == 0 ){
			ficha = turnoActual();
			estado = comprobarLineas( fil, entero_col, ficha );
		
		}
	}
	return estado;
}
bool Tablero::posibilidadMovimiento(int jugador) const{
	assert(jugador == 1 || jugador == 2);
	bool estado = false;
	if ( !estadoTablero() ){
		int fils = matriz.getFils(), cols = matriz.getCols();
		for (int i = 0 ; i < fils && !estado ; i++){
			for (int j = 0 ; j < cols && !estado ; j++){
				if(matriz.getPosition(i,j) == 0)
					estado = comprobarLineas(i , j , jugador);
				
										
			}
		}
	}
	
	return estado;
}

void Tablero::cambiarFichas(int fil , int i_fils, int col , int i_cols, int ficha){ 
	fil += i_fils;
	col += i_cols;
	//como solo se llamara cunado estemos seguros que la diagonal o la recta es correcta
	//para el cambio solo tenemos que ir cambiando asta encontrarnos con la ficha dell oponente
	while(matriz.getPosition(fil,col) != ficha){
		matriz.setPosition(fil , col, ficha);
		
		fil += i_fils;
		col += i_cols;	
	}
	
}


void Tablero::colocarFicha(char col, int fil){
	int entero_col = transformarCharCol(col);
	assert ( !estadoTablero() && comprobarCoordenadas(fil , entero_col) && consultarPosicion(col,fil));
	int ficha = turnoActual();
	if(comprobarDiaSupDer( fil, entero_col, ficha )){
		cambiarFichas(fil , -1 , entero_col , 1 , ficha);
	}
	
	if(comprobarDiaSupIzq( fil, entero_col, ficha )){
		cambiarFichas(fil , -1 , entero_col , -1 , ficha);
	}
	
	if(comprobarDiaInfDer( fil, entero_col, ficha )){
		cambiarFichas(fil , 1 , entero_col , 1 , ficha);
	}
	
	if(comprobarDiaInfIzq( fil, entero_col, ficha )){
		cambiarFichas(fil , 1 , entero_col , -1 , ficha);
	}
	
	if(comprobarRecSup( fil, entero_col, ficha )){
		cambiarFichas(fil , -1 , entero_col , 0 , ficha);
	}
		
	if(comprobarRecInf( fil, entero_col, ficha )){
		cambiarFichas(fil , 1 , entero_col , 0 , ficha);
	}
		
	if(comprobarRecDer( fil, entero_col, ficha )){
		cambiarFichas(fil , 0 , entero_col , 1 , ficha);
	}
	
	if(comprobarRecIzq( fil, entero_col, ficha )){
		cambiarFichas(fil , 0 , entero_col , -1 , ficha);
	}
	matriz.setPosition(fil, entero_col, ficha);
	n_fichas_colocadas++;
	if(n_fichas_colocadas < n_fichas){
		turno_J1 = turno_J1 ? false : true;
			std::cout << turnoActual() << std::endl;
		if ( !posibilidadMovimiento(turnoActual())){
			turno_J1 = turno_J1 ? false : true;
				std::cout << turnoActual() << std::endl;
			if (!posibilidadMovimiento(turnoActual())){
				finalizado = true;
			}
		}
					
			
	}else{
		finalizado = true;
	}
		
}
void Tablero::escribir(std::ostream& os) const{
	int ficha;
	char a = 'a';
		int fils = getFils() , cols = getCols();
		os << std::endl << " ";
		for (int i = 0; i < cols; i++)
			os << " " << static_cast<char>(a+i);
		
		
		os << std::endl;
		
		for (int i = 0; i < fils; i++){
				os << i << "|";
			for (int j= 0; j < cols; j++){
				ficha = matriz.getPosition(i,j);
				if(ficha == 1){
					os << 'o' << "|" ;
				}else if(ficha == 2){
					os << 'x' << "|" ;
				}else{
					os << " |";
				}			
			}
			os << std::endl;
		}
		os << std::endl;
			
}















