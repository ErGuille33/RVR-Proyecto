#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <stdlib.h>

class Serializable
{
public:

    Serializable():_size(0), _data(0){};

    virtual ~Serializable()
    {
        if ( _data != 0 )
        {
            free(_data);
        }
    }

    virtual void to_bin() = 0;

    virtual int from_bin(char * data) = 0;

    char * data()
    {
        return _data;
    }

    int32_t size()
    {
        return _size;
    }

protected:

    int32_t _size;

    char *  _data;

    void alloc_data(int32_t data_size)
    {
        if ( _data != 0 )
        {
            free(_data);
        }

        _data = (char *) malloc(data_size);
        _size = data_size;
    }
};

#endif /* SERIALIZABLE_H_ */
