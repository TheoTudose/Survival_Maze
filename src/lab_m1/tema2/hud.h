#ifndef TEMA2_HUD_H
#define TEMA2_HUD_H
#include "utils/gl_utils.h"
#include "components/simple_scene.h"
#include "avatar.h"
#include "labirint.h"
#include "enemy.h"


class Hud {
private:
	glm::mat4 hBarMatrix;
	glm::mat4 sBarMatrix;
	glm::mat4 tBarMatrix;
	glm::mat4 crosshair_hor;
	glm::mat4 crosshair_vert;
	glm::vec3 pStartingPos;
	glm::vec3 cStartingPos;
	
	int squareNo = 12;
	float decaTimer = 0;
	int score = 0;
	bool showScore = false;
	float timer = 120;
	int gameVar = 0;
	Labirint* labirint = new Labirint();
	Avatar* avatar = new Avatar();

public:
	int maze[20][20];


	Hud();

	glm::mat4 getHBarMatrix()
	{
		return hBarMatrix;
	}

	glm::mat4 getSBarMatrix()
	{
		return sBarMatrix;
	}

	glm::mat4 getTBarMatrix()
	{
		return tBarMatrix;
	}

	glm::mat4 getCrosshairHor() {
		return crosshair_hor;
	}
	glm::mat4 getCrosshairVert() {
		return crosshair_vert;
	}

	int getSquareNo()
	{
		return squareNo;
	}

	float getDecaTimer()
	{
		return decaTimer;
	}

	int getScore()
	{
		return score;
	}

	bool getShowScore()
	{
		return showScore;
	}

	float getTimer()
	{
		return timer;
	}

	int getGameVar()
	{
		return gameVar;
	}

	glm::vec3 getPStartingPos()
	{
		return pStartingPos;
	}

	glm::vec3 getCStartingPos()
	{
		return cStartingPos;
	}


	void setBGMatrix();
	void setScore();
	void setShowScore(bool var);
	void showCMDScore();
	void setTimer(float deltaTimeSeconds);
	void writeGameFile();
	void readGameFile();
	void endGame(Avatar* player);

};


#endif //TEMA2_HUD_H
