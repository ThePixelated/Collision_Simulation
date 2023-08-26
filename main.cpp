#include <iostream>
#include <Windows.h>
#include <conio.h>

struct Ball {
    int x_coor;
    int y_coor;
    int ballSpeed;
    bool x_borderHit;
    bool y_borderHit;

    int styleBall;
};
	
struct AdditionalCoor{
	int x_coor;
	int y_coor;
};

struct Block {
	int xBarCoor;   // Center Point of X
	int yBarCoor;   // Center Point of Y
	
	AdditionalCoor top_bar;     // Mid Point of top left and top right
	AdditionalCoor bottom_bar;  // Mid Point of bottom left and bottom right
	AdditionalCoor left_bar;    // Mid Point of top left and bottom left
	AdditionalCoor right_bar;   // Mid Point of top right and bottom right
	AdditionalCoor center_bar;  // The Center of the block
	
	AdditionalCoor topLeft_bar;
	AdditionalCoor topRight_bar;
	AdditionalCoor bottomLeft_bar;
	AdditionalCoor bottomRight_bar;
};

Block* _BarInnit(int ManyBlocks = 1, int X_axis = -1, int Y_axis = -1, int WidthBlock = 1, int HeightBlock = 5, int BlockRotation = 0, int ScrnWidth = 119, int ScrnHeight = 30) {
	Block* bars = new Block[ManyBlocks];
	
	if (X_axis == -1) X_axis = (ScrnWidth / 2) + 1;
	if (Y_axis == -1) Y_axis = ScrnHeight / 2;
	
	for (int i = 0; i < ManyBlocks; i++) {
		std::cin >> X_axis >> Y_axis;
		bars[i].xBarCoor = X_axis;
		bars[i].yBarCoor = Y_axis;
		
		bars[i].top_bar.x_coor = bars[i].xBarCoor;
		bars[i].bottom_bar.x_coor = bars[i].xBarCoor;
		
		bars[i].top_bar.y_coor = bars[i].yBarCoor - HeightBlock / 2;
		bars[i].bottom_bar.y_coor = bars[i].yBarCoor + HeightBlock / 2;
	}
	
	return bars;
}

void EraseBall(Ball* ball_data, int size) {
    COORD coor;
    for (int i = 0; i < size; i++) {
        coor.X = ball_data[i].x_coor;
		coor.Y = ball_data[i].y_coor;
	
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coor);
	    std::cout << ' ';
	}

    // Sleep(100);
}

void RenderBall(Ball* ball_data, int size) {
    COORD coor;
    for (int i = 0; i < size; i++) {
        coor.X = ball_data[i].x_coor;
		coor.Y = ball_data[i].y_coor;
	
		SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coor);
	    std::cout << char(219);
	}
}

void BorderCollision(Ball* ball_data, int widthScreen, int heightScreen, int size) {
    // Border Collision Check
    // ----------------------
    for (int i = 0; i < size; i++) {
        if (ball_data[i].x_coor <= 0) {
            ball_data[i].x_borderHit = true;
        } else if (ball_data[i].x_coor >= widthScreen - 1) {
            ball_data[i].x_borderHit = false;
        }

        if (ball_data[i].y_coor <= 0) {
            ball_data[i].y_borderHit = true;
        } else if (ball_data[i].y_coor >= heightScreen) {
            ball_data[i].y_borderHit = false;
        }
    }
}

