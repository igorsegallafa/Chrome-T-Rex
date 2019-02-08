#include "Globals.h"
#include "Game.h"

#include "Menu.h"
#include "Help.h"
#include "World.h"
#include "Ranking.h"

EScreenType eScreenType = SCREENTYPE_Menu;
EScreenType eOldScreenType;

double fLastUpdateTime = 0.0f;

double GetTickCount()
{
  struct timespec now;

  if (clock_gettime(CLOCK_MONOTONIC, &now))
    return 0;

  return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}

void Init()
{
	//Criar uma cor para a logo do jogo
	init_pair( 1, COLOR_GREEN, COLOR_BLACK );

	//Inicializar o World e o Ranking
	InitWorld();
    InitRanking();
}

void Update()
{
	//Verificar a tela ativa, e chamar o update dela
	switch( eScreenType )
	{
        case SCREENTYPE_Menu:
			UpdateMenu( TICKCOUNT - fLastUpdateTime );
			break;
		case SCREENTYPE_World:
			UpdateWorld( TICKCOUNT - fLastUpdateTime );
			break;
		default:
			break;
	}

	fLastUpdateTime = TICKCOUNT;
}

void Render()
{
	clear();

	//Verificar a tela ativa, e chamar o render dela
	switch( eScreenType )
	{
		case SCREENTYPE_Menu:
			RenderMenu();
			break;
		case SCREENTYPE_Help:
			RenderHelp();
			break;
		case SCREENTYPE_World:
			RenderWorld();
			break;
        case SCREENTYPE_Ranking:
            RenderRanking();
            break;
	}
}

EScreenType	GetScreenType()
{
	return eScreenType;
}

EScreenType RestoreScreenType()
{
	return eOldScreenType;
}

void SetScreenType( EScreenType eScreen )
{
	eOldScreenType = eScreenType;
	eScreenType = eScreen;
	fLastUpdateTime = TICKCOUNT;

    if( eScreen == SCREENTYPE_World )
        InitWorld();

	clear();
}

int GetResolution( int iType )
{
	int iWidth = 0, iHeight = 0;
	getmaxyx( stdscr, iWidth, iHeight );

	return iType == 0 ? iWidth : iHeight;
}

void OnKeyDown( int iKeyCode )
{
    if( eScreenType == SCREENTYPE_World )
    {
    	switch( iKeyCode )
    	{
    		case 'h':
    		case 'H':
    			SetScreenType( SCREENTYPE_Help );
    			break;
            case 'q':
        	case 'Q':
        		SetScreenType( SCREENTYPE_Menu );
        		break;
    	}
    }

	switch( eScreenType )
	{
		case SCREENTYPE_Menu:
			return OnKeyDownMenu( iKeyCode );
		case SCREENTYPE_Help:
			return OnKeyDownHelp( iKeyCode );
		case SCREENTYPE_World:
			return OnKeyDownWorld( iKeyCode );
        case SCREENTYPE_Ranking:
            return OnKeyDownRanking( iKeyCode );
	}
}

BOOL GameStatus = 1; //0 quando fechar o jogo
void QuitGame() {
    GameStatus = FALSE;
}

BOOL GameOn() {
    return GameStatus;
}
