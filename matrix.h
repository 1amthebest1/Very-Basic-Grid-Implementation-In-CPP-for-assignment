#pragma once
#include <iostream>
#include "raylib.h"
#include <cstdlib>
#include <fstream>
#include "globals.h"
#include <string>
//Part 1: Template - Based Matrix Data Structure
//Implement a Matrix Class Template

//Your matrix must support :
//• Dynamic memory allocation
//• Any numeric data type(T) [done!?]
//• Row - major storage [okay i will do it]
//Required Operations :
//• Constructor : Matrix(rows, cols)
//• Copy constructor & destructor
//• Element access using operator()(i, j)
//• Matrix addition& subtraction
//• Scalar multiplication
//• Matrix multiplication(if dimensions allow)
//• Transpose

using namespace std;

template <typename T>
class MatriX {
public:
	T width;
	T height;
	int buttonColor[30][30];
	T buttonPositionX[30][30];
	T buttonPositionY[30][30];

	int Iterator = 0;
	bool musicPlaying = false;
	bool SingleMode = false;

	MatriX() {
		
	};

	//void scalarMultiplication();
	//void transpose();

	Color checkColorValue(T colorValue) {
		if (colorValue == 0) {
			return Color{ 255, 0, 13, 255 }; //red
		}
		else if (colorValue == 1) {
			return Color{ 0, 0, 200, 255 }; //blue
		}
		else if (colorValue == 2) {
			return Color{ 255, 255, 255, 255 }; //white
		}
		else if (colorValue == 3) {
			return Color{ 128, 0, 128, 255 }; //purple
		}
		else {
			return Color{ 255, 165, 0, 255 }; //orange
		}
	}

	void setDimensionsDefault() {
		width = 20;
		height = 20;
	}

	void drawMatrix() {
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				DrawRectangle(buttonPositionX[i][j], buttonPositionY[i][j], width, height, checkColorValue(buttonColor[i][j]));
			}
		}
	}

	void setButtonColorDefault() {
		srand(time(0));
		for (int i = 0; i < 30; i++) {
			for (int x = 0; x < 30; x++) {
				buttonColor[i][x] = rand() % 4;
			}
		}
	}

	void setButtonPositionDefault() {
		//create window of 760 by 760
		int incrementorX = 5;
		int incrementorY = 5;
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				buttonPositionX[i][j] = incrementorX;
				buttonPositionY[i][j] = incrementorY;
				incrementorX += 25;
			}
			incrementorX = 5;
			incrementorY += 25;
		}
	}

	void checkRectanglePressed() {
		if ((IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) && SingleMode==false) {
			Vector2 mousePoint = GetMousePosition();
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					if (mousePoint.x >= buttonPositionX[i][j] && mousePoint.x <= buttonPositionX[i][j] + width) {
						if (mousePoint.y >= buttonPositionY[i][j] && mousePoint.y <= buttonPositionY[i][j] + height) {
							//buttonColor[i][j] = changeButtonColor(buttonColor[i][j]);
							buttonColor[i][j] = 2;
						}
					}
				}
			}
		}
	}

	void checkRectanglePressedSingle() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && SingleMode == true) {
			Vector2 mousePoint = GetMousePosition();
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					if (mousePoint.x >= buttonPositionX[i][j] && mousePoint.x <= buttonPositionX[i][j] + width) {
						if (mousePoint.y >= buttonPositionY[i][j] && mousePoint.y <= buttonPositionY[i][j] + height) {
							buttonColor[i][j] = changeButtonColor(buttonColor[i][j]);
							//buttonColor[i][j] = 2;
						}
					}
				}
			}
		}
	}

	int changeButtonColor(int colorValue) {
		if (colorValue == 3) {
			return 0;
		}
		else if (colorValue == 0) {
			return 1;
		}
		else if (colorValue == 1) {
			return 2;
		}
		else {
			return 3;
		}
	}

	void drawSave() {
		DrawRectangle(5, 770, 90, 40, YELLOW);
		DrawText("Save Image", 7, 780, 15, BLACK);
	}

	void saveImage() {
		srand(time(0));
		string fileName = "BakerRocks" + to_string(rand() % 10000) + to_string(rand() % 99999);
		fileName = "C:\\Users\\saeed\\OneDrive\\Desktop\\savedImages\\" + fileName + ".txt";
		ofstream saver(fileName);
		if (saver) {
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					saver << buttonColor[i][j];
				}
				saver << "\n";
			}
		}
	}

	void checkSavePressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 5 && mousePoint.x <= 5 + 90) {
				if (mousePoint.y >= 770 && mousePoint.y <= 770 + 40) {
					saveImage();
					cout << "Image Saved" << endl;
				}
			}
		}
	}

	void clearCanvas() {
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				buttonColor[i][j] = 0;
			}
		}
		cout << "Canvas Cleared"<<endl;
	}

	void drawClearCanvas() {
		DrawRectangle(5, 830, 90, 40, YELLOW);
		DrawText("CLEAR", 16, 840, 15, BLACK);
	}

	void checkClearCanvasPressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 5 && mousePoint.x <= 5 + 90) {
				if (mousePoint.y >= 840 && mousePoint.y <= 830 + 40) {
					clearCanvas();
				}
			}
		}
	}

	void drawTranspose() {
		DrawRectangle(150, 770, 90, 40, YELLOW);
		DrawText("Transpose", 155, 780, 15, BLACK);
	}

	void Transpose() {
		for (int i = 0; i < 30; i++) {
			for (int j = i + 1; j < 30; j++) {
				swap(buttonPositionX[i][j], buttonPositionX[j][i]);
				swap(buttonPositionY[i][j], buttonPositionY[j][i]);
			}
		}
		cout << "Transpose Pressed"<<endl;
	}

	void checkTransposePressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 150 && mousePoint.x <= 150 + 90) {
				if (mousePoint.y >= 770 && mousePoint.y <= 770 + 40) {
					Transpose();
				}
			}
		}
	}

	void drawDance() {
		Iterator++;
		if (Iterator <= 30) {
			DrawRectangle(150, 830, 90, 40, GREEN);
		}
		else if (Iterator > 30 && Iterator <=60) {
			DrawRectangle(150, 830, 90, 40, PINK);
		}
		else if (Iterator > 60 && Iterator <= 90) {
			DrawRectangle(150, 830, 90, 40, ORANGE);
		}
		else if (Iterator > 90 && Iterator <= 120) {
			DrawRectangle(150, 830, 90, 40, BLUE);
		}
		else {
			DrawRectangle(150, 830, 90, 40, PURPLE);
			Iterator = 0;
		}
		DrawText("DANCE", 160, 840, 15, BLACK);
	}

	void dance() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !musicPlaying) {
			PlayMusicStream(bgMusic);
			musicPlaying = true;
		}

		if (musicPlaying) {
			UpdateMusicStream(bgMusic);
		}
	}

	void checkDancePressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 150 && mousePoint.x <= 150 + 90) {
				if (mousePoint.y >= 830 && mousePoint.y <= 830 + 40) {
					cout << "Dance Pressed" << endl;
					musicPlaying = !musicPlaying;
				}
			}
		}
	}

	void DrawSingleMode() {
		DrawRectangle(300, 770, 90, 40, YELLOW);
		DrawText("Single Mode", 305, 780, 15, BLACK);
	}

	void singleMode() {
		SingleMode =! SingleMode;
	}

	void checkSingleModePressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 300 && mousePoint.x <= 300 + 90) {
				if (mousePoint.y >= 770 && mousePoint.y <= 770 + 40) {
					singleMode();
					cout << "Single Mode" << endl;
				}
			}
		}
	}

};	
