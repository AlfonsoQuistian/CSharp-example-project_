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
            button1.Content = "";
            button2.Content = "";
            button3.Content = "";
            button4.Content = "";
            button5.Content = "";
            button6.Content = "";
            button7.Content = "";
            button8.Content = "";
            button9.Content = "";

        }

        
        gameBoard board = new gameBoard(4);
        int moveCount = 0;


        private void playButton_Click(object sender, RoutedEventArgs e)
        {
            int i = 0;

            playGame(1, board, false);
            playButton.IsEnabled = false;
            confirmButton.IsEnabled = true;
        }

        private void confirmButton_Click(object sender, RoutedEventArgs e)
        {

            if (board.isSpotEmpty(comboBoxRow.SelectedIndex + 1, comboBoxColumn.SelectedIndex + 1, board))
                playGame(1, board, false);//continueGame = true;
            else messageBox.Text = "Choice is already taken!";

            readBoard(boar);
        }

        string playerToken = "*";

        private void readBoard(gameBoard board)
        {
            board.getGameBoard()
        }

        public int playGame(int players, gameBoard board, bool Louie)
        {
            bool gameOver = false;
            int result = 0;
            if (moveCount == 0)
            {
                board.initBoard(board);
            }
            //while(!gameOver)
            {


                playerTakeTurn(1, board);
                if (players != 1)
                    playerTakeTurn(2, board);
                else pcTakeTurn();

                int check = checkGameStatus(board);
                result = check;
                moveCount++;

            }

            return result;
        }

        public void playerTakeTurn(int player, gameBoard board)
        {
            if (player == 1)
                playerToken = "X";
            else playerToken = "O";

            board.placeMove(comboBoxRow.SelectedIndex + 1, comboBoxColumn.SelectedIndex + 1, board, playerToken);

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

        private void comboBoxColumn_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            comboBoxColumn.SelectedIndex = 0;
            comboBoxRow.SelectedIndex = 0;
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            comboBoxColumn.SelectedIndex = 1;
            comboBoxRow.SelectedIndex = 0;
        }

        private void button3_Click(object sender, RoutedEventArgs e)
        {
            comboBoxColumn.SelectedIndex = 2;
            comboBoxRow.SelectedIndex = 0;
        }

        private void clearButton1_Click(object sender, RoutedEventArgs e)
        {
            comboBoxColumn.SelectedIndex = -1;
            comboBoxRow.SelectedIndex = -1;
        }

        private void button4_Click(object sender, RoutedEventArgs e)
        {
            comboBoxColumn.SelectedIndex = 0;
            comboBoxRow.SelectedIndex = 1;
        }

        private void button5_Click(object sender, RoutedEventArgs e)
        {
            comboBoxColumn.SelectedIndex = 1;
            comboBoxRow.SelectedIndex = 1;
        }

        private void button6_Click(object sender, RoutedEventArgs e)
        {
            comboBoxColumn.SelectedIndex = 2;
            comboBoxRow.SelectedIndex = 1;
        }

        private void button7_Click(object sender, RoutedEventArgs e)
        {
            comboBoxColumn.SelectedIndex = 0;
            comboBoxRow.SelectedIndex = 2;
        }

        private void button8_Click(object sender, RoutedEventArgs e)
        {
            comboBoxColumn.SelectedIndex = 1;
            comboBoxRow.SelectedIndex = 2;
        }

        private void button9_Click(object sender, RoutedEventArgs e)
        {
            comboBoxColumn.SelectedIndex = 2;
            comboBoxRow.SelectedIndex = 2;
        }
    }
}