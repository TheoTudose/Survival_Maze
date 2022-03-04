#include "hud.h"
#include "utils/gl_utils.h"
#include "components/simple_scene.h"
#include "avatar.h"
#include "labirint.h"
#include "enemy.h"
#include <iostream>
#include <fstream>

Hud::Hud() {}

void Hud::setBGMatrix() 
{
	hBarMatrix = glm::mat4(1) * transform3D::Translate(getPStartingPos().x + 3.0f, getPStartingPos().y + 4.5f, getPStartingPos().z - 0.01f) *
		transform3D::Scale(3.f, 0.5f, 0.01f);
	sBarMatrix = glm::mat4(1) * transform3D::Translate(getPStartingPos().x - 3.0f, getPStartingPos().y + 4.5f, getPStartingPos().z - 0.01f) *
		transform3D::Scale(3.f, 0.5f, 0.01f);
	tBarMatrix = glm::mat4(1) * transform3D::Translate(getPStartingPos().x - 4.25f, getPStartingPos().y, getPStartingPos().z - 0.01f) *
		transform3D::Scale(0.5f, 3.6f, 0.01f);
	crosshair_hor = glm::mat4(1) *
		transform3D::Translate(getPStartingPos().x, getPStartingPos().y, getPStartingPos().z) *
		transform3D::Scale(0.25f, 0.04f, 0.001f);
	crosshair_vert = glm::mat4(1) *
		transform3D::Translate(getPStartingPos().x, getPStartingPos().y, getPStartingPos().z) *
		transform3D::Scale(0.03f, 0.3f, 0.001f);
}


void Hud::setScore()
{
	score++;
}

void Hud::setShowScore(bool var)
{
	showScore = var;
}

void Hud::setTimer(float deltaTimeSeconds)
{
	timer -= deltaTimeSeconds;
	decaTimer += deltaTimeSeconds;
	if (squareNo > 1) {
		if (decaTimer >= 10)
		{
			squareNo--;
			std::cout << squareNo * 10 << " seconds remaining!\n";
			decaTimer = 0;
		}
	}
	else {
		if (decaTimer >= 1)
		{
			std::cout << lround(timer) << " seconds remaining!\n";
			decaTimer = 0;
		}
	}
}

void Hud::showCMDScore()
{
	if (showScore)
	{
		std::cout << "Score: " << score << "\n";
		showScore = false;
	}
}

void Hud::writeGameFile()
{
	std::ofstream ofs;
	ofs.open("src/lab_m1/tema2/maze.txt", std::ofstream::out | std::ofstream::trunc);
	if (gameVar == 1)
	{
		ofs << "2";
	}
	else if (gameVar == 2)
		ofs << "1";
	ofs.close();
}

void Hud::readGameFile()
{
	std::ifstream input_file;
	input_file.open("src/lab_m1/tema2/maze.txt");
	if (!input_file.is_open()) {
		std::cout << "Could not open the file - '"
			<< "Maze.txt" << "'" << "\n";
	}
	input_file >> gameVar;
	std::cout << gameVar << "\n";
	input_file.close();

	if (gameVar == 1)
	{
		pStartingPos = labirint->statingPos1;
		cStartingPos = labirint->cameraInitPos1;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				maze[i][j] = labirint->h_maze1[i][j];
			}
		}
	}
	else if (gameVar == 2)
	{
		pStartingPos = labirint->statingPos2;
		cStartingPos = labirint->cameraInitPos2;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				maze[i][j] = labirint->h_maze2[i][j];
			}
		}
	}
	

}

void Hud::endGame(Avatar* player)
{
	if (player->getStartingPos().x <= -21 || player->getStartingPos().z <= -21) {
		std::cout << "Final score is: " << score << "\n";
		std::cout << "Time: " << 120 - timer << "\n";
		exit(1);
	}
	if (player->getHealth() < 1 || timer <= 0)
	{
		std::cout << "GAME OVER\n";
		std::cout << "Final score is: " << score << "\n";
		exit(1);
	}
}

