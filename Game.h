#ifndef _GAME_H
#define _GAME_H

#include "Render.h"

#define RESOLUTION_ROWS 	   (GetResolution(0))
#define RESOLUTION_COLS		   (GetResolution(1))

#define TICKCOUNT            (GetTickCount())

typedef enum
{
	SCREENTYPE_Menu,
    SCREENTYPE_Help,
    SCREENTYPE_World,
    SCREENTYPE_Ranking,
} EScreenType;

/**
  * Funcao equivalente ao GetTickCount do Windows pelo Usuario Rob do StackOverflow
  * https://stackoverflow.com/questions/7729686/convert-gettickcount-vxworks-to-linux
  */
double        GetTickCount();

/**
  * Funcões "mães" padrões, devem chamar as funcões "filhas" de acordo com a tela ativa
  */
void 			    Init();
void			    Update();
void			    Render();

/**
  * Retornar o tipo de tela ativa
  * @return - tipo da tela
  */
EScreenType		GetScreenType();

EScreenType   RestoreScreenType();

/**
  * Setar um tipo de tela como ativa
  * @param1 - Tela que deseja deixar ativa
  */
void			    SetScreenType( EScreenType eScreen );

/**
  * Retornar a resolucão do terminal (colunas e linhas)
  * @param1 <0|1> - Se 1 retorna as colunas, se 0 as linhas
  * @return - Numero de colunas ou linhas do terminal
  */
int 			    GetResolution( int iType );

/**
  * Funcão chamada quando alguma tecla é pressionada
  * @param1 - Tecla que foi pressionada
  */
void 			    OnKeyDown( int iKeyCode );

void 				  QuitGame();
BOOL 				  GameOn();

#endif
