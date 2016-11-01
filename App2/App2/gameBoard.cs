using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App2
{
    class gameBoard
    {
        private string[,] gameBoardObj;
        private int boardSize;

        public gameBoard()
        {
            gameBoardObj = new string[4,4];
            boardSize = 4;
        }

        public gameBoard(int size)
        {
            gameBoardObj = new string[size + 1, size + 1];
            boardSize = size + 1;
        }

        public void initBoard(gameBoard board)
        {

        }

    }
}
