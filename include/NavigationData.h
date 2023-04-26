using namespace std;

#ifndef NAVIGATION_DATA_H
#define NAVIGATION_DATA_H
class NavigationData {
    private:
    char * timestamp;

    public:
    NavigationData();
    char * getTimestamp();

};


#endif // NAVIGATION_DATA_H