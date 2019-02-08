#ifndef _MENU_H
#define _MENU_H

/**
  * Opções do Menu
  */
typedef enum
{
	MENUID_Start,
	MENUID_Ranking,
	MENUID_Help,
	MENUID_Quit
} EMenuID;

/**
  * Pegar o nick que o jogador digitou ao abrir o jogo
  * @return - string com o nick do jogador
  */
char * GetUserNick();

void UpdateMenu( double fElapsed );
void OnSelectMenu( EMenuID eMenu );
void RenderMenu();
void OnKeyDownMenu( int iKeyCode );

#endif
