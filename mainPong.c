// Copyright [2023] <Ángel Almahano Moreno>
#include <stdio.h>
#include "basicFunctions.h"
#include <conio.h>
#include <time.h>
//compilar con estas opciones, para hacer más pequeño el archivo: g++ -s -o pong mainPong.c

class BALL
{
	COORD c, d;
	bool hit = false;

public:
	BALL(int x, int y);
	void Draw();
	void Erase();
	COORD GetCoord();
	bool Collision();
	void Move();
	void ChangeDirection(bool x, bool y);
};

// Constructor
BALL::BALL(int x, int y)
{
	// inicializa las coordenadas
	c.X = x;
	c.Y = y;
	// inicializa la direccion
	d.Y = 1;
	d.X = 1;
}

void BALL::Draw()
{
	// coloca el cursor y pinta un caracter sacado de 
	// https://elcodigoascii.com.ar/codigos-ascii-extendidos/bloque-color-tramado-densidad-baja-caracter-grafico-codigo-ascii-176.html
	Gotoxy(c.X, c.Y);printf("%c", 220);
}

void BALL::Erase()
{
	// si es distinto de la linea de enmedio, borra
	if (c.X !=60)
	{
		Gotoxy(c.X, c.Y);printf(" ");
	}
	else
	{
		Gotoxy(c.X, c.Y);printf("%c",219);	
	}
}

COORD BALL::GetCoord()
{
	return c;
}

bool BALL::Collision()
{

	hit = true;

	// width 120 height 30
	if((c.X > 2 && c.X <117) && (c.Y > 2 && c.Y <27))
		hit = false;

	return hit;
}

void BALL::Move()
{

	Erase();


	if(Collision())
	{
		// cuando golpea los limites horizontales o verticales cambia la dirección

		if(c.X < 2 || c.X > 117)
			ChangeDirection(true, false);
		if(c.Y < 2 || c.Y > 27)
			ChangeDirection(false, true);

	}
	
	c.X +=d.X;
	c.Y +=d.Y;	
	
	
	Draw();

}

void BALL::ChangeDirection(bool x, bool y)
{
	if(x)
	{
		d.X *=-1;
	}
	if(y)
	{
		d.Y *=-1;
	}
}

class RACKET
{
	COORD c;
	int score;
public:
	RACKET(int x, int y);
	void Draw();
	void Erase();
	void Move(int y);
	void UpdateScore(int posX);
	void SetPoint();
};

RACKET::RACKET(int x, int y)
{
	c.X = x;
	c.Y = y;
	score = 0;
}

void RACKET::Draw()
{
	Gotoxy(c.X, c.Y);printf("%c",219);
	Gotoxy(c.X, c.Y+1);printf("%c",219);
	Gotoxy(c.X, c.Y+2);printf("%c",219);
	Gotoxy(c.X, c.Y+3);printf("%c",219);
}

void RACKET::Erase()
{
	Gotoxy(c.X, c.Y);printf(" ");
	Gotoxy(c.X, c.Y+1);printf(" ");
	Gotoxy(c.X, c.Y+2);printf(" ");
	Gotoxy(c.X, c.Y+3);printf(" ");
}

void RACKET::Move(int y)
{
	Erase();

	c.Y = y;

	Draw();
}

void RACKET::UpdateScore(int posX)
{
	Gotoxy(posX,0);printf("           ");
	Gotoxy(posX,0);printf("Score: %d",score);
}

void RACKET::SetPoint()
{
	score +=1;
}

DrawLimits()
{
	// dibuja el tablero

	// lineas horizontales
	for(int i=0; i< 119; i++)
	{
		Gotoxy(i,0);printf("%c",219);
		Gotoxy(i,29);printf("%c",219);
	}

	// lineas verticales
	for(int i=0; i< 30; i++)
	{
		Gotoxy(0,i);printf("%c",219);
		Gotoxy(119,i);printf("%c",219);
	}

	// linea de enmedio
	for(int i=0; i< 30; i++)
	{
		Gotoxy(60,i);printf("%c",219);
	}	
}

int main()
{
	// dibuja el tablero
	DrawLimits();
	
	// inicializa la semilla para el random
	srand(time(NULL));

	// crea la pelota en un punto aleatorio del tablero dentro de los limites
	BALL b(rand()%110+1, rand()%20+1);

	// inicializa la direccion aleatoria en un numero entre el 0 y el 1
	int directionX = rand()%2+1;
	int directionY = rand()%2+1;

	if (directionX==1)
		b.ChangeDirection(true,false);
	if (directionY==1)
		b.ChangeDirection(false,true);
	
	COORD p1;
	p1.X = 1;
	p1.Y = 15;

 	COORD p2;
	p2.X = 118;
	p2.Y = 15;
	
	// inicializa las raquetas
	RACKET r1(p1.X, p1.Y);
	RACKET r2(p2.X, p2.Y);

	bool run = true;
	bool goal = false;

	while(run)
	{
		// oculta el cursor
		HideCursor();

		// inicia los marcadores
		r1.UpdateScore(30);
		r2.UpdateScore(90);
		
		// mueve la pelota	
		b.Move();

		// si se pulsa una tecla
		if(kbhit())
		{
			char k = getch();

			// Player 1 UP
			if(k == 'q' && p1.Y > 1)
			{
				p1.Y -= 1;
			}
			// Player 1 DOWN
			if(k == 'a' && p1.Y+3 <28)
			{
				p1.Y += 1;
			}
			// Player 2 UP
			if(k == 72 && p2.Y > 1)
			{
				p2.Y -= 1;
			}
			// Player 2 DOWN
			if(k == 80 && p2.Y+3 <28)
			{
				p2.Y += 1;
			}
		}

		// mueve las raquetas
		r1.Move(p1.Y);
		r2.Move(p2.Y);

		// si la pelota golpea la raqueta Player 1
		if (b.GetCoord().X == p1.X && (b.GetCoord().Y == p1.Y || b.GetCoord().Y == p1.Y+1 || b.GetCoord().Y == p1.Y+2 || b.GetCoord().Y == p1.Y+3))
		{
			goal = false;
		}
		else if(b.GetCoord().X < 2)
		{
			goal = true;
			r2.SetPoint();
		}

		if (b.GetCoord().X == p2.X && (b.GetCoord().Y == p2.Y || b.GetCoord().Y == p2.Y+1 || b.GetCoord().Y == p2.Y+2 || b.GetCoord().Y == p2.Y+3))
		{
			goal = false;
		}
		else if(b.GetCoord().X > 117)
		{
			goal = true;
			r1.SetPoint();
		}

		// necesario para que el procesador no se sobrecargue
		Sleep(30);	
	}
	

	return 0;
}