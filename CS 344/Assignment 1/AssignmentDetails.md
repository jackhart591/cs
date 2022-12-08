# Introduction

In this assignment, you'll write a program that will introduce you to programming in C on UNIX based systems.
Learning Outcomes

    How to write a C program to solve a problem? (Module 1 MLO 4)
    How do you interact with the user in C programs? (Module 1 MLO 6)
    How are C programs transformed into an executable form? (Module 1 MLO 7)
    Define programming language constructs in C (Module 2 MLO 1)
    Describe structure data types of C programming language (Module 2 MLO 3)
    What are pointers and how is this mechanism supported in C? ((Module 2 MLO 4)
    Describe memory allocation in Unix (Module 2 MLO 5)
    Explain how to create and manipulate strings in C (Module 2 MLO 6)

# Instructions

Write a program that

    Reads a CSV file with movie data that is provided to the program as an argument
    Processes the data in the file to create structs to hold data for each movie
    Creates a linked list of all these structs
    Gives user choices to ask questions about the movies in the data
    Prints out the data about the movies per user choice

# Format of the CSV File

Here is a sample file whose format corresponds to the format of the CSV file your program will be tested with.

    The first line in the input file will always be the header line containing the column headers (i.e., it will not have data for a movie).
    All the other lines will have the data for a movie in valid format and no columns will be missing.
    The file will not have any empty lines.
    The file will contain data for at least one movie.
    Don't assume a maximum number of movies in the file.
    Commas appear as delimiters between columns, but will not appear in the values of any columns.
    The name of the input file will be less than 50 characters and will not contain any spaces.
    Don't assume that the input file name will have a particular extension.

This file has the following columns:

    Title
        This is a string with the movie title. 
        E.g., Iron Man 2
        You cannot assume a maximum length of the movie title.
    Year
        This is a 4 digit integer value for the year the movie was released
        It's value will be between 1900 and 2021 (inclusive of these years).
        E.g., 2010
    Languages
        The language or languages in which the movie was released.
        One or more string values that are always enclosed within []
        Multiple values are separated by semi-colons.
        E.g,
            [English;Portuguese;Spanish]
            [English;French]
            [English]
        You can assume that the maximum number of languages any movie can be released in is 5.
        You can assume that the maximum length of a particular language is 20 characters.
        You cannot assume any particular case for the letters in the language.
            E.g., don't assume that the first letter is upper case, or that all letters are lowercase.
    Rating Value
        A number between 1 and 10 (inclusive of both 1 and 10)
        It can be an integer or a double with one digit after the decimal point
        E.g.,
            5
            8.7

# Program Functionality
Process the input file

When your program starts it must read all data from the file and process it. After processing the file, the program must print the following message to stdout

"Processed file XYZ and parsed data for M movies"

where XYZ is the name of the file that has been process and M is the number of movies whose data has been processed (this will be 1 less than than the number of lines in the file because the first line has the column headers).

E.g., Processed file movies_sample_1.csv and parsed data for 24 movies
Interactive Functionality

Next your program should display a menus of interactive choices to the user and process the selected choice as described below. For the text of messages to print, see the section "Sample Program Execution."

1. Show movies released in a specified year

    If the user chooses this option, then ask them to enter a year and
        Display the names of all the movies released in that year, one on each line
    If the data doesn't have any movies released in that year, print a message about this. 
    Your program can assume that the user will enter a 4 digit integer for the year between 1900 and 2021 (inclusive of these years)

2. Show highest rated movie for each year

    If the user chooses this option, then for each year for which at least one movie was released, display a movie that had the highest rating along with the year and the rating with one line per year.
        In case of ties, display any one movie that had the highest rating that year.
    Display the data in the form: YYYY RatingValue MovieTitle
    The data doesn't have to be sorted by year or by rating value.
    E.g.,
        2010 8.5 Avengers: Infinity War
        2012 8.1 The Avengers

3. Show movies and their year of release for a specific language

    If the user chooses this option, ask them to enter a language and
        For all movies released in the specified language
        Display the year of release and the movie title, one line per movie
    If the data doesn't include any movie released in this language, print a message about it.
    You should only do an exact match on the language entered by the user
        E.g., "English" shouldn’t match "english"
    You can assume that the length of the language string entered by the user will be less than 20 character.

4. Exit

    If the user choose this option, the program should exit.

# Notes:

    For the interaction choice if  the user enters an incorrect integer (i.e., something other than 1 to 4), print an error message and again present the 4 choices to the user. 
    You can assume that when the program asks user to enter an integer, the user will indeed enter an integer (i.e., you don't need to verify the data type of the user input).
    Don't assume that the languages in the test file will be the same as the ones that appear in the sample file.
    Don’t make an assumption about the number of distinct languages that can appear in the test file.

#Technical Requirements

Your program is required to

    Read data from the file line by line
    Break-up the line into tokens
    Create a struct called movie with the data for that line
    Create a linked list containing all the movie structures

See the Resources section (below) to access sample code that you can adapt to meet these technical requirements.
#Sample Program Execution

Here is a complete example of executing the assignment with the provided sample CSV file.

$ ./movies movies_sample_1.csv 
Processed file movies_sample_1.csv and parsed data for 24 movies

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 1
Enter the year for which you want to see movies: 1999
No data about movies released in the year 1999

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 1
Enter the year for which you want to see movies: 2012
The Avengers
Rise of the Guardians
Anna Karenina

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 2
2008 7.9 Iron Man
2009 7.6 Sherlock Holmes
2010 7.0 Iron Man 2
2013 7.2 Iron Man 3
2017 7.9 Thor: Ragnarok
2012 8.1 The Avengers
2016 7.8 Captain America: Civil War
2018 8.5 Avengers: Infinity War
2015 7.4 Avengers: Age of Ultron
2011 7.0 Thor
2014 7.8 Captain America: The Winter Soldier
2003 6.6 Right on Track

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 3
Enter the language for which you want to see movies: English
2008 The Incredible Hulk
2009 Sherlock Holmes
2008 Iron Man
2010 Iron Man 2
2013 Iron Man 3
2017 Thor: Ragnarok
2012 The Avengers
2016 Doctor Strange
2018 Avengers: Infinity War
2015 Avengers: Age of Ultron
2011 Thor
2013 Thor: The Dark World
2017 Spider-Man: Homecoming
2011 Captain America: The First Avenger
2016 Captain America: Civil War
2015 Ant-Man
2014 Captain America: The Winter Soldier
2018 Mary Queen of Scots
2016 Revolting Rhymes Part One
2017 The Glass Castle
2016 Free Fire
2003 Right on Track
2012 Rise of the Guardians
2012 Anna Karenina

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 3
Enter the language for which you want to see movies: Punjabi
No data about movies released in Punjabi

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 5
You entered an incorrect choice. Try again.

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 4
$

# Hints

    Code the functionality incrementally, constantly testing it and using version control (e.g., Git) to track changes.
        You can use the Grading Rubric as a guide to incrementally develop the functionality.
    To convert a string to int, you can use the function atoi 

    Links to an external site..

    To convert a string to a double, you can use the function strtod 

Links to an external site..
To extract tokens from a string, use strtok_r
Links to an external site. instead of strtok.
To print a variable of data type double to one decimal space, use "%.1f" for this variable in the format string passed to printf
Links to an external site..
