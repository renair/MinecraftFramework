#ifndef _FUNCTIONS

template<typename T>
T changeIndianess(T value)
{
	char* arr = (char*)&value;
	unsigned short size = sizeof(T);
	for(unsigned short i = 0; i < size/2;++i)
	{
		char tmp = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = tmp;
	}
	return *((T*)arr);
}

#endif