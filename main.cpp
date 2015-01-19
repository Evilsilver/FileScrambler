
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <cstdlib>
//adding this here will make it so you never have to type "std::" ever again.
using namespace std;

string load(string nameOfFile){ //done

    ifstream input;
    input.open(nameOfFile.c_str());
    string content((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    return content;
}

string encrypt(string content, string password){ //also decrypts! :D

    string out;
    int p = 0;
    for (int index = 0; index < content.size(); ++index){
            out += content[index] xor password[p] * p % 30;
            ++p;
            if (p >= password.size())
                p = 0;
        }
    return out;
}

void save(string nameOfFile, string content){ //saves a file with content Content
    char response;
    ifstream in(nameOfFile.c_str());
    ofstream of;
    if (!in){ //prevents a file from being overwritten unless the user says it's okay (in the nested IF statement).
        in.close();
        of.open(nameOfFile.c_str());
        of << content;
    } else{
        in.close();
        cout << "A file with that name already exists. Overwrite? (y/n)\n";
        cin >> response;
        if(response == 'y'){
            of.open(nameOfFile.c_str());
            of << content;
        } else {
            cout << "Save cancelled. \n";
            }
    }
    of.close();
}


int main(){

    int answer = 0;
    string response, data, nameOfFile, password, encrypted;
    char responseC;

    do{

        switch(answer){
//adding in the breaks like this will make it easier to read in the long run.
        case 0:
            {
            cout << "Available commands:" << endl;
            cout << "'0'. list commands" << endl 
                << "---" << endl;
            cout << "'1'. load a file" << endl 
                << "---" << endl;
            cout << "'2'. save a file" << endl 
                << "---" << endl;
            cout << "'3'. encrypt a file" << endl 
                << "---" << endl;
            cout << "'4'. decrypt a file" << endl 
                << "---" << endl;
            cout << "'5'. display contents in memory" << endl 
                << "---" << endl;
            cout << "'6'. close the program" << endl 
                << "---" << endl;
            cout << "Note: You must load a file before saving, encrypting, or decrypting." << endl 
                << "---" << endl;
            break;
            }

        case 1: //Load a file's content into memory, stored in the 'data' variable.
            {
            cout << "enter name of file (with extension) to load:\n";
            cin >> nameOfFile;
            data = load(nameOfFile.c_str());
            cout << "Display contents? (y/n):\n";
            cin >> responseC;
            if (responseC == 'y')
                cout << data << "\n";
            break;
            }
        case 2: //Save a file's content.
            {
            cout << "save file as: ";
            cin >> response;
            save(response, data);
            break;
            }
        case 3: //Encrypt the content of 'data' by XORing it against a password.
            {
            cout << "Encrypt " << nameOfFile << "?(y/n)\n";
            cin >> responseC;
            if (responseC == 'y'){

                    //responseC = '\n';
                    cout << "Enter password to decrypt " << nameOfFile << ':' << "\n";
                    cin >> password;
                    cout << "Encrypting... \n";
                    data = encrypt(data, password);
            }
            break;
            }
        case 4: //Decrypt the content of 'data' by XORing it against a password. If the password is correct,
            {  //the data actually makes sense. If it isn't, the contents will appear to be gibberish.
            cout << "Enter password for file: ";
            cin >> password;
            cout << "Decrypting...\n";
            data = encrypt(data, password); //uses the same same process as encryption.
            cout << "Done.\n";
            break;
            }
        case 5: //Display the contents of the Data variable.
            cout << "File contents\n-----\n" << data << "\n-----\n";
            break;
        case 6:
            {
                exit(0);
            }
        default:
            cout << "Unrecognized command. Enter '0' to view command list\n";
        }
        cout << "Enter command:\n";
        cin >> answer;

    }while(answer != 6);

    return 0;
}
