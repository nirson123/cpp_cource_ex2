//
// Created by nir son on 20/03/2021.
//

#include "doctest.h"
#include <string>
#include "Board.hpp"
#include <random>
#include <cstdlib>
#include <cmath>

using namespace ariel;

TEST_CASE("simple post / read"){
    Board board;

    //check horizontal posting
    board.post(0,0,Direction::Horizontal , "hello");
    CHECK(board.read(0,0,Direction::Horizontal,5) == std::string("hello"));

    //check vertical posting
    board.post(1,1,Direction::Vertical,"world");
    CHECK(board.read(1,1,Direction::Vertical,5) == std::string("world"));

    //check overriding messages
    board.post(0,0,Direction::Vertical,"override");
    CHECK(board.read(0,0 , Direction::Vertical , 8) == std::string("override"));
    CHECK(board.read(0,0,Direction::Horizontal,5) == std::string("oello"));

    //check empty spaces read
    CHECK(board.read(0 , 8 , Direction::Horizontal , 12) == std::string("____________"));
    board.post(3,3,Direction::Horizontal,"kkkkkkkkkkkkk");
    CHECK(board.read(0,3,Direction::Vertical , 6) == std::string("l__k__"));
}
TEST_CASE("big numbers"){

    Board board;

    std::random_device rnd;
    unsigned int rand1 = rnd() % (unsigned)int(pow(10,6)) +  (unsigned)int(pow(10,6));
    unsigned int rand2 = rnd() % (unsigned)int(pow(10,6)) +  (unsigned)int(pow(10,6));

    CHECK_NOTHROW(board.post(rand1 , rand2 ,Direction::Vertical , "somerandommessage"));
    CHECK_NOTHROW(board.post(rand1 , rand2 ,Direction::Horizontal , "somerandommessage"));

    CHECK(board.read(rand1-1,rand2,Direction::Vertical,19) == std::string("_somerandommessage_"));
    CHECK(board.read(rand1,rand2-1,Direction::Horizontal,19) == std::string("_somerandommessage_"));
}
TEST_CASE("long string"){

    Board board;

    std::string long_string(pow(10,6), 'a');

    CHECK_NOTHROW(board.post(0,0,Direction::Horizontal,long_string));
    CHECK_NOTHROW(board.post(0,0,Direction::Vertical,long_string));

    CHECK(board.read(0,0,Direction::Horizontal,pow(10,6)) == long_string);
    CHECK(board.read(0,0,Direction::Vertical,pow(10,6)) == long_string);

}
TEST_CASE("weird strings"){

    Board board;

    //characters string
    CHECK_NOTHROW(board.post(0,0,Direction::Horizontal , "!@#$%^&*()_+~`-=[]{}/?.><,\\"));
    CHECK(board.read(0,0,Direction::Horizontal , 27) == std::string("!@#$%^&*()_+~`-=[]{}/?.><,\\"));

    //hebrew string
    CHECK_NOTHROW(board.post(0,0,Direction::Horizontal , "אבגד"));
    CHECK(board.read(0,0,Direction::Horizontal , 4) == std::string("אבגד"));
}
TEST_CASE("empty string"){

    Board board;

    CHECK_NOTHROW(board.post(0,0,Direction::Vertical , ""));
    CHECK(board.read(0,0,Direction::Vertical,0) == std::string(""));

    //read zero chars
    CHECK(board.read(4,4,Direction::Horizontal,0) == std::string(""));

    //read zero chars at occupied location
    board.post(7,7,Direction::Horizontal,"test");
    CHECK(board.read(7,7,Direction::Horizontal,0) == std::string(""));

    //posting empty string should not over ride existing text
    board.post(7,7,Direction::Horizontal,"");
    CHECK(board.read(7,7,Direction::Horizontal,4) == std::string("test"));

    //posting empty string and then reading should return "_"
    board.post(20,20,Direction::Vertical,"");
    CHECK(board.read(20,20,Direction::Vertical,1) == std::string("_"));
}