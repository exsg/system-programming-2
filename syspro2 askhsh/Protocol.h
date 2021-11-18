#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

using namespace std;


class Protocol {
public:
    static void send(string * s, int size, int descriptor);
    static string * receive(int descriptor, int * size);

    static unsigned int bufferSize;
    static void * buffer;
    
    static string to_string(int v);
};

#endif /* PROTOCOL_H */

