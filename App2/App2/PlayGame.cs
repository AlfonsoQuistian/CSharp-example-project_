using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App2
{
    class PlayGame
    {

        string playerToken = "*";
        bool continueGame = false;

        public int playGame(int players, gameBoard board, bool Louie)
        {
            bool gameOver = false;
            int result = 0;
            board.initBoard(board);
            //while(!gameOver)
            {
               

                playerTakeTurn(1);

                checkForCat();

                if (players != 1)
                    playerTakeTurn(2);
                else pcTakeTurn();

                int check = checkGameStatus(board);
                result = check;

                
            }

            return result;
        }

        public void playerTakeTurn(int player)
        {
            if (player == 1)
                playerToken = "X";
            else playerToken = "O";



        }

        public void pcTakeTurn()
        {
            playerToken = "O";
        }

        public int checkGameStatus(gameBoard board)
        {
            int result = 0;
            for(int i = 0; i < board.getSize();i++)
            { if ((board.getGameBoard())[0, i] == "3")
                    result = 1;
           

            }
            return result;
        }

        public void updateBoard(int col, int row, gameBoard board)
        {
            board.placeMove(row, col, board, playerToken);
            board.checkColumn(board, row, col);
            board.checkRow(board, row, col);
        }


        public void checkForCat()
        {

        }

    }
}
