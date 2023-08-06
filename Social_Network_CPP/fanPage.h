#ifndef __FANPAGE_H
#define __FANPAGE_H
#include "Entity.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

class User;


class Fanpage :public Entity
{
private:
    std::vector<User*> m_fans;

public:
    //constructor
    Fanpage(std::string name);
    Fanpage(std::ifstream& inputFile);



    //dtor
    ~Fanpage() = default;


    //add a user to a fan page fans array
    bool addFan(const User* _newFan);

    //remove a user from a fans vector
    bool removeFan(User* newFan);

    //show all the  fan page fans
    void showFans() const;

    bool isUserFan(const User* user)const;


    int getNumOfFans() const;
    int getFansCapacity()const { return (int)m_fans.capacity(); }
    void setNumOfFans(int numFans) { m_fans.reserve(numFans); }

    User* chooseFan();

    void operator+=(User* newFan);


    bool operator>(Fanpage& other) const;
    bool operator<(Fanpage& other) const { return (!(*this > other)); }


    bool operator>(User& other) const;
    bool operator<(User& other) const { return !(*this > other); }

    virtual void save(std::ofstream& outputFile)const override;
    void saveFansNames(std::ofstream& outputFile)const;

};


#endif // __FANPAGE_H