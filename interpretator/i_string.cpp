#include "i_string.h"

char* update_string(char* s)
{
	int i = 0,m = 0,k = strlen(s);
	char* out = (char*)malloc(k);

	memset(out,0,k);
	while(s[i])
	{
		if(s[i] == '\\')
		{
			if(s[i+1] == 't' || s[i+1] == 'n' || s[i+1] == 'v' || s[i+1] == 'b' || s[i+1] == 'a' || s[i+1] == 'r' || s[i+1] == 'f' || s[i+1] == '?' || s[i+1] == '\\')
			{
				if(s[i+1] == 't')
					out[m] = '\t';
				if(s[i+1] == 'n')
					out[m] = '\n';
				if(s[i+1] == 'v')
					out[m] = '\v';
				if(s[i+1] == 'b')
					out[m] = '\b';
				if(s[i+1] == 'a')
					out[m] = '\a';
				if(s[i+1] == 'r')
					out[m] = '\r';
				if(s[i+1] == 'f')
					out[m] = '\f';
				if(s[i+1] == '\\')
					out[m] = '\\';
				if(s[i+1] == '?')
					out[m] = '\?';
				i++;
				m++;
			}
		}
		else
		{
			if(s[i] != '"')
			{
				out[m] = s[i];
				m++;
			}
		}
		i++;
	}
	if(i!=k)
		realloc(out,i);
	return out;
}