using namespace std;

#ifndef hopper_h
#define hopper_h

class Hopper
{
    private:
    int beans;

    public:
    int grind();
    int getBeans();
    Hopper(int cups);
    ~Hopper();
};

#endif