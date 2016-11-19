using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace App2
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class GameBoard : Page
    {
        public GameBoard()
        {
            this.InitializeComponent();
            confirmButton.IsEnabled = false;

        }
        gameBoard board = new gameBoard(4);
        int selectedBox = -1;

        private void playButton_Click(object sender, RoutedEventArgs e)
        {
            int i = 0;

            playGame(1, board, false);
            playButton.IsEnabled = false;
            confirmButton.IsEnabled = true;
        }

        private void confirmButton_Click(object sender, RoutedEventArgs e)
        {
            playGame(1, board, false);//continueGame = true;
        }

        string playerToken = "*";

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
            for (int i = 0; i < board.getSize(); i++)
            {
                if ((board.getGameBoard())[0, i] == "3")
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

        private void textBox0_TextChanged(object sender, TextChangedEventArgs e)
        {
            selectedBox = 0;
            textBox.Text = selectedBox.ToString();
        }
    }
}