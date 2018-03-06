#pragma once

class UniqueID
{
public:
    static unsigned long long getID() { return GUIDNEXT++;};
    static unsigned long long GUIDNEXT;
}

unsigned long long GUIDNEXT = 1000;