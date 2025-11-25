#include "renderZone.hpp"

void RenderZone :: drawBoard(sf :: RenderWindow &window, GoBoard &goBoard){
    window.clear(metaControls.Background_Color);

    sf :: Vertex line[2];
    //it requires two vertexes to draw a line
    line[0].color = sf :: Color :: Black;
    line[1].color = sf :: Color :: Black;

    //Drawing the horizontal line
    for (int i = 0; i < goBoard.boardSize; ++i){
        int vertexPos = metaControls.SHIFT_CONST + i * (1.0 * (metaControls.ZONE_SIZE - 2 * metaControls.SHIFT_CONST) / (goBoard.boardSize - 1));
        line[0].position = sf :: Vector2f(metaControls.SHIFT_CONST, vertexPos);
        line[1].position = sf :: Vector2f(metaControls.ZONE_SIZE - metaControls.SHIFT_CONST, vertexPos);
        window.draw(line, 2, sf :: Lines);
    }

    //Drawing the vertical line  
    for (int i = 0; i < goBoard.boardSize; ++i){
        int vertexPos = metaControls.SHIFT_CONST + i * (1.0 * (metaControls.ZONE_SIZE - 2 * metaControls.SHIFT_CONST) / (goBoard.boardSize - 1));
        line[0].position = sf :: Vector2f(vertexPos, metaControls.SHIFT_CONST);
        line[1].position = sf :: Vector2f(vertexPos, metaControls.ZONE_SIZE - metaControls.SHIFT_CONST);
        window.draw(line, 2, sf :: Lines);
    }

    //Drawing hoshi point
    std :: vector<sf :: Vector2f> hoshiPosition;
    
    double CeilSize = (1.0 * (metaControls.ZONE_SIZE - 2 * metaControls.SHIFT_CONST) / (goBoard.boardSize - 1));

    if(goBoard.boardSize == 9){
        std :: vector<std :: pair<int, int>> point = {
            {2, 2}, {2, 6}, {6, 2}, {6, 6}, {4, 4}
        };

        for (std :: pair<int, int> x : point){
            hoshiPosition.emplace_back(sf :: Vector2f(CeilSize * x.first, CeilSize * x.second));
        }
    }
    if(goBoard.boardSize == 13){
        std :: vector<std :: pair<int, int>> point = {
            {3, 3}, {3, 9}, {9, 3}, {9, 9}, {6, 6} 
        };
        
        for (std :: pair<int, int> x : point){
            hoshiPosition.emplace_back(sf :: Vector2f(CeilSize * x.first, CeilSize * x.second));
        }
    }
    if(goBoard.boardSize == 19){
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
        hoshi.setPosition(metaControls.SHIFT_CONST + x.x - hoshi.getRadius(), metaControls.SHIFT_CONST + x.y - hoshi.getRadius());
        window.draw(hoshi);
    }
}

sf :: Color blackColor(55, 55, 65), whiteColor(235, 235, 225), borderColor(20, 20, 20, 0);

void RenderZone :: drawPiece(sf :: RenderWindow &window, GoBoard &goBoard, int i, int j, int ghost = 0){
    if ((!!ghost) != (goBoard.grid[i][j] == Empty)) return;
    int vertexX = metaControls.SHIFT_CONST + i * (1.0 * (metaControls.ZONE_SIZE - 2 * metaControls.SHIFT_CONST) / (goBoard.boardSize - 1));
    int vertexY = metaControls.SHIFT_CONST + j * (1.0 * (metaControls.ZONE_SIZE - 2 * metaControls.SHIFT_CONST) / (goBoard.boardSize - 1));

    sf :: CircleShape piece;
    sf :: Color pieceColor(ghost == 1 || goBoard.grid[i][j] == Black ? blackColor : whiteColor);
    pieceColor.a = (1 << (8 - !!ghost)) - 1;
    float pieceRadius = 300.0f / (goBoard.boardSize + 1);

    piece.setRadius(pieceRadius);
    piece.setFillColor(pieceColor - borderColor);   
    piece.setPosition(vertexX - piece.getRadius(), vertexY - piece.getRadius());
    window.draw(piece);

    piece.setRadius(pieceRadius - 5);
    piece.setFillColor(pieceColor); 
    piece.setPosition(vertexX - piece.getRadius(), vertexY - piece.getRadius());
    window.draw(piece);
}

void RenderZone :: drawAllPieces(sf :: RenderWindow &window, GoBoard &goBoard){
    for (int i = 0; i < goBoard.boardSize; ++i){
        for (int j = 0; j < goBoard.boardSize; ++j){
            drawPiece(window, goBoard, i, j);
        }
    }
}
LogBox logbox;
void RenderZone :: drawControlPanel(sf :: RenderWindow &window){
    sf :: Vertex line[2];
    line[0].color = sf :: Color :: Black;
    line[1].color = sf :: Color :: Black;


    //draw control panel
    line[0].position = sf :: Vector2f(metaControls.ZONE_SIZE, metaControls.SHIFT_CONST);

    line[1].position = sf :: Vector2f(metaControls.ZONE_SIZE, metaControls.ZONE_SIZE - metaControls.SHIFT_CONST);
    window.draw(line, 2, sf :: Lines);
    line[0].position = sf :: Vector2f(metaControls.ZONE_SIZE * metaControls.ASPECT_RATIO - metaControls.SHIFT_CONST, metaControls.ZONE_SIZE - metaControls.SHIFT_CONST);
    window.draw(line, 2, sf :: Lines);
    line[1].position = sf :: Vector2f(metaControls.ZONE_SIZE * metaControls.ASPECT_RATIO - metaControls.SHIFT_CONST, metaControls.SHIFT_CONST);
    window.draw(line, 2, sf :: Lines);
    line[0].position = sf :: Vector2f(metaControls.ZONE_SIZE, metaControls.SHIFT_CONST);
    window.draw(line, 2, sf :: Lines);

    
}

void RenderZone :: drawMain(sf :: RenderWindow &window, GoBoard &goBoard){
    drawBoard(window, goBoard);
    drawControlPanel(window);
    drawAllPieces(window, goBoard);
}

void RenderZone :: initSize(sf :: RenderWindow &window){
    WINDOW_SIZE = sf :: VideoMode :: getDesktopMode().height / 2;
    window.setSize({(unsigned int)(WINDOW_SIZE * metaControls.ASPECT_RATIO), WINDOW_SIZE});
}

void RenderZone :: normalizeSize(sf :: RenderWindow &window){
    auto [new_width, new_height] = window.getSize();
    if ((unsigned int)new_height == WINDOW_SIZE){
        WINDOW_SIZE = new_width / metaControls.ASPECT_RATIO;
    } else 
    if ((unsigned int)new_width == WINDOW_SIZE){
        WINDOW_SIZE = new_height;
    } else {
        WINDOW_SIZE = std :: min(1.0L * new_width / metaControls.ASPECT_RATIO, 1.0L * new_height);
    }
    window.setSize({(unsigned int)(WINDOW_SIZE * metaControls.ASPECT_RATIO), WINDOW_SIZE});
}
