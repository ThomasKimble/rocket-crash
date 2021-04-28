#include <nds.h>
#include <stdio.h>
#include <fat.h>


//*****************************************************************************
//***************************** STORAGE VARIABLES *****************************
//*****************************************************************************

//Scores
int max_score[4];
int score;

//File pointer
FILE* file;



//*****************************************************************************
//************************ READ AND WRITE FUNCTIONS ***************************
//*****************************************************************************

/*
 * VOID WRITEMAXSCORES()
 * This function writes the four highest scores to the "Highscores.txt" file.
 * If there is no file, it is created and the four highest scores are written
 */
void writeMaxScores();

/*
 * VOID READEMAXSCORES()
 * This function reads the four highest scores in the "Highscores.txt" file
 */
void readMaxScores();



//*****************************************************************************
//**************************** HIGH SCORE FUNCTIONS ***************************
//*****************************************************************************

/*
 * VOID UPDATEHIGHSCORES()
 * This function compares the current score with the four highest scores after
 * reading them from the the "Highscores.txt" file. If it is higher than one of
 * the four highest scores, they are updated and written in the
 * "Highscores.txt" file.
 */
void updateHighscores();
