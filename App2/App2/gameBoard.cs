using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App2
{
    public class gameBoard
    {
        private string[,] gameBoardObj;
        private int boardSize;

        public gameBoard()
        {
            gameBoardObj = new string[4, 4];
            boardSize = 4;
        }



        public gameBoard(int size)
        {
            gameBoardObj = new string[size + 1, size + 1];
            boardSize = size + 1;
        }

        public void initBoard(gameBoard board)
        {
            for (int i = 1; i < board.boardSize; i++)
            {
                for (int j = 1; j < board.boardSize; j++)
                {
                    board.gameBoardObj[i, j] = "*";
                }

            }

            for(int i = 0; i< board.boardSize; i++)
            {
                board.gameBoardObj[0,i] = "0";
                board.gameBoardObj[i, 0] = "0";
            }

        }

        public int getSize()
        {
            return boardSize;
        }

        public string[,] getGameBoard()
        {
            return gameBoardObj;
        }

        public int checkColumn(gameBoard board, int row, int col)
        {
            int colResult = 0;
            for (int i = 1; i < board.getSize(); i++)
            {
                if (board.gameBoardObj[i, col] == "X")
                    colResult++;
                else if (board.gameBoardObj[i, col] == "O")
                    colResult--;
            }

            return colResult;
        }

        public int checkRow(gameBoard board, int row, int col)
        {
            int rowResult = 0;
            for (int i = 1; i < board.getSize(); i++)
            {
                if (board.gameBoardObj[i, col] == "X")
                    rowResult++;
                else if (board.gameBoardObj[i, col] == "O")
                    rowResult--;
            }
            return rowResult;
        }

        public void placeMove(int row, int col, gameBoard board, String playerToken)
        {
            board.gameBoardObj[row, col] = playerToken; 
        }

    }
}
