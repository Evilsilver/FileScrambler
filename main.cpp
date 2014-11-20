#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

//--**--**-- NOTE --**--**--
//Words surrounded with '*' are functions.
//Words surrounded with '|' are variables.

//prototyping
unsigned int getLength(std::string fileName);
string alphabetize(string source);
string getContent(string fileName);
string scramble(string source, int numOfPasses);
bool doesFileExist(string name);
//all done!

int main()
{
    char input; //used throughout *main* for various user selection purposes.

    cout << "Make sure you have a text file in the same directory as this program!";
    cout << "\nWhat's the text file's name? (including extension!)" <<endl;

    string myFile;
    cin >> myFile; //declares then stores the name of the text file you want to scramble/alphabetize.

    //--**--**-- NOTE --**--**--
    //at this point here, add a check to see if the file the user entered actually exists!

    cout << endl << "--------------" << endl; // makes a spacer, to keep things nice and neat!

    cout <<"File content:\n" << getContent(myFile) << endl << "--------------" << endl;
    cout << "Length of file: " << getLength(myFile);
    cout << " bytes. Do you want to scramble (alphabetize) this file? \n(y/n): ";

    cin >> input;

    if(input =='n'){
        cout << ":(";
        return 0; //that's it, I quit. Done. Kaput. Over.
    }
    cout << "Alphabetize, Randomize, or Quit? (a/r/q)?:";

    string Scrambled;

    cin >> input; //there's that char variable again!

    if (input == 'a'){
        //user decided to alphabetize the file. See *alphabetize* for how this is done.
        Scrambled = alphabetize(getContent(myFile)); //sets |Scrambled| equal to the string returned by *alphabetize()*

    }else if(input == 'r'){
        //user decided to randomize the file. See *scramble* for how this is done.
        cout << "Number of passes to scramble? \n(recommended: between 10 and 20x length of file)" << endl;

        int numPass;
        cin >> numPass; //user specifies how many passes the randomizer should perform.

        Scrambled = scramble(getContent(myFile),numPass); //sets |Scrambled| equal to the string returned by *scramble()*

    }else if (input == 'q'){
        cout << "Stopping. Sorry for wasting your time. :(" << endl;
        return 0; //-sadface- i has a sad.
    }

    cout << "Save name: ";

    string name;        //
    char answer;        // Just a couple variables. Don't mind them.

    do{

    cin >> name;
    ofstream output;

    if (doesFileExist(name) == false){
         //checks to see if another file with the same name exists in the same directory as this program.
         //If it doesn't find one, the program will use the specified name.
         //if it does find one, it will ask the user if they want to overwrite it.

         output.open(name.c_str());
         output << Scrambled;
         return 0;

        } else {

            cout << "That file already exists. Overwrite it? Yes? No? Cancel? (y/n/c)";
            cin >> answer;

            if (answer == 'y'){
                //if the user enters anything other than 'y' or 'c', the program will ask them for a new
                //filename, and checks that new name all over again. if the user enters 'y', then
                //the file with the name in question is overwritten.

                output.open(name.c_str());
                output << Scrambled;
                output.close();
                return 0;
            } else if (answer == 'c'){
                //Save cancelled. sadface.

                cout << "Canceled.";
                return 0;
                } else{
                    cout << "Save name: ";
                }
            }
    } while (true);
}

string scramble(string source, int numOfPasses){

    int randNum;
    unsigned int index; //unsigned. can't have negative indices, now can we?

    cout << "--------------" << endl;
    cout << source << endl;

    do{
        index = 1; //resets  |index| after every pass.



        do{
            srand(time(0)); //re-seeds *rand()* every sub-pass.

            randNum = (rand() % 5); //regenerates the random number every sub-pass.

            if(randNum % 2 == 1){
                //for every sub-pass, the contents of |source[index]| and |source[index - 1]| (if source were a character array, that is.)
                //have a 60% chance of being swapped.

                swap(source.at(index),source.at(index-1));
            }
            ++index;

        }while(index < source.length());

        numOfPasses--;

    }while(numOfPasses > 0);

    cout << source << endl;
    cout << "--------------" << endl; //prints the newly randomized string, with a spacer.

    return source;
}

string alphabetize(string source){
    //not quite as complex as *scramble*

    int numOfSwaps;     //
    unsigned int index; //couple variables. Don't mind them.

    cout << "--------------" << endl;
    cout << source << endl;

    do{ //this function keeps running until the source string is completely alphabetized.

        numOfSwaps = 0; //resets the tally of number of swaps performed to prevent infini-looping.
        index = 1; //resets the index.

        do{

            if(source.at(index) < source.at(index-1)){
                //if the ascii representation of the character in the string at (index)
                //is less than the ascii representation of the character at (index - 1),
                //swap them, and add one to 'numOfSwaps'

                swap(source.at(index),source.at(index-1));
                ++numOfSwaps;

                //cout << source << endl;

                //uncomment the above line (by removing the '//') to print the source string after each sub-pass.
                //NOTE: This will seriously spam your console!!
            }

            ++index;

        }while(index < source.length());

        //cout << source << endl;

        //uncomment the above line (by removing the '//') to print the source string after each pass.
        //NOTE: This too will spam your console!

    }while(numOfSwaps != 0); //ends the loop when the inner-most IF statement does not execute in a pass.

    cout << source << endl;
    cout << "--------------" << endl; //prints the newly alphabetized string, with a spacer.
    return source;
}

unsigned int getLength(string fileName){
    //I have no idea how this one works. I got it off the internet.

ifstream InFile(fileName.c_str());
unsigned int FileLength = 0;
while (InFile.get() != EOF) FileLength++;
InFile.close();
return FileLength;
}

string getContent(std::string fileName){
    //I don't know how this function works, and just like *getLength*, I got it off the 'net.

    ifstream ifs;
    ifs.open(fileName.c_str());
    string str((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    return str;
}

bool doesFileExist(string name){
    //This one should be self-explanatory.

    ifstream file(name.c_str());
    if(!file)
        return false;
    else
        return true;
}
