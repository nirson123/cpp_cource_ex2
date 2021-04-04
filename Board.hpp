//
// Created by nir son on 20/03/2021.
//

#ifndef CPP_TASK_2_BOARD_HPP
#define CPP_TASK_2_BOARD_HPP

#include <string>
#include <map>
#include <tuple>
#include <vector>
#include "Direction.hpp"

namespace ariel{

    class Board{

        private:
            std::vector<std::vector<char>> board;
            unsigned int n_cols;
        public:
            Board();
            ~Board();
            void post(unsigned int row , unsigned int column , Direction direction ,const std::string &msg);
            std::string read(unsigned int row , unsigned int column , Direction direction , unsigned int length) const;
            void show() const;
    };
}









#endif //CPP_TASK_2_BOARD_HPP
