#ifndef _RENDER_H
#define _RENDER_H

#define MAX_COLORS  256		//Número máximo de cores que pode criar

/**
  * Estrutura para guardar a cor e sua ID
  */
typedef struct Color{
	short 	sR, sG, sB;
	int		iColorID;
} Color;

/**
  * Desenhar texto com as flags do ncurses
  */
void DrawText( int iX, int iY, char * pszText, int iFlags );

/**
  * Desenhar o texto com cores RGB
  */
void DrawTextColor( int iX, int iY, char * pszText, int iFlags, short sR, short sG, short sB );

/**
  * Desenhar o texto com cores RGB e background RGB
  */
void DrawTextColorBackground( int iX, int iY, char * pszText, int iFlags, short sR, short sG, short sB, short sR2, short sG2, short sB2 );

/**
  * Desenhar um bloco vazio com flags do ncurses
  */
void DrawEmptyBlock( int iX, int iY, int iCols, int iRols, int iFlags );

/**
  * Desenhar um bloco vazio com cores RGB
  */
void DrawEmptyBlockColor( int iX, int iY, int iCols, int iRols, short sR, short sG, short sB );

/**
  * Desenhar a logo do jogo
  */
void DrawLogo();

#endif
