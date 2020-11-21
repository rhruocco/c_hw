namespace playerHeader
{
    class Player
    {
        int cash;
        vector<int> hand;
        public:
            vector<int> getHand();
            int getCash();
            void giveOrTake(int amount);
            void Player();
    }
}