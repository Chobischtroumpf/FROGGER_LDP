#include "DrawingUtils.hpp"



Fl_Color getVehicleColor(VehicleType type){
    switch(type) {
        case VehicleType::Bus :
            return FL_YELLOW;
        case VehicleType::Car:
            return FL_RED;  
        case VehicleType::Log:
            return fl_rgb_color(55, 33, 0); // Brown
        case VehicleType::Turtle:
            return FL_DARK_GREEN;
        default:
            return FL_WHITE;
    };
}

// Draw a filled rectangle with a frame
void drawFilledRect(int x, int y, int width, int height, Fl_Color fillColor, Fl_Color frameColor ) {
    fl_color(fillColor);
    fl_rectf(x, y, width, height);

    fl_color(frameColor);
    fl_rect(x, y, width, height);
}

void drawSquare(Position pos, int size, Fl_Color fillColor , Fl_Color frameColor ){
    int tileSize = DisplaySettings::tileSize;

    Coordinate coord = Coordinate{pos};
    
    // Set the fill color and draw the filled square
    fl_color(fillColor);
    fl_rectf(coord.x + ( tileSize - size ) / 2 , coord.y + ( tileSize - size ) / 2, size, size);
}

// Draws a vehicle part on the board
void drawVehicle(Vehicle v) {
    int size = 30;
    int tileSize = DisplaySettings::tileSize;

    Coordinate coord = Coordinate{v.position};

    Fl_Color vehicleColor = getVehicleColor(v.getType());

    // Change the color to give an underwater effect to the diving turtles
    if (v.getType() == VehicleType::Turtle && v.isDiving) {

        // Set the new color
        vehicleColor = fl_rgb_color(0, 100, 20);
    }

    fl_color(vehicleColor);

 
        
    // Draw the vechicle
    if (v.getDirection() == Direction::Right) {
        fl_rectf(coord.x - v.length * tileSize , coord.y + ( tileSize - size ) / 2, v.length * tileSize, size);
    } else {
        fl_rectf(coord.x + ( tileSize - size ) / 2, coord.y + ( tileSize - size ) / 2,  v.length * tileSize, size);

    }
       
    
}

// Draw a PNG image on the board
void drawPNG(const char* filename, Coordinate coord, int size) {
    std::string imagePath = "assets/" + std::string(filename);
    Fl_PNG_Image originalImage(imagePath.c_str());

    Fl_Image* scaledImage = &originalImage;

    if (size != 0) {
        double aspectRatio = static_cast<double>(originalImage.w()) / originalImage.h();

        // Calculate the new width and height based on the desired size and aspect ratio
        int newWidth = size;
        int newHeight = static_cast<int>(size / aspectRatio);

        // Resize the image to the new dimensions using copy(), which returns a new Fl_Image
        scaledImage = originalImage.copy(newWidth, newHeight);
    }

    // Calculate position to center the image at the coordinate
    int x = coord.x - scaledImage->w() / 2;
    int y = coord.y - scaledImage->h() / 2;

    // Draw the image at calculated position
    scaledImage->draw(x, y);

    // Clean up if a new image was created
    if (scaledImage != &originalImage) {
        delete scaledImage;
    }
}


void drawTransformedRectangle(int x, int y, int w, int h) {
    fl_begin_polygon();
    fl_vertex(x, y);
    fl_vertex(x + w, y);
    fl_vertex(x + w, y + h);
    fl_vertex(x, y + h);
    fl_end_polygon();
}

void drawPlayer(Position pos, int rotation) {
    
    Coordinate coord = Coordinate{pos};
    int tileSize = DisplaySettings::tileSize;
    int size = 30;  // Size of the frog

    // Calculate the center of the frog
    int centerX = coord.x ; // Already centered
    int centerY = coord.y ;

    // Save the current transformation state
    fl_push_matrix();

    // Translate to the center of the frog and apply rotation
    fl_translate(centerX, centerY);
    fl_rotate(rotation);

    // Draw the body of the frog using the helper function
    fl_color(FL_GREEN);
    drawTransformedRectangle(-size / 2, -size / 2, size, size);

    // Draw eyes
    fl_color(FL_RED);
    drawTransformedRectangle(-size / 4, -size / 4, 5, 5);
    drawTransformedRectangle(size / 4 - 5, -size / 4, 5, 5);

    // Draw rectangular legs
    fl_color(FL_GREEN);
    drawTransformedRectangle(-size / 2 - 5, size / 3, 10, 10);  // Left back leg
    drawTransformedRectangle(size / 2 - 5, size / 3, 10, 10);   // Right back leg
    drawTransformedRectangle(-size / 2 - 5, -size / 3 - 10, 10, 10);  // Left front leg
    drawTransformedRectangle(size / 2 - 5, -size / 3 - 10, 10, 10);   // Right front leg

    // Restore the transformation matrix
    fl_pop_matrix();
}
    
