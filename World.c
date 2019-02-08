#include "Globals.h"
#include "World.h"

#include "Game.h"
#include "Menu.h"

//Valores usados para inicializar os objetos
#define HEIGHTZERO      0
#define TREXCOLS        22
#define TREXROWS        15
#define CACTUSCOLS      13
#define CACTUSROWS      8
#define ROCKCOLS        11
#define ROCKROWS        3
#define EGGCOLS         13
#define EGGROWS         6
#define PTERODCTLCOLS   32
#define PTERODCTLROWS   12

//Desenho do Cactus em forma de matriz
int iaObjectCactus[CACTUSROWS][CACTUSCOLS] ={{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },
											 { 0,0,0,0,0,0,1,1,0,0,0,0,0 },
											 { 0,0,0,1,0,0,1,1,0,0,1,0,0 },
											 { 0,0,0,1,1,0,1,1,0,1,1,0,0 },
											 { 0,0,0,0,1,1,1,1,1,1,0,0,0 },
											 { 0,0,0,0,0,0,1,1,0,0,0,0,0 },
											 { 0,0,0,0,0,0,1,1,0,0,0,0,0 },
											 { 0,0,0,0,0,0,1,1,0,0,0,0,0 }};

//Desenho da Pedra em forma de matriz
int iaObjectRock[ROCKROWS][ROCKCOLS] = {{ 0,0,0,0,0,0,0,1,1,0,0 },
										{ 0,0,0,1,1,1,1,1,1,1,0 },
										{ 0,1,1,1,1,1,1,1,1,1,1 }};

//Desenho do Ovo em forma de Matriz
int iaObjectEgg[EGGROWS][EGGCOLS] = {	{ 0,0,0,0,0,1,1,1,0,0,0,0,0 },
										{ 0,0,0,1,1,1,1,1,1,1,0,0,0 },
										{ 0,0,0,1,1,1,1,1,1,1,0,0,0 },
										{ 0,0,1,1,1,1,1,1,1,1,1,0,0 },
										{ 0,0,1,1,1,1,1,1,1,1,1,0,0 },
										{ 0,0,0,1,1,1,1,1,1,1,0,0,0 }};

