#include "renderZone.hpp"

void RenderZone :: drawBoard(sf :: RenderWindow &window){
    window.clear(sf :: Color(222, 184, 135));

    sf :: Vertex line[2];
    //it requires two vertexes to draw a line
    line[0].color = sf :: Color :: Black;
    line[1].color = sf :: Color :: Black;

    //Drawing the horizontal line
    for (int i = 0; i < BOARD_SIZE; ++i){
        int vertexPos = SHIFT_CONST + i * (1.0 * (ZONE_SIZE - 2 * SHIFT_CONST) / (BOARD_SIZE - 1));
        line[0].position = sf :: Vector2f(SHIFT_CONST, vertexPos);
        line[1].position = sf :: Vector2f(ZONE_SIZE - SHIFT_CONST, vertexPos);
        window.draw(line, 2, sf :: Lines);
    }

    //Drawing the vertical line  
    for (int i = 0; i < BOARD_SIZE; ++i){
        int vertexPos = SHIFT_CONST + i * (1.0 * (ZONE_SIZE - 2 * SHIFT_CONST) / (BOARD_SIZE - 1));
        line[0].position = sf :: Vector2f(vertexPos, SHIFT_CONST);
        line[1].position = sf :: Vector2f(vertexPos, ZONE_SIZE - SHIFT_CONST);
        window.draw(line, 2, sf :: Lines);
    }

    //Drawing hoshi point
    std :: vector<sf :: Vector2f> hoshiPosition;
    
    double CeilSize = (1.0 * (ZONE_SIZE - 2 * SHIFT_CONST) / (BOARD_SIZE - 1));

    if(BOARD_SIZE == 9){
        std :: vector<std :: pair<int, int>> point = {
            {2, 2}, {2, 6}, {6, 2}, {6, 6}, {4, 4}
        };

        for (std :: pair<int, int> x : point){
            hoshiPosition.emplace_back(sf :: Vector2f(CeilSize * x.first, CeilSize * x.second));
        }
    }
    if(BOARD_SIZE == 13){
        std :: vector<std :: pair<int, int>> point = {
            {3, 3}, {3, 9}, {9, 3}, {9, 9}, {6, 6} 
        };
        
        for (std :: pair<int, int> x : point){
            hoshiPosition.emplace_back(sf :: Vector2f(CeilSize * x.first, CeilSize * x.second));
        }
    }
    if(BOARD_SIZE == 19){
        std :: vector<std :: pair<int, int>> point = {
            {3, 3}, {3, 9}, {3, 15}, {9, 3}, {9, 9}, {9, 15}, {15, 3}, {15, 9}, {15, 15}  
        };

        for (std :: pair<int, int> x : point){
            hoshiPosition.emplace_back(sf :: Vector2f(CeilSize * x.first, CeilSize * x.second));
        }
    }

    sf :: CircleShape hoshi(5.0f);
    hoshi.setFillColor(sf :: Color :: Black);
    for (sf :: Vector2f x : hoshiPosition){
        hoshi.setPosition(SHIFT_CONST + x.x - hoshi.getRadius(), SHIFT_CONST + x.y - hoshi.getRadius());
        window.draw(hoshi);
    }
}
void RenderZone :: drawPiece(sf :: RenderWindow &window, GoBoard &goBoard, int i, int j){
    if (goBoard.grid[i][j] == Empty) return;
    int vertexX = SHIFT_CONST + i * (1.0 * (ZONE_SIZE - 2 * SHIFT_CONST) / (BOARD_SIZE - 1));
    int vertexY = SHIFT_CONST + j * (1.0 * (ZONE_SIZE - 2 * SHIFT_CONST) / (BOARD_SIZE - 1));

    sf :: CircleShape piece(25.0f);
    piece.setFillColor((goBoard.grid[i][j] == Black ? sf :: Color(30, 30, 40) : sf :: Color(220, 220, 200)));        
    piece.setPosition(vertexX - piece.getRadius(), vertexY - piece.getRadius());
    window.draw(piece);

    piece.setRadius(20.0f);
    piece.setFillColor((goBoard.grid[i][j] == Black ? sf :: Color(15, 15, 20)  : sf :: Color(240, 240, 225)));        
    piece.setPosition(vertexX - piece.getRadius(), vertexY - piece.getRadius());
    window.draw(piece);
}

void RenderZone :: drawAllPieces(sf :: RenderWindow &window, GoBoard &goBoard){
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            drawPiece(window, goBoard, i, j);
        }
    }
}

void RenderZone :: drawMain(sf :: RenderWindow &window, GoBoard &goBoard){
    drawBoard(window);
    drawAllPieces(window, goBoard);
}

void RenderZone :: initSize(sf :: RenderWindow &window){
    WINDOW_SIZE = sf :: VideoMode :: getDesktopMode().height / 2;
    window.setSize({WINDOW_SIZE * ASPECT_RATIO, WINDOW_SIZE});
}

void RenderZone :: normalizeSize(sf :: RenderWindow &window){
    auto [new_width, new_height] = window.getSize();
    if (new_height == WINDOW_SIZE){
        WINDOW_SIZE = new_width / ASPECT_RATIO;
    } else 
    if (new_width == WINDOW_SIZE){
        WINDOW_SIZE = new_height;
    } else {
        WINDOW_SIZE = std :: min(1.0L * new_width / ASPECT_RATIO, 1.0L * new_height);
    }
    window.setSize({WINDOW_SIZE * ASPECT_RATIO, WINDOW_SIZE});
}
