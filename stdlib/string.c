#include <kernel/fos.h>

int32_t strlen  (
                char* str
                )
{
    int32_t len=0;
    while (str[len++]);
    return len;
}

int8_t equals(char* first, char* second){
	int32_t c=0, length = strlen(first);
	if(length == strlen(second)){
		for(int i=0;i<length;i++){
			if( first[i] == second[i]){
				c++;
			}	
		}
		if(c == length)
			return 0;
	}
	else{
			return 1;
		}
}
