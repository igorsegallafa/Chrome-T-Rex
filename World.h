#ifndef _WORLD_H
#define _WORLD_H

#define MAX_LEVEL		10		//Numero máximo de niveis
#define MAX_OBJECTS		100		//Numero máximo de objetos para guardar no vetor

#define NUM_OBJECTS 	6		//Numero de tipo de objetos

/**
  * Tipo de objetos possiveis
  */
typedef enum
{
	OBJECTTYPE_TRex,
	OBJECTTYPE_Cactus,
	OBJECTTYPE_Rock,
    OBJECTTYPE_Pterodactyl,
    OBJECTTYPE_GroundHole,
	OBJECTTYPE_EggInvincible,
    OBJECTTYPE_EggFire,
    OBJECTTYPE_FireBall,
} EObjectType;

/**
  * Estados que algum objeto pode ter
  */
typedef enum
{
	STATE_Idle,
	STATE_Running,
	STATE_Jumping,
	STATE_Falling,
	STATE_Duck,
} EState;

/**
  * Bounding Box (area de colisao do objeto)
  */
typedef struct BoundingBox{
	int 			iX, iY, iWidth, iHeight;
} BoundingBox;

/**
  * Objeto do jogo
  */
typedef struct Object{
	int 			iX, iY;
	int 			iCols, iRows;
	EObjectType		eType;
	EState			eState;
	int 			iFrame;
	int 			iMaxFrames;
	int 			iHeight;

	BOOL			bEnemy;
	BoundingBox		sBoundingBox;
} Object;

/**
  * Procurar uma posição livre dentro do vetor de objetos
  * @return - Posição livre dentro do vetor, se for -1 nao tem posicao livre
  */
int  FreeVetorObjects();

/**
  * Renderizar algum objeto
  * @param1 - Ponteiro para o objeto que vai ser desenhado
  */
void RenderObject( Object * psObject );

/**
  * Adicionar algum objeto ao jogo
  * @param1 - Posicao X que ele deve nascer
  * @param2 - Posicao Y que ele deve nascer
  * @param3 - Tipo do objeto
  */
void AddObject( int iX, int iY, EObjectType eType );

/**
  * Inicializar o objeto com suas respectivas configurações
  * @param1 - Ponteiro para o objeto que vai inicializar
  */
void InitObject( Object * psObject );

/**
  * Matar o jogador
  */
void DeadPlayer();

void InitWorld();
void UpdateWorld( double fElapsed );
void RenderWorld();
void OnKeyDownWorld( int iKeyCode );

#endif
