#include "Globals.h"
#include "Ranking.h"

#include "Game.h"
#include "Render.h"

int                 iTotalUsers = 0;            //Total de jogadores carregados
RankingUser       * psaRankingUsers = NULL;     //Vetor para guardar os jogadores carregados

int Compare( const void * a, const void * b )
{
    //Ordenar os jogadores por seus scores
    RankingUser * pA = (RankingUser*)a;
    RankingUser * pB = (RankingUser*)b;

    return (pB->iScore - pA->iScore );
}

void InitRanking()
{
    //Ler o arquivo que guarda os scores
    FILE * pFile = fopen( "score.txt", "rb" );
    if( pFile )
    {
        char * pszLine = "";
        size_t iLen = 0;
        ssize_t nRead = 0;

        const char sDelimiter[2] = " ";
        char * pTokens;

        //Ler cada linhada do arquivo
        while( (nRead = getline(&pszLine,&iLen,pFile)) != -1 )
        {
            //Se a linha possui algum conteudo
            if( strlen(pszLine) > 4 )
            {
                //Incrementar o numero de jogadores carregados
                iTotalUsers++;

                //Primeira vez? Entao alocar o ranking, se nao apenas mudar seu tamanho
                if( psaRankingUsers == NULL )
                    psaRankingUsers = malloc(sizeof(RankingUser));
                else
                    psaRankingUsers = realloc(psaRankingUsers,sizeof(RankingUser) * iTotalUsers);

                int iIndex = 0;
                pTokens = strtok( pszLine, sDelimiter );

                //Percorrer os elementos daquela linha, para pegar o nome e score
                while( pTokens != NULL )
                {
                    if( iIndex == 0 )
                        strcpy( psaRankingUsers[iTotalUsers-1].szNick, pTokens);
                    else if( iIndex == 1 )
                        psaRankingUsers[iTotalUsers-1].iScore = atoi(pTokens);

                    iIndex++;
                    pTokens = strtok( NULL, pszLine );
                }
            }
        }

        //Ordenar o ranking pelo score dos jogadores
        qsort( psaRankingUsers, iTotalUsers, sizeof(RankingUser), Compare );

        fclose( pFile );
    }
}

void RenderRanking()
{
    DrawLogo();

    for( int i = 0; i < iTotalUsers; i++ )
    {
        //Desenhar apenas o TOP 10
        if( i >= 10 )
            break;

        DrawTextColor( (RESOLUTION_COLS >> 1) - 20, (RESOLUTION_ROWS >> 1) - 5, "#      Nick", A_BOLD, 255, 255, 255 );
        DrawTextColor( (RESOLUTION_COLS >> 1) + 15, (RESOLUTION_ROWS >> 1) - 5, "Score", A_BOLD, 255, 255, 255 );

        char szText[32] ={0};
        sprintf( szText, "%02d     %s", i + 1, psaRankingUsers[i].szNick );
        DrawTextColor( (RESOLUTION_COLS >> 1) - 20, (RESOLUTION_ROWS >> 1) - 4 + i, szText, 0, 255, 255, 255 );

        sprintf( szText, "%d", psaRankingUsers[i].iScore );
        DrawTextColor( (RESOLUTION_COLS >> 1) + 15, (RESOLUTION_ROWS >> 1) - 4 + i, szText, 0, 255, 255, 255 );
    }

    DrawText( (RESOLUTION_COLS >> 1) - (strlen("Voltar") >> 1), RESOLUTION_ROWS - 5, "Voltar", A_STANDOUT );
}

void OnKeyDownRanking( int iKeyCode )
{
    switch( iKeyCode )
	{
		case 10:
		case KEY_ENTER:
            //Voltar para a tela de menu
			SetScreenType( RestoreScreenType() );
			break;
	}
}
