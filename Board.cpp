//
// Created by nir son on 20/03/2021.
//

#include "Board.hpp"
#include <string>
#include <iostream>

using namespace std;

ariel::Board::Board():
n_cols(0), board(0)
{}

ariel::Board::~Board() = default;

void ariel::Board::post(unsigned int row, unsigned int column, ariel::Direction direction,  const std::string &msg) {

    if (direction == Direction::Horizontal){

        //keep mark of the number of columns
        n_cols = (column+msg.length() > n_cols)? column+msg.length() : n_cols;

        //resize if needed
        if(board.size() <= row){board.resize(row+1, vector<char>(0));}
        if(board.at(row).size() < column + msg.length()){board.at(row).resize(column+msg.length(),'_');}

        //post the msg
        for(unsigned int i = 0; i < msg.length(); i++){board.at(row).at(column+i) = msg.at(i);}
    }
    else if (direction == Direction::Vertical){

        n_cols = (column >= n_cols)? column+1 : n_cols;

        //resize if needed
        if(board.size() <= row+msg.length()){board.resize(row+msg.length(), vector<char>(column+1,'_'));}
        for(unsigned int i = row; i < row + msg.length(); i++){
            if(board.at(i).size() <= column){board.at(i).resize(column+1,'_');}
        }

        //post the msg
        for(unsigned int i = 0; i < msg.length(); i++){board.at(row+i).at(column) = msg.at(i);}
    }
}

string ariel::Board::read(unsigned int row, unsigned int column , Direction direction , unsigned int length) const{

    string result;

    if(direction == Direction::Horizontal) {
        for (unsigned int i = 0; i < length; i++) {
            //if nothing is posted at the location, read '_'
            if (board.size() <= row || board.at(row).size() <= column + i) {result += '_';}
            //read from the board
            else{result += board.at(row).at(column+i);}
        }
    }
    else if(direction == Direction::Vertical) {
        for (unsigned int i = 0; i < length; i++) {
            //if nothing is posted at the location, read '_'
            if (board.size() <= row+i || board.at(row+i).size() <= column) {result += '_';}
            //read from the board
            else{result += board.at(row+i).at(column);}
        }
    }

    return result;
}

void ariel::Board::show() const{
    for(unsigned int i = 0; i < board.size(); i++){
        cout << read(i , 0 , Direction::Horizontal, n_cols) << endl;
    }
}
