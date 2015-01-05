
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <cstdlib>

std::string load(std::string nameOfFile){ //done

    std::ifstream input;
    input.open(nameOfFile.c_str());
    std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    return content;
}

std::string encrypt(std::string content, std::string password){ //also decrypts! :D

    std::string out;
    int p = 0;
    for (int index = 0; index < content.size(); ++index){
            out += content[index] xor password[p] * p % 30;
            ++p;
            if (p >= password.size())
                p = 0;
        }
    return out;
}

void save(std::string nameOfFile, std::string content){ //saves a file with content Content
    char response;
    std::ifstream in(nameOfFile.c_str());
    std::ofstream of;
    if (!in){ //prevents a file from being overwritten unless the user says it's okay (in the nested IF statement).
        in.close();
        of.open(nameOfFile.c_str());
        of << content;
    } else{
        in.close();
        std::cout << "A file with that name already exists. Overwrite? (y/n)\n";
        std::cin >> response;
        if(response == 'y'){
            of.open(nameOfFile.c_str());
            of << content;
        } else {
            std::cout << "Save cancelled. \n";
            }
    }
    of.close();
}


int main(){

    int answer = 0;
    std::string response, data, nameOfFile, password, encrypted;
    char responseC;

    do{

        switch(answer){

        case 0:
            {
            std::cout << "Available commands:\n";
            std::cout << "'0'. list commands\n---\n";
            std::cout << "'1'. load a file\n---\n";
            std::cout << "'2'. save a file\n---\n";
            std::cout << "'3'. encrypt a file\n---\n";
            std::cout << "'4'. decrypt a file\n---\n";
            std::cout << "'5'. display contents in memory\n---\n";
            std::cout << "'6'. close the program\n---\n";
            std::cout << "Note: You must load a file before saving, encrypting, or decrypting.\n";
            break;
            }

        case 1: //Load a file's content into memory, stored in the 'data' variable.
            {
            std::cout << "enter name of file (with extension) to load:\n";
            std::cin >> nameOfFile;
            data = load(nameOfFile.c_str());
            std::cout << "Display contents? (y/n):\n";
            std::cin >> responseC;
            if (responseC == 'y')
                std::cout << data << "\n";
            break;
            }
        case 2: //Save a file's content.
            {
            std::cout << "save file as: ";
            std::cin >> response;
            save(response, data);
            break;
            }
        case 3: //Encrypt the content of 'data' by XORing it against a password.
            {
            std::cout << "Encrypt " << nameOfFile << "?(y/n)\n";
            std::cin >> responseC;
            if (responseC == 'y'){

                    //responseC = '\n';
                    std::cout << "Enter password to decrypt " << nameOfFile << ':' << "\n";
                    std::cin >> password;
                    std::cout << "Encrypting... \n";
                    data = encrypt(data, password);
            }
            break;
            }
        case 4: //Decrypt the content of 'data' by XORing it against a password. If the password is correct,
            {  //the data actually makes sense. If it isn't, the contents will appear to be gibberish.
            std::cout << "Enter password for file: ";
            std::cin >> password;
            std::cout << "Decrypting...\n";
            data = encrypt(data, password); //uses the same same process as encryption.
            std::cout << "Done.\n";
            break;
            }
        case 5: //Display the contents of the Data variable.
            std::cout << "File contents\n-----\n" << data << "\n-----\n";
            break;
        case 6:
            {
                exit(0);
            }
        default:
            std::cout << "Unrecognized command. Enter '0' to view command list\n";
        }
        std::cout << "Enter command:\n";
        std::cin >> answer;

    }while(answer != 6);

    return 0;
}
