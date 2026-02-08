#include "raylib.h"
#include "utility.h"
#include "matrix.h"
#include "globals.h"
//---- GRAPHIC FUNCTIONS ----//

void setFPS(int FPS) {
	SetTargetFPS(FPS);
}

void createWindow(int width, int height) {
	InitWindow(width, height, "B4k3r");
}

void finishWindow() {
	CloseWindow();
}

void createCanvasBlack() {
	BeginDrawing();
	ClearBackground(BLACK);
};

void finishCanvas() {
	EndDrawing();
}

int main() {
	MatriX <int> grid;
	grid.setDimensionsDefault();
	grid.setButtonPositionDefault();
	grid.setButtonColorDefault();

	createWindow(760, 900);
	InitAudioDevice();
	setFPS(60);
	while (!WindowShouldClose()) {
			createCanvasBlack();
			grid.checkRectanglePressed();
			grid.checkRectanglePressedSingle();
			grid.drawMatrix();
			grid.drawSave();
			grid.drawClearCanvas();
			grid.drawTranspose();
			grid.drawDance();
			grid.DrawSingleMode();

			grid.checkSavePressed();
			grid.checkClearCanvasPressed();
			grid.checkTransposePressed();
			grid.checkDancePressed();
			grid.checkSingleModePressed();
			finishCanvas();
	}
	StopMusicStream(bgMusic);
	UnloadMusicStream(bgMusic);
	CloseAudioDevice();
	finishWindow();
}

//---- ----------------- ----//