//Desenho do Pterodactilo em Matriz
int iaObjectPterodactyl[PTERODCTLROWS][PTERODCTLCOLS] = {
							{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
                            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
                            { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
                            { 0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
                            { 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
                            { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0 },
                            { 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
                            { 0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
                            { 0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
                            { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
                            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
                            { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }};

//Configurações dos Niveis				//Add cada obstaculo   	//MinTime   //MaxTime   //Valor para mudar de nivel
int iaLevelsSetting[MAX_LEVEL][4] = { 	{ 1, 					1200,		3000,		100 },
										{ 2, 					1200,		2500,		150 },
										{ 3, 					1000,		2200,		200 },
										{ 4, 					1000,		2000,		250 },
										{ 5, 					1000,		1900,		270 },
										{ 6, 					1000,		1800,		300 },
										{ 7, 					1000,		1700,		350 },
										{ 8, 					800,		1700,		400 },
										{ 9, 					800,		1600,		450 },
										{ 10, 					800,		1500,		500 },
									 };

//Configurações de probabilidade dos Objetos   //Tipo do objetos        //Range (min-max)
int iaProbabilityObjects[NUM_OBJECTS][3] = { { OBJECTTYPE_Cactus,       0,      3500  },
                                             { OBJECTTYPE_Rock,         3501,   5500  },
                                             { OBJECTTYPE_Pterodactyl,  5501,   7000  },
                                             { OBJECTTYPE_GroundHole,   7001,   9000  },
                                             { OBJECTTYPE_EggInvincible,9001,   9500  },
                                             { OBJECTTYPE_EggFire,      9501,   10000 }};

int                 iUserScore = 0;        			//Variavel para guarar o user score

float	            fTimePowerup = -1;     			//Guardar o tempo do powerup
EObjectType         ePowerupType;          			//Tipo do powerup (lança bola de fogo ou invencibilidade)

float 	            TimeObstacle = -1;     			//Tempo pra gerar os obstaculos
int 	            iDistance = 0;					//Distancia percorrida no jogo

BOOL 				bDead = FALSE;					//Guardar se o jogador morreu
BOOL    			bAnimateFalling = FALSE;    	//Jogador ja morreu, apenas fazer animacao dele caindo
BOOL    			bCanThrowFireBall = TRUE;		//Pode lançar a bola de fogo?

int 				iLevel = 0;						//Nivel em que o jogador esta

double 				fLastKeyDownChecked = 0.0f;		//Ultima vez que o game verificou se a tecla estava pressionada

Object 				sPlayer;						//Struct para o jogador principal
Object 			  * vObjects[MAX_OBJECTS] = {0};	//Vetor para guardar os objetos dentro do jogo

EObjectType RandomObject( BOOL bGenerateEgg )
{
	//Gerar valor aleatorio entre 1 e 10000
    int iRandomValue = (random() % 10000) + 1;

    //Atualizar a seed
    srand( time(NULL) );

    for( int i = 0; i < NUM_OBJECTS; i++ )
    {
    	//O valor gerado está dentro do alcance de algum bojeto?
        if( iRandomValue >= iaProbabilityObjects[i][1] && iRandomValue < iaProbabilityObjects[i][2] )
        {
        	//Gerou algum ovo mas nao era pra gerar? Então gerar novamente
            if( iaProbabilityObjects[i][0] >= OBJECTTYPE_EggInvincible && !bGenerateEgg )
                return RandomObject( bGenerateEgg );
            else
                return iaProbabilityObjects[i][0];
        }
    }

	return OBJECTTYPE_Cactus;
}

int FreeVetorObjects()
{
	//Procurar um espaco dentro do vetor que esteja nulo, ou seja, livre
	for( int i = 0; i < MAX_OBJECTS; ++i )
		if( vObjects[i] == NULL )
			return i;

	return -1;
}

void UnInitVetorObjects()
{
	//Percorrer o vetor que guarda os objetos
	for( int i = 0; i < MAX_OBJECTS; ++i )
	{
		//Objeto existe? Então deletar ele da memoria e liberar a posicao dentro do vetor
		if( vObjects[i] )
		{
			free( vObjects[i] );
			vObjects[i] = NULL;
		}
	}
}

void RenderObject( Object * psObject )
{
	if( psObject->eType == OBJECTTYPE_TRex )
	{
		//Cor do dinossauro em RGB
		short sColorR = 34, sColorG = 177, sColorB = 76;

		//Se o jogador morreu, deixar em escala de cinza
		if( bDead )
			sColorR = 163, sColorG = 163, sColorB = 163;

		//Desenhar as pernas conforme o frame da animacao (0-Normal,1-Perna esquerda levantada,2-Perna direita Levantada)
		if( psObject->iFrame == 1 )
		{
			if( fTimePowerup > 0.0f )
            {
                if( ePowerupType == OBJECTTYPE_EggInvincible )
                    sColorR = 30, sColorG = 240, sColorB = 180;
                else if( ePowerupType == OBJECTTYPE_EggFire )
                    sColorR = 240, sColorG = 120, sColorB = 30;
            }

			DrawEmptyBlockColor( psObject->iX + 4, psObject->iY + 12 - psObject->iHeight, 2, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 10, psObject->iY + 12 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 5, psObject->iY + 13 - psObject->iHeight, 3, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 10, psObject->iY + 13 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 10, psObject->iY + 14 - psObject->iHeight, 2, 1, sColorR, sColorG, sColorB );
		}
		else if( psObject->iFrame == 2 )
		{
			if( fTimePowerup > 0.0f )
            {
                if( ePowerupType == OBJECTTYPE_EggInvincible )
                    sColorR = 30, sColorG = 240, sColorB = 230;
                else if( ePowerupType == OBJECTTYPE_EggFire )
                    sColorR = 240, sColorG = 30, sColorB = 30;
            }

			DrawEmptyBlockColor( psObject->iX + 4, psObject->iY + 12 - psObject->iHeight, 2, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 10, psObject->iY + 12 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 4, psObject->iY + 13 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 10, psObject->iY + 13 - psObject->iHeight, 3, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 4, psObject->iY + 14 - psObject->iHeight, 2, 1, sColorR, sColorG, sColorB );
		}
		else
		{
			DrawEmptyBlockColor( psObject->iX + 4, psObject->iY + 12 - psObject->iHeight, 2, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 10, psObject->iY + 12 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 4, psObject->iY + 13 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 10, psObject->iY + 13 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 4, psObject->iY + 14 - psObject->iHeight, 2, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 10, psObject->iY + 14 - psObject->iHeight, 2, 1, sColorR, sColorG, sColorB );
		}

		//Desenhar a parte de cima do dinossauro (Duck-Abaixado)
		if( psObject->eState == STATE_Duck )
		{
			DrawEmptyBlockColor( psObject->iX + 21, psObject->iY + 6 - psObject->iHeight, 6, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX, psObject->iY + 7 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 18, psObject->iY + 7 - psObject->iHeight, 5, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 24, psObject->iY + 7 - psObject->iHeight, 5, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX, psObject->iY + 8 - psObject->iHeight, 3, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 9, psObject->iY + 8 - psObject->iHeight, 21, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX, psObject->iY + 9 - psObject->iHeight, 26, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 2, psObject->iY + 10 - psObject->iHeight, 17, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 21, psObject->iY + 10 - psObject->iHeight, 8, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 3, psObject->iY + 11 - psObject->iHeight, 10, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 17, psObject->iY + 11 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
		}
		else
		{
			DrawEmptyBlockColor( psObject->iX + 10, psObject->iY + 0 - psObject->iHeight, 8, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 9, psObject->iY + 1 - psObject->iHeight, 3, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 13, psObject->iY + 1 - psObject->iHeight, 7, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 9, psObject->iY + 2 - psObject->iHeight, 11, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 9, psObject->iY + 3 - psObject->iHeight, 6, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 9, psObject->iY + 4 - psObject->iHeight, 9, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX, psObject->iY + 5 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 9, psObject->iY + 5 - psObject->iHeight, 7, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX, psObject->iY + 6 - psObject->iHeight, 2, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 7, psObject->iY + 6 - psObject->iHeight, 11, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX, psObject->iY + 7 - psObject->iHeight, 3, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 6, psObject->iY + 7 - psObject->iHeight, 10, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 18, psObject->iY + 7 - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX, psObject->iY + 8 - psObject->iHeight, 15, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 2, psObject->iY + 9 - psObject->iHeight, 11, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 3, psObject->iY + 10 - psObject->iHeight, 8, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 4, psObject->iY + 11 - psObject->iHeight, 4, 1, sColorR, sColorG, sColorB );
			DrawEmptyBlockColor( psObject->iX + 9, psObject->iY + 11 - psObject->iHeight, 2, 1, sColorR, sColorG, sColorB );
		}
	}
    else if( psObject->eType == OBJECTTYPE_GroundHole )
	{
        DrawEmptyBlock( psObject->iX, psObject->iY - psObject->iHeight, psObject->iCols, psObject->iRows, COLOR_PAIR(1) );
        DrawEmptyBlockColor( psObject->iX - 2, psObject->iY - psObject->iHeight, 2, 5, bDead ? 178 : 182, bDead ? 178 : 122, bDead ? 178 : 87 );
        DrawEmptyBlockColor( psObject->iX + psObject->iCols, psObject->iY - psObject->iHeight, 2, 5, bDead ? 178 : 182, bDead ? 178 : 122, bDead ? 178 : 87 );
    }
    else if( psObject->eType == OBJECTTYPE_FireBall )
	{
        DrawEmptyBlockColor( psObject->iX, psObject->iY - psObject->iHeight, 2, 1, bDead ? 178 : 182, bDead ? 178 : 122, bDead ? 178 : 87 );
    }
	else
	{
		//Desenhar outros objetos com base em sua matriz
		for( int i = 0; i < psObject->iRows; ++i )
		{
			//Desenhar as colunas da matriz
			for( int j = 0; j < psObject->iCols; ++j )
			{
				if ( psObject->eType == OBJECTTYPE_Cactus )
				{
					//Cor do cacto
					short sColorR = 18, sColorG = 117, sColorB = 48;

					//Se o jogador morreu, deixar em escala de cinza
					if( bDead )
						sColorR = 130, sColorG = 130, sColorB = 130;

					if( iaObjectCactus[i][j] )
						DrawEmptyBlockColor( psObject->iX + j, psObject->iY + i - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
				}
				else if(psObject->eType == OBJECTTYPE_Rock)
				{
					//Cor da pedra
					short sColorR = 110, sColorG = 110, sColorB = 110;

					if( iaObjectRock[i][j] )
						DrawEmptyBlockColor( psObject->iX + j, psObject->iY + i - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
				}
				else if(psObject->eType == OBJECTTYPE_EggInvincible)
				{
					//Cor do Ovo
					short sColorR = 151, sColorG = 178, sColorB = 159;

					if( psObject->iFrame == 1 )
						sColorR = 234, sColorG = 227, sColorB = 170;
					else if( psObject->iFrame == 2 )
						sColorR = 234, sColorG = 212, sColorB = 64;

					//Se o jogador morreu, deixar em escala de cinza
					if( bDead )
						sColorR = 170, sColorG = 170, sColorB = 170;

					if( iaObjectEgg[i][j] )
						DrawEmptyBlockColor( psObject->iX + j, psObject->iY + i - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
				}
                else if(psObject->eType == OBJECTTYPE_EggFire)
				{
					//Cor do Ovo
					short sColorR = 151, sColorG = 178, sColorB = 159;

					if( psObject->iFrame == 1 )
						sColorR = 255, sColorG = 170, sColorB = 80;
					else if( psObject->iFrame == 2 )
						sColorR = 200, sColorG = 65, sColorB = 40;

					//Se o jogador morreu, deixar em escala de cinza
					if( bDead )
						sColorR = 170, sColorG = 170, sColorB = 170;

					if( iaObjectEgg[i][j] )
						DrawEmptyBlockColor( psObject->iX + j, psObject->iY + i - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
				}
                else if(psObject->eType == OBJECTTYPE_Pterodactyl)
				{
					//Cor do Pterodactilo
					short sColorR = 50, sColorG = 80, sColorB = 50;

					//Se o jogador morreu, deixar em escala de cinza
					if( bDead )
						sColorR = 90, sColorG = 90, sColorB = 90;

					if( iaObjectPterodactyl[i][j] )
						DrawEmptyBlockColor( psObject->iX + j, psObject->iY + i - psObject->iHeight, 1, 1, sColorR, sColorG, sColorB );
				}
			}
		}
	}
}

void AddObject( int iX, int iY, EObjectType eType )
{
	//Procurar uma posicao vaga dentro do vetor
	int iIndex = FreeVetorObjects();

	//Se a posicao que retornou foi diferente de -1, quer dizer que tem espaco
	if( iIndex != -1 )
	{
		Object * psObject = malloc(sizeof(Object));
		psObject->iX 	= iX;
		psObject->iY 	= iY;
		psObject->eType = eType;
		InitObject( psObject );

		//Guardar o objeto criado no vetor
		vObjects[iIndex] = psObject;
	}
}

void InitObject( Object * psObject )
{
	if( psObject )
	{
		if( psObject->eType == OBJECTTYPE_TRex )
		{
			psObject->iCols = TREXCOLS;
			psObject->iRows = TREXROWS;
			psObject->iHeight = HEIGHTZERO;
			psObject->iMaxFrames = 3;

			//Bounding Box do Jogador (usado para a colisao do dinossauro e os objetos)
			psObject->sBoundingBox.iX = (psObject->iCols >> 1) - 3;
			psObject->sBoundingBox.iY = 0;
			psObject->sBoundingBox.iWidth = 6;
			psObject->sBoundingBox.iHeight = 13;

			psObject->bEnemy = FALSE;
		}
		else if( psObject->eType == OBJECTTYPE_Cactus )
		{
			psObject->iCols = CACTUSCOLS;
			psObject->iRows = CACTUSROWS;
			psObject->iHeight = HEIGHTZERO;
			psObject->iMaxFrames = 1;

			//Bounding Box do Cacto
			psObject->sBoundingBox.iX = (psObject->iCols >> 1) - 5;
			psObject->sBoundingBox.iY = (psObject->iRows >> 1) - 5;
			psObject->sBoundingBox.iWidth = 10;
			psObject->sBoundingBox.iHeight = 10;

			psObject->bEnemy = TRUE;
		}
		else if( psObject->eType == OBJECTTYPE_Rock )
		{
			psObject->iCols = ROCKCOLS;
			psObject->iRows = ROCKROWS;
			psObject->iHeight = HEIGHTZERO;
			psObject->iMaxFrames = 1;

			//Bounding Box da Pedra
			psObject->sBoundingBox.iX = (psObject->iCols >> 1) - 3;
			psObject->sBoundingBox.iY = 0;
			psObject->sBoundingBox.iWidth = 6;
			psObject->sBoundingBox.iHeight = 3;

			psObject->bEnemy = TRUE;
		}
		else if( psObject->eType == OBJECTTYPE_EggInvincible )
		{
			psObject->iCols = EGGCOLS;
			psObject->iRows = EGGROWS;
			psObject->iHeight = HEIGHTZERO;
			psObject->iMaxFrames = 3;

			//Bounding Box do Ovo
			psObject->sBoundingBox.iX = (psObject->iCols >> 1) - 4;
			psObject->sBoundingBox.iY = 2;
			psObject->sBoundingBox.iWidth = 8;
			psObject->sBoundingBox.iHeight = 3;

			psObject->bEnemy = FALSE;
		}
        else if( psObject->eType == OBJECTTYPE_EggFire )
		{
			psObject->iCols = EGGCOLS;
			psObject->iRows = EGGROWS;
			psObject->iHeight = HEIGHTZERO;
			psObject->iMaxFrames = 3;

			//Bounding Box do Ovo
			psObject->sBoundingBox.iX = (psObject->iCols >> 1) - 4;
			psObject->sBoundingBox.iY = 2;
			psObject->sBoundingBox.iWidth = 8;
			psObject->sBoundingBox.iHeight = 3;

			psObject->bEnemy = FALSE;
		}
        else if( psObject->eType == OBJECTTYPE_Pterodactyl )
		{
			psObject->iCols = PTERODCTLCOLS;
			psObject->iRows = PTERODCTLROWS;
			psObject->iHeight = HEIGHTZERO;
            psObject->iY -= PTERODCTLROWS;
            psObject->iMaxFrames = 1;

			//Bounding Box do Pterodactilo
			psObject->sBoundingBox.iX = 16;
			psObject->sBoundingBox.iY = 0;
			psObject->sBoundingBox.iWidth = 1;
			psObject->sBoundingBox.iHeight = 12;

			psObject->bEnemy = TRUE;
		}
        else if( psObject->eType == OBJECTTYPE_GroundHole )
		{
			psObject->iCols = 21;
			psObject->iRows = 5;
			psObject->iHeight = 0;
            psObject->iMaxFrames = 1;
            psObject->iY += 5;

			//Bounding Box do Buraco no Chao
			psObject->sBoundingBox.iX = 14;
			psObject->sBoundingBox.iY = -3;
			psObject->sBoundingBox.iWidth = 2;
			psObject->sBoundingBox.iHeight = 15;

			psObject->bEnemy = TRUE;
		}
        else if( psObject->eType == OBJECTTYPE_FireBall )
		{
			psObject->iCols = 2;
			psObject->iRows = 1;
			psObject->iHeight = 0;
            psObject->iMaxFrames = 1;

			//Bounding Box do Fogo
			psObject->sBoundingBox.iX = 0;
			psObject->sBoundingBox.iY = 0;
			psObject->sBoundingBox.iWidth = 2;
			psObject->sBoundingBox.iHeight = 1;

			psObject->bEnemy = FALSE;
		}

		psObject->iY -= psObject->iRows;
	}
}

void DeadPlayer()
{
    bDead = TRUE;

    //Salvar o High Score do Jogador no arquivo score.txt
    FILE * pFile = fopen( "score.txt", "a+" );
    if( pFile )
    {
        fprintf( pFile, "%s %d\n", GetUserNick(), iUserScore );
        fclose(pFile);
    }
}

void InitWorld()
{
	//Limpar o vetor que guarda os objetos
    UnInitVetorObjects();

    //Resetar configurações do jogo
	TimeObstacle 	= iaLevelsSetting[iLevel][1] + (random() % (iaLevelsSetting[iLevel][2] - iaLevelsSetting[iLevel][1]));
	sPlayer.iX    	= 30;
	sPlayer.iY    	= RESOLUTION_ROWS - 5;
	sPlayer.eType 	= OBJECTTYPE_TRex;
	sPlayer.eState	= STATE_Jumping;

	iLevel 			= 0;
	iUserScore		= 0;
	iDistance 	  	= 0;
    bAnimateFalling = FALSE;
	bDead			= FALSE;

	//Inicializar o jogador novamente
	InitObject( &sPlayer );
}

void UpdateWorld( double fElapsed )
{
	static double fTime10MS = 0.0f; static double fTime150MS = 0.0f;
	static double fTimeRandom = 0.0f;

	fTime10MS += fElapsed; fTime150MS += fElapsed;
	fTimeRandom += fElapsed;

	//Se está usando algum powerup, entao diminuir seu tempo total
	if( fTimePowerup > 0.0f )
		fTimePowerup -= fElapsed;

	//Atualizar o estado do jogo se o jogador ainda nao morreu
	if( !bDead )
	{
		//Verificar se o jogador ainda esta pressionando a tecla para se abaixar
		if( sPlayer.eState == STATE_Duck )
		{
			//Se ele ainda estiver pressionando, colocado o estado como abaixado, se nao, como correndo
			if( TICKCOUNT - fLastKeyDownChecked < 500.0f )
            {
				sPlayer.eState = STATE_Duck;
                bCanThrowFireBall = FALSE;
            }
			else
            {
				sPlayer.eState = STATE_Running;
                bCanThrowFireBall = TRUE;
            }
		}

		//Gerar obstaculos aleatoriamente
		if(fTimeRandom >= TimeObstacle)
		{
			EObjectType eObjectType = RandomObject( fTimePowerup > 0.0f ? FALSE : TRUE );
			AddObject( RESOLUTION_COLS, RESOLUTION_ROWS - 5, eObjectType );

			TimeObstacle = iaLevelsSetting[iLevel][1] + (random() % (iaLevelsSetting[iLevel][2] - iaLevelsSetting[iLevel][1]));
			fTimeRandom = 0.0f;
		}

		//Verificar se ja passou 10MS desde o ultimo Update
		if( fTime10MS >= 10.0f )
		{
			//Se ja passou, zerar a variavel que guarda o tempo total
			fTime10MS = 0.0f;

			//Atualizar o objeto do jogador conforme a animacao, pulando ou caindo
			if( sPlayer.eState == STATE_Jumping )
			{
				//Como esta pulando, incrementar sua altura de 1 em 1
				sPlayer.iHeight += 1;

				//Se ele chegou na altura maxima, fazer ele cair
				if( sPlayer.iHeight > 15 )
					sPlayer.eState = STATE_Falling;
			}
			else if( sPlayer.eState == STATE_Falling )
			{
				//Como esta descendo, decrementar sua altura de 1 em 1
				sPlayer.iHeight -= 1;

				//Se chegou no chao, mudar para animacao de correr e zerar variaveis
				if( sPlayer.iHeight <= 0 && !bAnimateFalling )
				{
					sPlayer.eState = STATE_Running;
					sPlayer.iFrame = 0;
					sPlayer.iHeight = 0;
				}
                else if( bAnimateFalling && sPlayer.iHeight < -5 - sPlayer.iRows )
                    DeadPlayer();
			}

            if( !bAnimateFalling )
            {
                //Incrementar a distancia percorrida
                iDistance += iLevel > 7 ? 2 : 1;

    			//Atualizar outros objetos do jogo sem ser o jogador
    			for( int i = 0; i < MAX_OBJECTS; ++i )
    			{
    				Object * psObject = vObjects[i];

    				//Ponteiro valido?
    				if( psObject )
    				{
    					//Se o objeto for uma bola de fogo, entao incrementar seu x, se não, decrementar
    					if( psObject->eType == OBJECTTYPE_FireBall )
                            psObject->iX += iLevel > 7 ? 2 : 1;
                        else
    					    psObject->iX -= iLevel > 7 ? 2 : 1;

    					int iAddX = 0;
    					int iAddY = 0;
    					int iAddWidth = 0;
    					int iAddHeight = 0;

    					//Se o objeto for diferente do buraco no chão, e o player está abaixado, mudar a bounding box do Player
    					if( sPlayer.eState == STATE_Duck && psObject->eType != OBJECTTYPE_GroundHole )
    					{
    						iAddY = 6;
    						iAddWidth = 10;
    					}

    					//Objeto pra comprar o bounding box
                        Object * pObj1 = psObject;

                        //Se o objeto for a bola de fogo, entao procurar o objeto mais proximo dele
                        if( psObject->eType == OBJECTTYPE_FireBall )
                        {
                            int iMinDistance = RESOLUTION_COLS;

                            for( int j = 0; j < MAX_OBJECTS; j++ )
                                if( vObjects[j] )
                                    if( vObjects[j]->iX < iMinDistance && vObjects[j]->eType < OBJECTTYPE_EggInvincible )
                                        pObj1 = vObjects[j];
                        }

                        //Se for bola de fogo, usar ela para a comparacao, se nao, o jogador
                        Object * pObj2 = psObject->eType == OBJECTTYPE_FireBall ? psObject : &sPlayer;

    					int iX11 = pObj1->iX + pObj1->sBoundingBox.iX;
    					int iX12 = pObj1->iX + pObj1->sBoundingBox.iX + pObj1->sBoundingBox.iWidth;
    					int iY11 = pObj1->iY - pObj1->iHeight + pObj1->sBoundingBox.iY;
    					int iY12 = pObj1->iY - pObj1->iHeight + pObj1->sBoundingBox.iY + pObj1->sBoundingBox.iHeight;
    					int iX21 = pObj2->iX + pObj2->sBoundingBox.iX + iAddX;
    					int iX22 = pObj2->iX + pObj2->sBoundingBox.iX + pObj2->sBoundingBox.iWidth + iAddWidth;
    					int iY21 = pObj2->iY - pObj2->iHeight + pObj2->sBoundingBox.iY + iAddY;
    					int iY22 = pObj2->iY - pObj2->iHeight + pObj2->sBoundingBox.iY + pObj2->sBoundingBox.iHeight + iAddHeight;

    					int bNoOverlap = iX11 >= iX22 || iX21 >= iX12 || iY11 >= iY22 || iY21 >= iY12;

    					//Verificar se o jogador colidiu com o objeto
    					if( !bNoOverlap )
    					{
    						//O objeto era inimigo? Entao o jogador morre
    						if( psObject->bEnemy )
    						{
    							//Buraco no chao? Entao fazer o jogador cair
                                if( psObject->eType == OBJECTTYPE_GroundHole )
                                {
                                    sPlayer.eState = STATE_Falling;
                                    bAnimateFalling = TRUE;
                                }
                                else if( fTimePowerup > 0.0f && ePowerupType == OBJECTTYPE_EggInvincible )
                                {
                                }
                                else
                                {
                                	//Fazer o jogador morrer
                                    DeadPlayer();
                                }
    						}
                            else if( psObject->eType == OBJECTTYPE_FireBall && psObject != pObj1 )
                            {
                            	//Se o objeto é uma bola de fogo, e ela colidiu com outro objeto

                  				//Mover a bola de fogo e o outro objeto para fora da tela, para assim serem deletados
                                psObject->iX = RESOLUTION_COLS + 1;
                                pObj1->iX = -pObj1->iX;
                            }
    						else if( fTimePowerup < 0.0f && sPlayer.eState == STATE_Duck )
    						{
    							//Setar o powerup como ativo por 8s
    							fTimePowerup = 8000.0f;
                                ePowerupType = psObject->eType;

                                //Mover o ovo para fora da tela, para assim ser deletado
    							psObject->iX = -psObject->iCols;
    						}
    					}

    					//Objeto ja passou pelo jogador e saiu da tela?
    					if( psObject->iX + psObject->iCols < 0 || (psObject->eType == OBJECTTYPE_FireBall && psObject->iX > RESOLUTION_COLS) )
    					{
    						//Deletar o objeto
    						free( psObject );
    						vObjects[i] = NULL;

    						iUserScore += iaLevelsSetting[iLevel][0];
    					}
    				}
    			}
            }
		}

		//Verificar se ja passou 150MS desde o ultimo Update
		if( fTime150MS > 150.0f )
		{
			fTime150MS = 0.0f;

			//Atualizar o frame da animacao do dinossauro (0..2)
			sPlayer.iFrame = (sPlayer.iFrame + 1) % sPlayer.iMaxFrames;

			//Atualizar outros objetos do jogo sem ser o jogador
			for( int i = 0; i < MAX_OBJECTS; ++i )
				if( vObjects[i] )
					vObjects[i]->iFrame = (vObjects[i]->iFrame + 1) % vObjects[i]->iMaxFrames;

			//Atualizar o User Score
			iUserScore += 1;

			//Atualizar o level se passar na condicao
			if( iUserScore >= iaLevelsSetting[iLevel][3] && iLevel != MAX_LEVEL - 1 )
				iLevel++;
		}
	}
}

void RenderWorld()
{
	//Desenhar o Chao
    {
        short sColorR = 50, sColorG = 100, sColorB = 50;

        if( bDead )
            sColorR = 100, sColorG = 100, sColorB = 100;

        DrawEmptyBlockColor( 0, RESOLUTION_ROWS - 4, RESOLUTION_COLS, 4, sColorR, sColorG, sColorB  );
    	DrawEmptyBlockColor( 0, RESOLUTION_ROWS - 5, RESOLUTION_COLS, 1, bDead ? 178 : 182, bDead ? 178 : 122, bDead ? 178 : 87 );

    	for( int i = 0; i < RESOLUTION_COLS; ++i)
    	{
    		if( ((iDistance + i) % 25) == 0 )
    			DrawTextColorBackground( i, RESOLUTION_ROWS - 3, "_", A_BOLD, bDead ? 178 : 255, bDead ? 178 : 242, bDead ? 178 : 0, sColorR, sColorG, sColorB );

    		if( ((iDistance + i) % 36) == 0 )
    			DrawTextColorBackground( i, RESOLUTION_ROWS - 2, ".", A_BOLD, bDead ? 178 : 255, bDead ? 178 : 255, bDead ? 178 : 255, sColorR, sColorG, sColorB );
    	}
    }

	//Desenhar outros objetos do jogo
	for( int i = 0; i < MAX_OBJECTS; ++i )
	{
		Object * psObject = vObjects[i];

		//Ponteiro valido?
		if( psObject )
			RenderObject( psObject );
	}

    //Desenhar o jogador (dinossauro trex)
    RenderObject( &sPlayer );

	//Desenhar tela quando o jogador morreu
	if( bDead )
	{
		char * pszText = "Você morreu!";
		DrawTextColor( (RESOLUTION_COLS >> 1) - (strlen(pszText) >> 1), (RESOLUTION_ROWS >> 1) - 5, pszText, A_BOLD, 255, 70, 70 );

		char szUserScore[32]={0};
		sprintf(szUserScore,"Score Final: %d", iUserScore );
		DrawTextColor( (RESOLUTION_COLS >> 1) - (strlen(szUserScore) >> 1), (RESOLUTION_ROWS >> 1) - 4, szUserScore, 0, 255, 255, 255 );

		pszText = "Pressione ESPACO para recomeçar!";
		DrawTextColor( (RESOLUTION_COLS >> 1) - (strlen(pszText) >> 1), (RESOLUTION_ROWS >> 1) - 2, pszText, 0, 255, 255, 255 );
	}
	else
	{
		//Desenhar o user score do jogador
		DrawTextColor( RESOLUTION_COLS - 20, 2, "User Score", 0, 255, 255, 255 );

		char szText[128]={0};
		sprintf(szText,"%d", iUserScore );
		DrawTextColor( RESOLUTION_COLS - 8, 2, szText, A_BOLD, 0, 255, 0 );

		memset( szText, 0, 128 );
		sprintf(szText,"LEVEL %d", iLevel + 1 );
		DrawTextColor( (RESOLUTION_COLS >> 1) - (strlen(szText) >> 1), 2, szText, A_BOLD, 255, 255, 255 );
	}
}

void OnKeyDownWorld( int iKeyCode )
{
	if( !bDead && !bAnimateFalling )
	{
		switch( iKeyCode )
		{
			case ' ':
			case KEY_UP:
				//Verificar se o jogador ja nao esta pulando ou caindo
				if( sPlayer.eState != STATE_Jumping && sPlayer.eState != STATE_Falling )
				{
					sPlayer.eState = STATE_Jumping;
					sPlayer.iFrame = 0;
				}
				break;
			case KEY_DOWN:
				//Verificar se o jogador pode lançar bola de fogo
                if( bCanThrowFireBall && fTimePowerup > 0.0f && ePowerupType == OBJECTTYPE_EggFire )
                    AddObject( sPlayer.iX + 5, sPlayer.iY + 10, OBJECTTYPE_FireBall );

				//Verificar se o jogador ja nao esta pulando ou caindo
				if( sPlayer.eState != STATE_Jumping && sPlayer.eState != STATE_Falling )
				{
					fLastKeyDownChecked = TICKCOUNT;
					sPlayer.eState = STATE_Duck;
				}
				break;
			default:
				break;
		}
	}
	else if( bDead && (iKeyCode == ' ' || iKeyCode == 10 || iKeyCode == KEY_UP || iKeyCode == KEY_ENTER) )
		InitWorld();
}
