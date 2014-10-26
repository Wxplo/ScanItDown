#include "vector.h"

int main () {

}

struct vector* vector_make(size_t capacity) {
	struct vector *vect = malloc(sizeof(size_t) * capacity);
	vect->size = 0;
	vect->capacity = capacity;
	return vect;
}

void vector_push_back(struct vector *vect, int x) {
	(vect->size)++;
	if (vect->size > vect->capacity) 
	{
		vect = realloc(vect, vect->size);
		vect->capacity = vect->size;
	}
	vect->data[vect->size] = x;
	
}

int  vector_pop_back(struct vector *vect, int *x) {
	
	x = &vect->data[vect->size];
	free(&(vect->data[vect->size]));
	(vect->size)--;
	if (vect->size > 0)
	{
		return 1;	
	}
	else 
	{
		return 0;
	}
}

void vector_push_front(struct vector *vect, int x){
	(vect->size++);
	if (vect->size > vect->capacity) 
        {
                vect = realloc(vect, vect->size);
                vect->capacity = vect->size;
        }

	size_t i = vect->size;
	while ( i > 0)
	{
		vect->data[i]=vect->data[i-1];
		i--;
	}
	vect->data[0] = x;
}

int  vector_pop_front(struct vector *vect, int *x){
	x = &(vect->data[0]);
	free(&(vect->data[0]));
	size_t i = 0;
	while ( i < vect->size)
	{
		vect->data[i] = vect->data[i+1];
		i++;
		
	}
	(vect->size)--;
        if (vect->size > 0)
        {
                return 1;
        }
        else        {
                return 0;
        }

}

int vector_insert_at(struct vector *vect, size_t pos, int x){
	vect->data[pos] = x;
	size_t i= 0;
	while ((i < vect->size) && (vect->data[i]< x))
	{
		i++;
	}
	if (pos == 0)
	{
		vector_push_front(vect,x);
	}
	else { 
		if (pos == vect->size) 
		{
			vector_push_back(vect,x);
		}
		else
		{	
			(vect->size)++;
			if (vect->size > vect->capacity)
		        {
            			vect = realloc(vect, vect->size);
                		vect->capacity = vect->size;
        		}
			size_t j = vect->size;
			while (j > i)
			{
				vect->data[j]=vect->data[j-1];	
				j--;
			}
			vect->data[i] = x;
			pos = i;
		}
	}
	if (pos <= vect->size)
	{
		return 1;
	}	
	else
	{
		return 0;
	}

}

int vector_extract_at(struct vector *vect, size_t pos, int *x)	{
	if (pos == 0)
        {
                vector_pop_front(vect,x);
        }
        else {
                if (pos == vect->size-1)
                {
                        vector_pop_back(vect,x);
                }
                else
                {	
			size_t i = pos +1;
			x = &(vect->data[pos]);
			free(&(vect->data[pos]));
                        while (i < vect->size)
                        {
                                vect->data[i]=vect->data[i+1];
                                i++;
                        }
                        (vect->size)--;
                }
        }
        if ((vect->size == 0)||(pos >= vect->size))
        {
                return 0;
        }
        else
        {
                return 1;
        }
		
}

struct vector* vector_clone(struct vector *vect) {
	struct vector *vect_copy = vector_make(vect->capacity);
	vect_copy->size = vect->size;
	for (size_t i = 0; i <= vect->size ;i++)
	{
		vector_push_back(vect_copy,vect->data[i]);
		
	}
	return vect_copy;
}


