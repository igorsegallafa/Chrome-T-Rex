#include "Globals.h"
#include "Render.h"
#include "Game.h"

int iTotalTextColors = 0;					//Total de cores criadas para o texto
Color * vTextColors[MAX_COLORS] = {0};		//Vetor para guardar as cores criadas para os textos

int iTotalBlockColors = 0;					//Total de cores criadas para blocos
Color * vBlockColors[MAX_COLORS] = {0};		//Vetor para guardar as cores criadas para os blocos

int GetColorID( Color ** vColors, short sR, short sG, short sB, short sR2, short sG2, short sB2, int iType )
{
	//Percorrer o vetor procurando uma cor com o RGB especificado, se encontrar, retornar a ID da cor
	for( int i = 0; i < MAX_COLORS; ++i )
	{
		Color * psColor = vColors[i];

		//Ponteiro valido?
		if( psColor )
			if( psColor->sR == (iType == 2 ? sR + sR2 : sR) && psColor->sG == (iType == 2 ? sG + sG2 : sG) && psColor->sB == (iType == 2 ? sB + sB2 : sB) )
				return psColor->iColorID;
	}

    //Criar a cor com fundo preto, para textos
    if( iType == 0 )
    {
        Color * psNewColor = malloc(sizeof(Color));
        psNewColor->sR = sR;
        psNewColor->sG = sG;
        psNewColor->sB = sB;
        psNewColor->iColorID = 50 + iTotalTextColors;

        init_pair( psNewColor->iColorID, psNewColor->iColorID, COLOR_BLACK );
        init_color( psNewColor->iColorID, (sR * 1000) / 255, (sG * 1000) / 255, (sB * 1000) / 255 );

        vTextColors[iTotalTextColors++] = psNewColor;

        return psNewColor->iColorID;
    }
    //Criar a cor para blocos vazios
    else if( iType == 1 )
    {
        Color * psNewColor = malloc(sizeof(Color));
        psNewColor->sR = sR;
        psNewColor->sG = sG;
        psNewColor->sB = sB;
        psNewColor->iColorID = 115 + iTotalBlockColors;

        init_pair( psNewColor->iColorID, COLOR_BLACK, psNewColor->iColorID );
        init_color( psNewColor->iColorID, (sR * 1000) / 255, (sG * 1000) / 255, (sB * 1000) / 255 );

        vBlockColors[iTotalBlockColors++] = psNewColor;

        return psNewColor->iColorID;
    }
    //Criar a cor para textos com cor de fundo
    else if( iType == 2 )
    {
        Color * psNewColor = malloc(sizeof(Color));
        psNewColor->sR = sR + sR2;
        psNewColor->sG = sG + sG2;
        psNewColor->sB = sB + sB2;
        psNewColor->iColorID = 200 + iTotalTextColors;

        init_pair( psNewColor->iColorID, psNewColor->iColorID, psNewColor->iColorID + 1 );
        init_color( psNewColor->iColorID, (sR * 1000) / 255, (sG * 1000) / 255, (sB * 1000) / 255 );
        init_color( psNewColor->iColorID + 1, (sR2 * 1000) / 255, (sG2 * 1000) / 255, (sB2 * 1000) / 255 );

        vTextColors[iTotalTextColors++] = psNewColor;
        iTotalTextColors++;

        return psNewColor->iColorID;
    }

	return -1;
}

void DrawText( int iX, int iY, char * pszText, int iFlags )
{
	attron( iFlags );
	mvprintw( iY, iX, pszText );
	attroff( iFlags );
}

void DrawTextColor( int iX, int iY, char * pszText, int iFlags, short sR, short sG, short sB )
{
	//Procurar a cor especificada dentro do vetor de texto
	int iColorPair = GetColorID( vTextColors, sR, sG, sB, 0, 0, 0, 0 );

	attron( COLOR_PAIR(iColorPair) | iFlags );
	mvprintw( iY, iX, pszText );
	attroff( COLOR_PAIR(iColorPair) | iFlags );
}

void DrawTextColorBackground( int iX, int iY, char * pszText, int iFlags, short sR, short sG, short sB, short sR2, short sG2, short sB2 )
{
    //Procurar a cor especificada dentro do vetor de texto
	int iColorPair = GetColorID( vTextColors, sR, sG, sB, sR2, sG2, sB2, 2 );

	attron( COLOR_PAIR(iColorPair) | iFlags );
	mvprintw( iY, iX, pszText );
	attroff( COLOR_PAIR(iColorPair) | iFlags );
}

void DrawEmptyBlock( int iX, int iY, int iCols, int iRols, int iFlags )
{
    attron( iFlags );
    for( int i = 0; i < iCols; ++i )
        for( int j = 0; j < iRols; ++j )
            mvprintw( iY + j, iX + i, " " );
    attroff( iFlags );
}

void DrawEmptyBlockColor( int iX, int iY, int iCols, int iRols, short sR, short sG, short sB )
{
	//Procurar a cor especificada dentro do vetor de blocos
	int iColorPair = GetColorID( vBlockColors, sR, sG, sB, 0, 0, 0, 1 );

	attron( COLOR_PAIR(iColorPair) );
	for( int i = 0; i < iCols; ++i )
		for( int j = 0; j < iRols; ++j )
			mvprintw( iY + j, iX + i, " " );
	attroff( COLOR_PAIR(iColorPair) );
}

void DrawLogo()
{
	DrawText( (RESOLUTION_COLS >> 1) - 40, LOGOSTART_Y, "  _____ _                                _______     _____                       ", COLOR_PAIR(1) );
	DrawText( (RESOLUTION_COLS >> 1) - 40, LOGOSTART_Y + 1, " / ____| |                              |__   __|   |  __ \\            _     _   ", COLOR_PAIR(1) );
	DrawText( (RESOLUTION_COLS >> 1) - 40, LOGOSTART_Y + 2, "| |    | |__  _ __ ___  _ __ ___   ___     | |______| |__) |_____  ___| |_ _| |_ ", COLOR_PAIR(1) );
	DrawText( (RESOLUTION_COLS >> 1) - 40, LOGOSTART_Y + 3, "| |    | '_ \\| '__/ _ \\| '_ ` _ \\ / _ \\    | |______|  _  // _ \\ \\/ |_   _|_   _|", COLOR_PAIR(1) );
	DrawText( (RESOLUTION_COLS >> 1) - 40, LOGOSTART_Y + 4, "| |____| | | | | | (_) | | | | | |  __/    | |      | | \\ |  __/>  <  |_|   |_|  ", COLOR_PAIR(1) );
	DrawText( (RESOLUTION_COLS >> 1) - 40, LOGOSTART_Y + 5, " \\_____|_| |_|_|  \\___/|_| |_| |_|\\___|    |_|      |_|  \\_\\___/_/\\_\\            ", COLOR_PAIR(1) );
}
