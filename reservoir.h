using namespace std;

#ifndef reservoir_h
#define reservoir_h

class Reservoir
{
    private:

    int cups,temp;

    public:
    void boil();
    void pour();
    int getTemp();
    int getCups();
    void fill(int cups);
    Reservoir();
    ~Reservoir();

};

#endif