void BallCollisionBar(Ball* ball_data, Block* bar, int size, int ManyBlocks = 1) {
//	int xAxis_Cache[size];
//	int yAxis_Cache[size];
//	
//	xAxis_Cache[0] = ball_data[0].x_coor;
//	yAxis_Cache[0] = ball_data[0].y_coor;
	
	for (int i = 0; i < size; i++) {
//		if (i > 0) xAxis_Cache[i] = ball_data[i - 1].x_coor;
		
		for (int j = 0; j < ManyBlocks; j++) {
			// X AXIS CHECK
			// ------------
			// Left Side Bar Collision
			if (/* ball_data[i].x_coor != xAxis_Cache[i] && */ ball_data[i].x_borderHit && (ball_data[i].x_coor >= bar[j].xBarCoor && ball_data[i].x_coor <= bar[j].xBarCoor) && (ball_data[i].y_coor >= bar[j].top_bar.y_coor && ball_data[i].y_coor <= bar[j].bottom_bar.y_coor) ) {
				ball_data[i].x_coor -= 1;
				ball_data[i].x_borderHit = false;
			}
			
			// Right Side Bar Collision
			else if (!ball_data[i].x_borderHit && (ball_data[i].x_coor <= bar[j].xBarCoor && ball_data[i].x_coor >= bar[j].xBarCoor) && (ball_data[i].y_coor >= bar[j].top_bar.y_coor && ball_data[i].y_coor <= bar[j].bottom_bar.y_coor) ) {
				ball_data[i].x_coor += 1;
				ball_data[i].x_borderHit = true;
			}
			
			// Y AXIS CHECK
			// ------------
			// Top Side Bar Collision
			if (ball_data[i].y_borderHit && (ball_data[i].y_coor >= bar[j].top_bar.y_coor && ball_data[i].y_coor <= bar[j].top_bar.y_coor) && (ball_data[i].x_coor >= bar[j].xBarCoor && ball_data[i].x_coor <= bar[j].xBarCoor)) {
				ball_data[i].y_coor -= 1;
				ball_data[i].y_borderHit = false;
			}
			
			// Bottom Side Bar Collision
			else if (!ball_data[i].y_borderHit && (ball_data[i].y_coor <= bar[j].bottom_bar.y_coor && ball_data[i].y_coor >= bar[j].bottom_bar.y_coor) && (ball_data[i].x_coor >= bar[j].xBarCoor && ball_data[i].x_coor <= bar[j].xBarCoor)) {
				ball_data[i].y_coor += 1;
				ball_data[i].y_borderHit = true;
			}
		}
	}
}

void BallMovement(Ball* ball_data, int size) {
    // Ball Movement
    // -------------
    for (int i = 0; i < size; i++) {
//        EraseBall(ball_data[i]);

        if (ball_data[i].x_borderHit) ball_data[i].x_coor += ball_data[i].ballSpeed;    // X Axis Movement
        else ball_data[i].x_coor -= ball_data[i].ballSpeed;

        if (ball_data[i].y_borderHit) ball_data[i].y_coor += ball_data[i].ballSpeed;    // Y Axis Movement
        else ball_data[i].y_coor -= ball_data[i].ballSpeed;

//        RenderBall(ball_data[i]);
    }
}

void RenderBlock(Block* bar, int ManyBlocks = 1) {
    COORD coor;
    
    for (int i = 0; i < ManyBlocks; i++) {
//    	std::cerr << " Break Point B\n";
    	for (int j = bar[i].top_bar.y_coor; j <= bar[i].top_bar.y_coor - (bar[i].top_bar.y_coor - bar[i].bottom_bar.y_coor); j++) {
//    		std::cerr << " Break Point C\n";
    		coor.X = bar[i].xBarCoor;
			coor.Y = j;
			
//			std::cerr << " Break Point D\n";
			SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coor);
			std::cout << char(219);
		}
		
//		std::cerr << " Break Point E\n";
	}
    
}

void corner_coorBuff(int ScreenWidth, int ScreenHeight) {
    COORD corner_coor;
    corner_coor.X = ScreenWidth;
    corner_coor.Y = ScreenHeight;

    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), corner_coor);
}

int main() {
    int width = 119;
    int height = 29;
	
	int ManyBlocks = 15;
	Block* bar = _BarInnit(ManyBlocks);
	
	// Inspect
	// -------
	
//	std::cout << bar[0].xBarCoor << ",";
//	std::cout << bar[0].yBarCoor << '\n';
//	
//	std::cout << bar[0].top_bar.x_coor << ":";
//	std::cout << bar[0].bottom_bar.x_coor << "  - X\n";
//	
//	std::cout << bar[0].top_bar.y_coor << ":";
//	std::cout << bar[0].bottom_bar.y_coor << "  - Y\n\n";
//	
//	getch();
	
	int size;
    std::cin >> size;
    Ball ball[size];

    for (int i = 0; i < size; i++) {
        std::cin >> ball[i].x_coor >> ball[i].y_coor >> ball[i].ballSpeed >> ball[i].x_borderHit >> ball[i].y_borderHit;
    }
    
//    std::cerr << " Break Point A\n";
	RenderBlock(bar, ManyBlocks);
//	std::cerr << " Break Point A\n";

	while (true) {
		BorderCollision(ball, width, height, size);
        BallCollisionBar(ball, bar, size, ManyBlocks);
        
		EraseBall(ball, size);
		BallMovement(ball, size);
        RenderBall(ball, size);
		
		corner_coorBuff(119, 29);
		Sleep(15);
	}
	
	getch();
	
	return 0;
}
