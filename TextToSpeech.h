#include <string.h>

void Text_to_Speech(char str[]){
	char cmdlines [100];
	sprintf(cmdlines, "%s %s %s", "TTSAPI.vbs"," ", str);
	system(cmdlines);
}

