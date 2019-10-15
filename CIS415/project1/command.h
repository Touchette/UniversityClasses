/*
* Description: Project 1 header file. Contains function declarations for the commands listed in the project
*			   Description.
*
* Author: Jared Hall
*
* Date: 09/22/2019
*
* Notes: 
* 1. Do not edit this file.
*/

void listDir(); /*for the ls command*/

void showCurrentDir(); /*for the pwd command*/

void makeDir(char *dirName); /*for the mkdir command*/

void changeDir(char *dirName); /*for the cd command*/

void copyFile(char *sourcePath, char *destinationPath); /*for the cp command*/

void moveFile(char *sourcePath, char *destinationPath); /*for the mv command*/

void deleteFile(char *filename); /*for the rm command*/

void displayFile(char *filename); /*for the cat command*/