/**
 * @file       BufferTemplate.h
 * @brief      Classe template d'un Buffer de type fifo dont le type et le size sont configurable
 * @author     Marc Juneau
 * @version    0.01
 * @date       20 novembre 2015
 * @warning	   Cette classe est optimisée. Le paramètre nSize doit absolument être une puissance de 2 (ex 8, 16, 32 etc)
 */

#ifndef TEMPLATEBUFFERCOMM_H_
#define TEMPLATEBUFFERCOMM_H_

#include <stdlib.h>
template <class T, uint16_t nSize>
class BuffFifo {
public:
	/**
	 * Constructeur
	 */
	BuffFifo()
	{
        reset();
    }
    /**
     * Remise à zéro des indices
     */
    void reset()
    {
        in = 0;
        out = 0;
    }
    /**
     * Ajoute un élément dans le buffer
     * @param e élément à ajouter
     * @return 1 si l'ajout c'est bien passé.
     */
    bool add(T e)
    {
        if( (in + 1) != out )
        {
            data[in++ & (nSize-1)] = e;
            return 1;
        }
        return 0;
    }
    /**
     * Retire un élément du buffer
     * @return le plus ancient élément entré dans le buffer
     */
    T rem(){
        if (!isEmpty())
        {
            return data[out++ & (nSize-1)] ;
        }
        return data[0];
    }
    /**
     * Valide si le buffer est vide
     * @return 1 si le buffer est vide
     */
    bool isEmpty() const{
        return (out == in);
    }

private:
    unsigned int in ;
    unsigned int out;

    T data [nSize];
};


#endif /* TEMPLATEBUFFERCOMM_H_ */
