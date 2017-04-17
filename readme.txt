A  search engine model based on the IBM model 1, using EM

To compile:- 

g++ a.cpp -o a -fopenmp

The workflow to use the program is as follows :- 

On the first time the user is prompted with the statement :-
"Are you running the code for the first time ?"

If user gives "y" as input :-
Then the pre processing will be carried out.

If user gives "n" as input :-
Then no pre-processing will be done. Instead the files that were 
pruduced during the last step will be re-used.

Then the user will have to input the file path for the file the file to be translated.
Now the user will give the correct file and the scores will be given along with the 
translated version of the original file.

A prompt for giving out the average scores will also be given out.

The whole process can be repeated again till the user wishes to exit.
