#include <vector>

using namespace std;

#ifndef playerheader_h
#define playerheader_h

    class Player
    {
        private:

        int cash;
        vector<int> hand;

        public:
            vector<int> getHand();
            int getCash();
            void giveOrTake(int amount);
            Player();
            ~Player();
    };

#endif