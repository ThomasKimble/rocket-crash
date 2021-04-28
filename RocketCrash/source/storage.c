#include "storage.h"

//*****************************************************************************
//************************ READ AND WRITE FUNCTIONS ***************************
//*****************************************************************************

void writeMaxScores() {
	//Open the file in write mode to overwrite
	file = fopen("/Highscores.txt","w+");
	if (file != NULL) {
		//Print the value in the file
		fprintf(file,"%i\n%i\n%i\n%i\n", max_score[0], max_score[1],
				max_score[2], max_score[3]);
		//Close the file
		fclose(file);
	}
}

void readMaxScores() {
	//Open the file in read mode
	file = fopen("/Highscores.txt","r");
	if (file != NULL) {
		//Read the value and put it into the variable max_score
		fscanf(file,"%i\n%i\n%i\n%i\n", &max_score[0], &max_score[1],
			   &max_score[2], &max_score[3]);

		// close the file
		fclose(file);
	}
}


//*****************************************************************************
//**************************** HIGH SCORE FUNCTIONS ***************************
//*****************************************************************************

void updateHighscores() {
	int i, j;

	readMaxScores();

	for (j = 0; j < 4; j++) {
		if (score > max_score[j]) {
			for (i = 3; i >= j; i--) {
				max_score[i] = max_score[i-1];
			}
			max_score[j] = score;
			break;
		}
	}

	writeMaxScores();
}
