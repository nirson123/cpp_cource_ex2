//
// Created by nir son on 20/03/2021.
//

#ifndef CPP_TASK_2_BOARD_HPP
#define CPP_TASK_2_BOARD_HPP

#include <string>
#include "Direction.hpp"

namespace ariel{

    class Board{

        public:
            Board();
            ~Board();
            void post(unsigned int row , unsigned int column , Direction direction ,std::string msg);
            std::string read(unsigned int row , unsigned int column , Direction direction , unsigned int length);
            void show();
    };
}









#endif //CPP_TASK_2_BOARD_HPP
