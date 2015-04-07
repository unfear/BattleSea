#ifndef UTILITY
#define UTILITY

#include <QTextStream>
#include <iostream>

//#include <QDebug>
//qDebug() << "";

extern QTextStream cout;

enum APP_ROLE {
    UNKNOWN =   -1,
    CLIENT =    0,
    SERVER =    1,
};

enum class SEND_EVENT {
    UNKNOWN_EVENT = -1,
    FIRE = 0,
    BANG = 1,
    MISS = 2
};

class FireEvent {
public:
    int x;
    int y;
    SEND_EVENT event;


    friend std::ostream& operator<< (std::ostream& out, FireEvent& object) {
        out << object.x << " " << object.y << " " << (int)object.event;   //The space (" ") is necessari for separete elements;
        return out;
    }

    friend std::istream& operator>> (std::istream& in, FireEvent& object) {
        in >> object.x;
        in >> object.y;
        int tmpEvent;
        in >> tmpEvent;
        object.event = (SEND_EVENT)tmpEvent;
        return in;
    }
};

#endif // UTILITY
