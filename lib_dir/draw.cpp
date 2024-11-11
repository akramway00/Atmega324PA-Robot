#include "draw.h"
void DrawMap::printSimpleLine(uint8_t data){
    com.transmissionUART(0xE2);
    com.transmissionUART(0x94);
    com.transmissionUART(data);
    _delay_ms(10);
}
void DrawMap::printDoubleLine(uint8_t data)
{
    com.transmissionUART(0xE2);
    com.transmissionUART(0x95);
    com.transmissionUART(data);
    _delay_ms(10);
}
void DrawMap::writeName()
{
    com.sendMessage("Produit par : Mec26tSimple");
}
void DrawMap::drawMapR2(uint8_t sizes[], uint8_t messages[], bool& isSendingCompleted)
{
    int segmentCounter = 0;
    uint8_t nSegments = 6;
    Line tab[nSegments];
    for (uint8_t z = 0; z < nSegments; z++)
    {
        if (sizes[z] != 0)
        {
            tab[segmentCounter].location = messages[z] & 0b00111111;
            if ((messages[z] >> 6) == 0)
            {
                tab[segmentCounter].firstChar = 4;
                tab[segmentCounter].lastChar = 4 + sizes[z];
            }
            else if ((messages[z] >> 6) == 1)
            {
                tab[segmentCounter].firstChar = 22;
                tab[segmentCounter].lastChar = 22 - sizes[z];
            }
            segmentCounter++;
        }
        else {
            break;
        }
    }
    com.transmissionUART('\n');
    com.transmissionUART('\n');
    for (uint8_t i = 0; i <= MATRIX_LIG; i++)
    {
        for (uint8_t j = 0; j <= MATRIX_COL; j++)
        {
            bool printedSegment = false;
            // Affichage du segment en fonction du messages
            for (uint8_t x = 0; x < nSegments; x++)
            {
                if (tab[x].location != 0)
                { 
                    if (i == tab[x].firstChar && tab[x].firstChar == r2LineUp && j == r2ColumnLeft + tab[x].location)
                    {
                        printDoubleLine(r2TopRightLeft);
                        printedSegment = true;
                        break;
                    }
                    else if (i == tab[x].firstChar && tab[x].firstChar == r2LineDown && j == r2ColumnRight - tab[x].location)
                    {
                        printDoubleLine(r2BottomRightLeft);
                        printedSegment = true;
                        break;
                    }
                    else if ((i > tab[x].firstChar && i <= tab[x].lastChar && j == r2ColumnLeft + tab[x].location) || (i < tab[x].firstChar && i >= tab[x].lastChar && j == r2ColumnRight - tab[x].location))
                    {
                        printDoubleLine(r2Vertical);
                        printedSegment = true;
                        break;
                    }
                    
                }
                else
                    break;
            }
            // Affichage du cadre
            if (!printedSegment)
            {
                if (i == 0 && j == 0)
                    printSimpleLine(borderTopLeft);
                
                else if (i == 0 && j == MATRIX_COL)
                    printSimpleLine(borderTopRight);
                
                else if (i == MATRIX_LIG && j == 0)
                    printSimpleLine(borderBottomLeft);
                
                else if (i == MATRIX_LIG && j == MATRIX_COL)
                    printSimpleLine(borderBottomRight);
                else if (0 < i && i < (MATRIX_LIG) && (j == 0 || j == MATRIX_COL))
                    printSimpleLine(borderVertical);
                
                else if (0 < j && j < MATRIX_COL && (i == 0 || i == MATRIX_LIG))
                    printSimpleLine(borderHorizontal);
                // Affichage de la boite
                
                else if (i == boxLineUp && j == boxColumnLeft)
                    printSimpleLine(r1TopLeft);
                
                else if (i == boxLineUp && j == boxColumnRight)
                    printSimpleLine(r1TopRight);
                
                else if (i == boxLineDown && j == boxColumnLeft)
                    printSimpleLine(r1BottomLeft);
                else if (i == boxLineDown && j == boxColumnRight)
                    printSimpleLine(r1BottomRight);
                else if (boxLineUp < i && i < boxLineDown && j == boxColumnLeft)
                    printSimpleLine(r1Vertical);
                else if (boxLineUp < i && i < boxLineDown && j == boxColumnRight)
                    {
                        if (boxOpeningLineUp < i && i < boxOpeningLineDown && j == boxColumnRight)
                        {
                            com.transmissionUART(' ');
                            _delay_ms(10);
                        }
                        
                        else
                            printSimpleLine(r1Vertical);
                        
                    }
                else if (boxColumnLeft < j && j < boxColumnRight && (i == boxLineUp || i == boxLineDown))
                    printSimpleLine(r1Horizontal);
                // Affichage du circuit
                else if (i == r2LineUp && j == r2ColumnLeft)
                    printDoubleLine(r2TopLeft);
                else if (i == r2LineUp && j == r2ColumnRight)
                    printDoubleLine(r2TopRight);
                else if (i == r2LineDown && j == r2ColumnLeft)
                    printDoubleLine(r2BottomLeft);
                else if (i == r2LineDown && j == r2ColumnRight)
                    printDoubleLine(r2BottomRight);
                
                else if (r2LineUp < i && i < r2LineDown && j == r2ColumnLeft)
                {
                    if (i == r2EndLine)
                    {
                        printDoubleLine(r2VerticalLeft);
                    }
                    else
                    {
                        printDoubleLine(r2Vertical);
                    }
                }
                else if (r2LineUp < i && i < r2LineDown && j == r2ColumnRight)
                    printDoubleLine(r2Vertical);
                
                else if ((r2ColumnLeft < j && j < r2ColumnRight && (i == r2LineUp || i == r2LineDown)) || (i == r2EndLine && r2EndLineColumn < j && j < r2ColumnLeft))
                    printDoubleLine(r2Horizontal);
                // Caracteres vides
                else 
                {
                    com.transmissionUART(' ');
                }
            }
        }
        com.sendMessage("\n");
    }
    isSendingCompleted = true;
}
void DrawMap::drawMapR1(Position robotPos, bool& isSendingCompleted, uint8_t table[])
{
    uint8_t nSegments = 6;
    int segmentCounter = 0;
    Line tab[nSegments];
    tab[segmentCounter].location = table[0] & 0b00111111;
    if ((table[0] >> 6) == 0)
    {
        tab[segmentCounter].firstChar = 4;
        tab[segmentCounter].lastChar = 4 + table[1];
    }
    else if ((table[0] >> 6) == 1)
    {
        tab[segmentCounter].firstChar = 22;
        tab[segmentCounter].lastChar = 22 - table[1];
    }
    segmentCounter++;
    tab[segmentCounter].location = table[2] & 0b00111111;
    if ((table[2] >> 6) == 0)
    {
        tab[segmentCounter].firstChar = 4;
        tab[segmentCounter].lastChar = 4 + table[3];
    }
    else if ((table[2] >> 6) == 1)
    {
        tab[segmentCounter].firstChar = 22;
        tab[segmentCounter].lastChar = 22 - table[3];
    }
    segmentCounter++;
    tab[segmentCounter].location = table[4] & 0b00111111;
    if ((table[4] >> 6) == 0)
    {
        tab[segmentCounter].firstChar = 4;
        tab[segmentCounter].lastChar = 4 + table[5];
    }
    else if ((table[4] >> 6) == 1)
    {
        tab[segmentCounter].firstChar = 22;
        tab[segmentCounter].lastChar = 22 - table[5];
    }
    segmentCounter++;
    tab[segmentCounter].location = table[6] & 0b00111111;
    if ((table[6] >> 6) == 0)
    {
        tab[segmentCounter].firstChar = 4;
        tab[segmentCounter].lastChar = 4 + table[7];
    }
    else if ((table[6] >> 6) == 1)
    {
        tab[segmentCounter].firstChar = 22;
        tab[segmentCounter].lastChar = 22 - table[7];
    }
    segmentCounter++;
    tab[segmentCounter].location = table[8] & 0b00111111;
    if ((table[8] >> 6) == 0)
    {
        tab[segmentCounter].firstChar = 4;
        tab[segmentCounter].lastChar = 4 + table[9];
    }
    else if ((table[8] >> 6) == 1)
    {
        tab[segmentCounter].firstChar = 22;
        tab[segmentCounter].lastChar = 22 - table[9];
    }
    segmentCounter++;
    tab[segmentCounter].location = table[10] & 0b00111111;
    if ((table[10] >> 6) == 0)
    {
        tab[segmentCounter].firstChar = 4;
        tab[segmentCounter].lastChar = 4 + table[11];
    }
    else if ((table[10] >> 6) == 1)
    {
        tab[segmentCounter].firstChar = 22;
        tab[segmentCounter].lastChar = 22 - table[11];
    }
    com.transmissionUART('\n');
    com.transmissionUART('\n');
    for (uint8_t i = 0; i <= MATRIX_LIG; i++)
    {
        for (uint8_t j = 0; j <= MATRIX_COL; j++)
        {
            bool printedSegment = false;
            // Vérifier si la position actuelle est comprise entre la colonne du segment et posEndVerticalR2Line
            for (uint8_t x = 0; x < nSegments; x++)
            {
                if (tab[x].location != 0)
                {
                    if (i == tab[x].firstChar && tab[x].firstChar == r2LineUp && j == r2ColumnLeft + tab[x].location)
                    {
                        printDoubleLine(r2TopRightLeft);
                        printedSegment = true;
                        break;
                    }
                    else if (i == tab[x].firstChar && tab[x].firstChar == r2LineDown && j == r2ColumnRight - tab[x].location)
                    {
                        printDoubleLine(r2BottomRightLeft);
                        printedSegment = true;
                        break;
                    }
                    else if ((i > tab[x].firstChar && i <= tab[x].lastChar && j == r2ColumnLeft + tab[x].location) || (i < tab[x].firstChar && i >= tab[x].lastChar && j == r2ColumnRight - tab[x].location))
                    {
                        printDoubleLine(r2Vertical);
                        printedSegment = true;
                        break;
                    }
                }
            }
            // Affichage du cadre
            if (!printedSegment)
            {
                if (i == 0 && j == 0)
                    printSimpleLine(borderTopLeft);
                
                else if (i == 0 && j == MATRIX_COL)
                    printSimpleLine(borderTopRight);
                
                else if (i == MATRIX_LIG && j == 0)
                    printSimpleLine(borderBottomLeft);
                
                else if (i == MATRIX_LIG && j == MATRIX_COL)
                    printSimpleLine(borderBottomRight);
                else if (0 < i && i < (MATRIX_LIG) && (j == 0 || j == MATRIX_COL))
                    printSimpleLine(borderVertical);
                
                else if (0 < j && j < MATRIX_COL && (i == 0 || i == MATRIX_LIG))
                    printSimpleLine(borderHorizontal);
                // Affichage de la boite
                
                else if (i == 2 && j == 4)
                    printSimpleLine(r1TopLeft);
                
                else if (i == 2 && j == 33)
                    printSimpleLine(r1TopRight);
                
                else if (i == 24 && j == 4)
                    printSimpleLine(r1BottomLeft);
                else if (i == 24 && j == 33)
                    printSimpleLine(r1BottomRight);
                else if (2 < i && i < 24 && j == 4)
                    printSimpleLine(r1Vertical);
                else if (2 < i && i < 24 && j == 33)
                    {
                        if (11 < i && i < 15 && j == 33)
                        {
                            com.transmissionUART(' ');
                            _delay_ms(10);
                        }
                        
                        else
                            printSimpleLine(r1Vertical);
                        
                    }
                else if (4 < j && j < 33 && (i == 2 || i == 24))
                    printSimpleLine(r1Horizontal);
                // Affichage du circuit
                else if (i == 4 && j == 40)
                    printDoubleLine(r2TopLeft);
                else if (i == 4 && j == 95)
                    printDoubleLine(r2TopRight);
                else if (i == 22 && j == 40)
                    printDoubleLine(r2BottomLeft);
                else if (i == 22 && j == 95)
                    printDoubleLine(r2BottomRight);
                
                else if (4 < i && i < 22 && j == 40)
                {
                    if (i == 13)
                    {
                        printDoubleLine(r2VerticalLeft);
                    }
                    else
                    {
                        printDoubleLine(r2Vertical);
                    }
                }
                else if (4 < i && i < 22 && j == 95)
                    printDoubleLine(r2Vertical);
                
                else if ((40 < j && j < 95 && (i == 4 || i == 22)) || (i == 13 && 36 < j && j < 40))
                    printDoubleLine(r2Horizontal);
                // Affichage du robot
                else if (robotPos == Position::TOP_NORTH && ((j == 16 && i == 5) || (j == 21 && i == 8)))
                    printDoubleLine(diagonalTopLeft);
                else if (robotPos == Position::TOP_NORTH && (j == 17 || j == 18 || j == 19 || j == 20)  && i == 4)
                    com.transmissionUART('_');
                else if (robotPos == Position::TOP_NORTH && ((j == 21 && i == 5) || (j == 16 && i == 8)))
                    printDoubleLine(diagonalTopRight);
                else if (robotPos == Position::TOP_NORTH && ((j == 16 && i == 6) || (j == 21 && i == 6)))
                    printSimpleLine(borderVertical);
                else if (robotPos == Position::TOP_NORTH && ((j == 16 && i == 7) || (j == 21 && i == 7)))
                {
                    com.transmissionUART(wheels[0]);
                    com.transmissionUART(wheels[1]);
                    com.transmissionUART(wheels[2]);
                    _delay_ms(10);
                }
                
                else if (robotPos == Position::TOP_NORTH && (j == 17 || j == 18 || j == 19 || j == 20)  && i == 8)
                    com.transmissionUART('_');
                // Case BOTTOM_NORTH (i + 13)
                else if (robotPos == Position::BOTTOM_NORTH && ((j == 16 && i == 18 )|| (j == 21 && i == 21)))
                    printDoubleLine(diagonalTopLeft);
                else if (robotPos == Position::BOTTOM_NORTH && (j == 17 || j == 18 || j == 19 || j == 20)  && i == 17)
                    com.transmissionUART('_');
                else if (robotPos == Position::BOTTOM_NORTH && ((j == 21 && i == 18) || (j == 16 && i == 21)))
                    printDoubleLine(diagonalTopRight);
                else if (robotPos == Position::BOTTOM_NORTH && ((j == 16 && i == 19) || (j == 21 && i == 19)))
                    printSimpleLine(borderVertical);
                else if (robotPos == Position::BOTTOM_NORTH && ((j == 16 && i == 20) || (j == 21 && i == 20)))
                {
                    com.transmissionUART(wheels[0]);
                    com.transmissionUART(wheels[1]);
                    com.transmissionUART(wheels[2]);
                    _delay_ms(10);
                }
                
                else if (robotPos == Position::BOTTOM_NORTH && (j == 17 || j == 18 || j == 19 || j == 20)  && i == 21)
                    com.transmissionUART('_');
                // case BOTTOM_SOUTH (j + 13)
                
                else if (robotPos == Position::BOTTOM_SOUTH && ((j == 16 && i == 18) || (j == 21 && i == 21)))
                    printDoubleLine(diagonalTopLeft);
                else if (robotPos == Position::BOTTOM_SOUTH && (j == 17 || j == 18 || j == 19 || j == 20)  && i == 17)
                    com.transmissionUART('_');
                else if (robotPos == Position::BOTTOM_SOUTH && ((j == 21 && i == 18) || (j == 16 && i == 21)))
                    printDoubleLine(diagonalTopRight);
                else if (robotPos == Position::BOTTOM_SOUTH && ((j == 16 && i == 20) || (j == 21 && i == 20)))
                    printSimpleLine(borderVertical);
                else if (robotPos == Position::BOTTOM_SOUTH && ((j == 16 && i == 19) || (j == 21 && i == 19)))
                {
                    com.transmissionUART(wheels[0]);
                    com.transmissionUART(wheels[1]);
                    com.transmissionUART(wheels[2]);
                    _delay_ms(10);
                }
                
                else if (robotPos == Position::BOTTOM_SOUTH && (j == 17 || j == 18 || j == 19 || j == 20)  && i == 21)
                    com.transmissionUART('_');
                // Case TOP_SOUTH
                
                else if (robotPos == Position::TOP_SOUTH && ((j == 16 && i == 5) || (j == 21 && i == 8)))
                    printDoubleLine(diagonalTopLeft);
                else if (robotPos == Position::TOP_SOUTH && (j == 17 || j == 18 || j == 19 || j == 20)  && i == 4)
                    com.transmissionUART('_');
                else if (robotPos == Position::TOP_SOUTH && ((j == 21 && i == 5) || (j == 16 && i == 8)))
                    printDoubleLine(diagonalTopRight);
                else if (robotPos == Position::TOP_SOUTH && ((j == 16 && i == 7) || (j == 21 && i == 7)))
                    printSimpleLine(borderVertical);
                else if (robotPos == Position::TOP_SOUTH && ((j == 16 && i == 6) || (j == 21 && i == 6)))
                {
                    com.transmissionUART(wheels[0]);
                    com.transmissionUART(wheels[1]);
                    com.transmissionUART(wheels[2]);
                    _delay_ms(10);
                }
                
                else if (robotPos == Position::TOP_SOUTH && (j == 17 || j == 18 || j == 19 || j == 20)  && i == 8)
                    com.transmissionUART('_');
                // Caracteres vides
                else 
                {
                    com.transmissionUART(' ');
                }
            }
        }
        com.sendMessage("\n");
        _delay_ms(10);
    }
    writeName();
    isSendingCompleted = true;
}