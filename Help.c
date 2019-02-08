#include "Globals.h"
#include "Menu.h"

#include "Game.h"
char *ajuda = "Salte sobre obstáculos, desvie de pterodáctilos com o fenomenal dinossauro do Google Chrome, agora no seu terminal do Linux!\n\n	Colete ovos que lhe garantem poderes especiais:\n		Ovo Vermelho: Pressione a seta para baixo para que o Trex lance uma bola de fogo que destroi cactos\n		Ovo Verde: O Trex fica invencível por 5 segundos\n	Porém lembre-se, para coletar um ovo você deve passar por ele abaixado!\n\n	Controles:\n		Pular: Tecla de Espaço ou Seta para Cima\n		Abaixar: Seta para Baixo\n		Voltar para o menu: Tecla q";

void RenderHelp()
{
	DrawLogo();

	DrawTextColor(15, LOGOSTART_Y + 9, ajuda, 0, 50, 200, 100 );
	DrawText( (RESOLUTION_COLS >> 1) - (strlen("Voltar") >> 1), RESOLUTION_ROWS - 5, "Voltar", A_STANDOUT );
}

void OnKeyDownHelp( int iKeyCode )
{
	switch( iKeyCode )
	{
		case 10:
		case KEY_ENTER:
			SetScreenType( RestoreScreenType() );
			break;
	}
}
