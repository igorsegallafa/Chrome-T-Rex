#include "Globals.h"
#include "Menu.h"

#include "Game.h"
#include "Render.h"
#include "Ranking.h"

#define MENU_NUMOPTIONS				4	       //Numero total de opcoes do menu

char * pszaMenu[MENU_NUMOPTIONS] 	= { "INICIAR O JOGO", "RANKING", "AJUDA", "SAIR" }; //Strings do Menu
EMenuID eSelectedMenuID 			= MENUID_Start;	 //Variavel para guardar a opcao atual selecionada

char szaNick[18]                    = {0};      //Nick do jogador
int iLenNick                        = 0;        //Tamanho do nick do jogador

BOOL bCanRenderPipe                 = FALSE;    //Renderizar pipe no input do nick
BOOL bCanRenderMenu                 = FALSE;    //Pode mostrar o menu? Ou está esperando o nick

char * GetUserNick()
{
    return szaNick;
}

void UpdateMenu( double fElapsed )
{
    static double fTime500MS = 0.0f;
    fTime500MS += fElapsed;

    if( fTime500MS >= 500.0f )
    {
        //Ficar alternando entre sim ou nao para dar efeito de input
        bCanRenderPipe = !bCanRenderPipe;
        fTime500MS = 0.0f;
    }
}

void OnSelectMenu( EMenuID eMenu )
{
	switch( eMenu )
	{
		case MENUID_Start:
			SetScreenType( SCREENTYPE_World );
			break;
		case MENUID_Ranking:
			SetScreenType( SCREENTYPE_Ranking );
			break;
		case MENUID_Help:
			SetScreenType( SCREENTYPE_Help );
			break;
        case MENUID_Quit:
            QuitGame();
            break;
	}
}

void RenderMenu()
{
	DrawLogo();

    if( bCanRenderMenu )
    {
    	//Desenhar todas as opcoes do Menu
    	for( int i = 0; i < MENU_NUMOPTIONS; i++ )
    		DrawText( (RESOLUTION_COLS >> 1) - (strlen(pszaMenu[i]) >> 1), (RESOLUTION_ROWS >> 1) - (MENU_NUMOPTIONS - 1) + i, pszaMenu[i], i == eSelectedMenuID ? A_STANDOUT : 0 );
    }
    else
    {
        DrawTextColor( (RESOLUTION_COLS >> 1) - 16, RESOLUTION_ROWS >> 1, "Digite seu Nick:", A_BOLD, 255, 255, 255 );

        DrawTextColor( (RESOLUTION_COLS >> 1) + 1, RESOLUTION_ROWS >> 1, szaNick, 0, 255, 255, 255 );

        if( bCanRenderPipe )
            DrawTextColor( (RESOLUTION_COLS >> 1) + 1 + iLenNick, RESOLUTION_ROWS >> 1, "|", 0, 255, 255, 255 );
    }

    //Desenhar o rodapé da tela inicial
    char * pszFooter = "Jogo desenvolvido por Igor Segalla e João Vitor";
    DrawText( (RESOLUTION_COLS >> 1) - (strlen(pszFooter) >> 1), RESOLUTION_ROWS - 3, pszFooter, 0 );
}

void OnKeyDownMenu( int iKeyCode )
{
    if( bCanRenderMenu )
    {
    	switch( iKeyCode )
    	{
    		case 10:
    		case KEY_ENTER:
    			OnSelectMenu( eSelectedMenuID );
    			break;
    		case KEY_UP:
    			if( eSelectedMenuID != MENUID_Start )
    				eSelectedMenuID--;
    			break;
    		case KEY_DOWN:
    			if( eSelectedMenuID != MENUID_Quit )
    				eSelectedMenuID++;
    			break;
    	}
    }
    else if( iKeyCode != 0xFFFFFFFF )
    {
        //Digitar dentro do input a letra que o jogador teclou
        if( iLenNick < 16 && ((iKeyCode >= 'A' && iKeyCode <= 'z') || iKeyCode == ' ' || (iKeyCode >= '0' && iKeyCode <= '9')) )
        {
            szaNick[iLenNick] = iKeyCode;
            iLenNick++;
        }
        //Apagar a ultima letra que digitou
        else if( iKeyCode == KEY_BACKSPACE && iLenNick > 0 )
        {
            iLenNick--;
            szaNick[iLenNick] = 0;
        }
        //Colocou o nick e pressionou enter? Entao mostrar o menu padrao
        else if( (iKeyCode == 10 || iKeyCode == KEY_ENTER) && iLenNick > 0 )
            bCanRenderMenu = TRUE;
    }
}
