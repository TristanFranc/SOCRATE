
#ifndef TEMPLATEBUFFERCOMM_H_
#define TEMPLATEBUFFERCOMM_H_

#include <stdlib.h>
template <class T, uint16_t nSize>
class BuffFifo {
public:

	BuffFifo()
	{
        reset();
    }

    void reset()
    {
        in = 0;
        out = 0;
    }

    bool add(T e)
    {
        if( (in + 1) != out )
        {
            data[in++ & (nSize-1)] = e;
            return 1;
        }
        return 0;
    }

    T rem(){
        if (!isEmpty())
        {
            return data[out++ & (nSize-1)] ;
        }
        return data[0];
    }

    bool isEmpty() const{
        return (out == in);
    }

private:
    unsigned int in ;
    unsigned int out;

    T data [nSize];
};


#endif /* TEMPLATEBUFFERCOMM_H_ */
