#include "Globals.h"
#include "Game.h"

int main()
{
	//Inicializar NCurses
	initscr();
	raw();
	nodelay( stdscr, TRUE );
	keypad( stdscr, TRUE );
	noecho();
	curs_set(0);
	start_color();
	cbreak();

	//Inicializar o jogo
	Init();

	//Enquanto o jogo estiver ativo
	while( GameOn() )
	{
		//Ao pressionar alguma tecla
		OnKeyDown( getch() );

		//Atualizar o jogo
		Update();

		//Renderizar o jogo
		Render();
	}

	//Finalizar o ncurses
	noraw();
	curs_set(1);
	echo();
	clear();
	endwin();

	return 0;
}