// Draw a tile on the board
void drawTile(Tile tile, Fl_Color fillColor) {
    int tileSize = DisplaySettings::tileSize;

    switch (tile.type)
    {
    case TileType::Classic:
        drawSquare(tile.pos, tileSize, fillColor, FL_BLACK );
        break;
    case TileType::EmptyLilypad:
        drawSquare(tile.pos, tileSize, FL_BLUE, FL_BLACK );
        drawLilyPad(tile.pos, 40);
        break;
    case TileType::CompletedLilypad:
        drawSquare(tile.pos, tileSize, FL_BLUE, FL_BLACK );
        drawLilyPad(tile.pos, 40);
        drawPlayer(Position{tile.pos.x + tileSize/2, tile.pos.y + tileSize/2}, 0);
        break;
    default:
        break;
    }
} 

// Function to draw a lily pad
void drawLilyPad(Position pos, int size) {

    int tileSize = DisplaySettings::tileSize;
    Coordinate coord = Coordinate{pos};

    fl_push_matrix();  // Save the current transformation matrix

    // Translate to the center of the lily pad for better positioning
    fl_translate(coord.x + tileSize / 2, coord.y + tileSize / 2);

    // Set color to green
    fl_color(FL_DARK_GREEN);

    // Begin drawing an ellipse representing the lily pad
    fl_begin_complex_polygon();
    for (int i = 0; i < 360; i++) {
        double angle = i * 3.14159 / 180.0;  // Convert angle to radians
        fl_vertex(cos(angle) * size / 2, sin(angle) * size / 2);
    }
    fl_end_complex_polygon();

    fl_pop_matrix();  // Restore the transformation matrix
}


// Draw the number of lives left
void drawLife(int life) {
    // Build the life indicator string
    std::string heart = "❤️";
    std::string hearts;
    for (int i = 0; i < life; ++i) {
        hearts += heart;
    }

    fl_color(FL_RED);
    fl_font(FL_HELVETICA, 18);
    fl_draw(hearts.c_str(), DisplaySettings::boardCoords.x, DisplaySettings::boardCoords.y - 30);
}

// Draw the game over message
void drawGameOver(bool winOrLose) {
    std::string message = winOrLose ? "You Win!" : "Game Over!";

    // Draw the message at the center of the board
    fl_color( winOrLose ? FL_GREEN : FL_RED);
    fl_font(FL_HELVETICA, 36);
    drawPNG(winOrLose ? "youwin.png" : "gameover.png", Coordinate{DisplaySettings::boardCoords.x + DisplaySettings::boardViewSize/2 , DisplaySettings::boardCoords.y + DisplaySettings::boardViewSize/4 }, 200);
    drawPNG("tryagain.png", Coordinate{DisplaySettings::boardCoords.x + DisplaySettings::boardViewSize/2 , DisplaySettings::boardCoords.y + DisplaySettings::boardViewSize/4 + 100  }, 200);
    drawPNG("menu.png", Coordinate{DisplaySettings::boardCoords.x + DisplaySettings::boardViewSize/2 , DisplaySettings::boardCoords.y + DisplaySettings::boardViewSize/4 + 300}, 200);

}

void drawScore(int score) {
    // Build the score string
    std::string scoreStr = "Score: " + std::to_string(score);

    // Draw the score at the top right corner of the board
    fl_color(FL_WHITE);
    fl_font(FL_COURIER_BOLD, 18);
    fl_draw(scoreStr.c_str(), DisplaySettings::boardViewSize - 50, DisplaySettings::boardCoords.y - 30);
}


void drawSplashScreen() {
    drawPNG("froggers.png", Coordinate{DisplaySettings::windowSize / 2, DisplaySettings::windowSize / 2 - 150 }, 600);
    drawPNG("credits.png",  Coordinate{110 , 100 }, 200);
}


void drawTriangle(int x, int y, int baseSize) {
    fl_color(FL_WHITE);  
    fl_begin_polygon(); 
    fl_vertex(x - baseSize, y - baseSize / 2);  
    fl_vertex(x, y);  
    fl_vertex(x - baseSize, y + baseSize / 2); 
    fl_end_polygon();
}


void drawMenu(int selectedOption, std::vector<std::string> options) {
    // Draw the game title in small size
    drawPNG("froggers.png", Coordinate{ DisplaySettings::windowSize / 2 , 100 }, 300);    
    int optionsNum = options.size();
    for (int i = 0; i < optionsNum; ++i) {
        // Set the color to white if the option is selected
        Fl_Color color = i == selectedOption ? FL_WHITE : FL_GRAY;
        fl_color(color);
        int fontSize = 24;
        fl_font(FL_COURIER_BOLD, fontSize);
        Coordinate coord = Coordinate{DisplaySettings::windowSize / 2 - 50, DisplaySettings::windowSize / 2 + (i - optionsNum/2) * 50};
        // Draw the text
        fl_draw(options[i].c_str(), DisplaySettings::windowSize / 2 - 50, (i - optionsNum/2) * 50 + DisplaySettings::windowSize / 2 );
        // Draw the selector triangle
        if (i == selectedOption) {
            drawTriangle(coord.x - 20, coord.y - fontSize/2 , 16);
        }
    }

    // If the menu is the level selection menu, draw the high score reset hint
    if (options[selectedOption].find("High Score") != std::string::npos) {
            drawPNG("resetHS.png",  Coordinate{DisplaySettings::windowSize / 2, DisplaySettings::windowSize / 2 + 350 }, 400);
    }
}