#ifndef _RANKING_H
#define _RANKING_H

/**
  * Estrutura para guardar cada jogador do ranking
  */
typedef struct RankingUser{
    int     iScore;
    char    szNick[18];
} RankingUser;

void InitRanking();
void RenderRanking();
void OnKeyDownRanking( int iKeyCode );

#endif
