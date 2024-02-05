//THE2
//By Filiz Ipek Oktay- 30780

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//The Node Structures of each files/DLL
struct stockNode{
    string resourceName;
    int resourceQuantity;
    stockNode *next;
    stockNode *prev;
};

struct consumpNode{
    char buildType;
    vector<int> consumpQtys;
    consumpNode *next;
    consumpNode *prev;
};

struct colonyNode{
    char buildType;
    int emptyBlocks2TheLeft;
    colonyNode *next;
    colonyNode *prev;
};

//Deleting Function for the option number 8
int deletDLL(stockNode* &headStock, consumpNode* &headCons, colonyNode* &headCol){
    cout << "Clearing the memory and terminating the program.\n";

    //Deleting the Stock DLL
    stockNode* temp;
    while(headStock != nullptr){
        temp = headStock->next;
        delete headStock;
        headStock = temp;
    }

    //Deleting the Consumption DLL
    consumpNode* temp1;
    while (headCons != nullptr){
        temp1 = headCons->next;
        delete headCons;
        headCons = temp1;
    }

    //Deleting the Colony DLL
    colonyNode* temp2;
    while (headCol != nullptr){
        temp2 = headCol->next;
        delete headCol;
        headCol = temp2;
    }

    //Returning 0 in order to be used in terminating the program, will be used with return command
    return 0;
}

//Boolean function that returns true if the building type input is valid i.e. consumption DLL has the building type and false if not
bool buildCheck(consumpNode* &checker1, string &buildingType){
    while(checker1 != nullptr){
        //Checking whole DLL
        if(buildingType.length() == 1 && checker1->buildType == buildingType[0]){
            return true;
        } else {
            checker1 = checker1->next;
        }
    }
    return false;
}

//Boolean function that returns true if the building type input is valid i.e. colony DLL has the building type and false if not
bool buildCheckCol(colonyNode* &checker2, string &buildingType){
    //Checking whole DLL
    while(checker2 != nullptr){
        if(buildingType.length() == 1 && checker2->buildType == buildingType[0]){
            return true;
        } else {
            checker2 = checker2->next;
        }
    }
    return false;
}

//Consuming or loading the resources in the Stock
void changeRes(stockNode* &headStock, consumpNode* &headCons, string &buildingType, bool &consume){

    //Checking if the building type matches
    consumpNode* temp = headCons;
    vector<int> consVec;
    while(temp != nullptr){
        if(temp->buildType == buildingType[0]){
            consVec = temp->consumpQtys;
            break;
        }
        temp = temp->next;
    }

    //Consuming or loading
    stockNode* temp1 = headStock;
    int j = 0;
    while(temp1 != nullptr){ //The size of the consVec will be equal to number of stock nodes
        if(consume){ //When buildings are being constructed
            temp1->resourceQuantity -= consVec[j];
        }else{ //When buildings are being destroyed
            temp1->resourceQuantity += consVec[j];
        }
        temp1 = temp1->next;
        j++;
    }
}

//Printing DLL without dashes
void printDLL(colonyNode* &headCol){
    cout << "Colony DLL:\n";
    colonyNode* traverser = headCol;

    //Printing First Part
    while (traverser != nullptr) {
        cout << traverser->buildType;
        traverser = traverser->next;
    }
    traverser = headCol;
    cout << endl;

    //Printing Second Part
    while (traverser != nullptr) {
        cout << '(' << traverser->emptyBlocks2TheLeft << ')' << traverser->buildType;
        traverser = traverser->next;
    }
    cout << endl;
}

//Printing DLL Reversed
void printRevDLL(colonyNode* &tailCol){
    cout << "(Reverse) Colony DLL:\n";
    colonyNode* traverser = tailCol;
    while(traverser != nullptr){
        cout << traverser->buildType;
        traverser = traverser->prev;
    }
    cout << endl;
}

//Printing with Dashes
void printWDashes(colonyNode* &headCol){
    cout << "Colony DLL:\n";
    colonyNode* traverser = headCol;
    while(traverser != nullptr){
        if(traverser->emptyBlocks2TheLeft == 0){
            cout << traverser->buildType;
        } else {
            for(int i = 0; i < traverser->emptyBlocks2TheLeft; i++){
                cout << "-";
            }
            cout << traverser->buildType;
        }
        traverser = traverser->next;
    }
    cout << endl;
}

//Printing with Dashes Reversed
void printRevWDashes(colonyNode* &tailCol){
    cout << "(Reverse) Colony DLL:\n";
    colonyNode* traverser = tailCol;
    while(traverser != nullptr){
        cout << traverser->buildType;
        if(traverser->emptyBlocks2TheLeft != 0){
            int dashes = traverser->emptyBlocks2TheLeft;
            for(int i = 0; i < dashes; i++){
                cout << "-";
            }
        }
        traverser = traverser->prev;
    }
    cout << endl;
}

//Opening the files and promting if the file does not open until the valid input
void fileFunc(string &filename, ifstream &file, string &filetype){
    file.open(filename.c_str()); //Opening the stock file
    while(file.fail()){
        cout << "Unable to open the file " << filename << ". Please enter the correct " << filetype << " file name:\n"; //Asking for the valid file name
        cin >> filename;
        file.open(filename.c_str());
    }
}

//Function for checking if the stock is enough when loading the colony
void suffStock(stockNode* &headStock, consumpNode* &headCons, colonyNode* &headCol, bool &flag2){
    colonyNode* ptrCol = headCol;
    string inSuffRes;

    //Checking each DLL
    while(ptrCol != nullptr){
        consumpNode* ptrCons = headCons;
        flag2 = true;

        while(ptrCons != nullptr){
            if(ptrCol->buildType == ptrCons->buildType){
                stockNode* ptrStock = headStock;
                int i = 0;

                while(ptrStock != nullptr && i < ptrCons->consumpQtys.size()){
                    if(ptrStock->resourceQuantity < ptrCons->consumpQtys[i]){ //If the stock resources are less than the required quantity
                        flag2 = false;
                        inSuffRes = ptrStock->resourceName;
                        break;
                    }
                    i++;
                    ptrStock = ptrStock->next;
                }

                if(!flag2)
                    break;
            }
            ptrCons = ptrCons->next;
            if(!flag2)
                break;
        }

        //If not sufficent, promting the proporiate message
        if(!flag2){
            cout << "Insufficient resource " << inSuffRes << endl;
            cout << "Failed to load the colony due to insufficient resources.\n";
            break;
        } else {
            ptrCons = headCons;

            while(ptrCons != nullptr){
                if(ptrCol->buildType == ptrCons->buildType){
                    stockNode* ptrStock = headStock;
                    int i = 0;

                    while(ptrStock != nullptr && i < ptrCons->consumpQtys.size()){
                        ptrStock->resourceQuantity -= ptrCons->consumpQtys[i];
                        i++;
                        ptrStock = ptrStock->next;
                    }
                }
                ptrCons = ptrCons->next;
            }
        }

        ptrCol = ptrCol->next;
    }
}


int main(){
    string filename, sentence, sentence2, sentence3, filetype;
    ifstream file1, file2, file3;
    bool consume = false, flag2;

    cout << "Please enter the stock file name:\n"; //Asking for the file name
    cin >> filename;
    filetype = "stock";

    //Opening the Stock file and asking for a valid filename input
    fileFunc(filename,file1,filetype);

    if(!file1.fail()){
        //Creating a DLL for stock file
        stockNode* headStock;
        stockNode* tailStock;
        //First node for stock DLL
        stockNode* node = new stockNode(); //Dynamic Allocation
        node->prev = nullptr;
        node->next = nullptr;
        headStock = node;
        tailStock = node;

        //Loading the first node with data
        getline(file1,sentence);

        //Converting string into integer
        int quantity;
        stringstream ss;
        string str = sentence.substr(sentence.find(' ') + 1);
        ss << str;
        ss >> quantity;

        node->resourceName = sentence.substr(0, sentence.find(' '));
        node->resourceQuantity = quantity;

        while(getline(file1,sentence)){ //Reading the file
            if(!sentence.empty()){//Ignoring the empty lines

                //Adding new nodes with dynamic allocation
                node = new stockNode();
                node->next = nullptr;
                node->prev = tailStock;
                tailStock->next = node;
                tailStock = node;

                //Converting string to integer
                int quantity;
                stringstream ss;
                string str = sentence.substr(sentence.find(' ') + 1);
                ss << str;
                ss >> quantity;

                //Loading the other nodes node with data
                node->resourceName = sentence.substr(0, sentence.find(' '));
                node->resourceQuantity = quantity;
            }
        }

        cout << "Please enter the consumption file name:\n"; //Asking for the file name
        cin >> filename;
        filetype = "consumption";

        //Opening the Consumption file and asking for a valid filename input
        fileFunc(filename,file2, filetype);

        if(!file2.fail()){
            //Creating a DLL for consumption file
            consumpNode* headCons;
            consumpNode* tailCons;
            //First node for consumption DLL
            consumpNode* node = new consumpNode(); //Dynamic Allocation
            node->prev = nullptr;
            node->next = nullptr;
            headCons = node;
            tailCons = node;

            //Loading the data into DLL
            getline(file2,sentence2);
            vector<int> temp;
            //Converting string to an integer
            istringstream iss(sentence2);
            string word;
            while (iss >> word) {
                int num;
                istringstream ss1(word);
                if (ss1 >> num) {
                    temp.push_back(num);
                }
            }

            node->buildType = sentence2[0];
            node->consumpQtys = temp;


            while(getline(file2, sentence2)){
                if(!sentence2.empty()){
                    //Adding new nodes
                    node = new consumpNode();  //Dynamic Allocation
                    node->next = nullptr;
                    node->prev = tailCons;
                    tailCons->next = node;
                    tailCons = node;

                    vector<int> temp;
                    //Converting string to an integer
                    istringstream iss(sentence2);
                    string word;
                    while (iss >> word) {
                        int num;
                        istringstream ss1(word);
                        if (ss1 >> num) {
                            temp.push_back(num);
                        }
                    }
                    node->buildType = sentence2[0];
                    node->consumpQtys = temp;

                }
            }

            cout << "Please enter the colony file name:\n"; //Asking for the file name
            cin >> filename;
            filetype = "colony";

            //Opening the Colony file and asking for a valid filename input
            fileFunc(filename, file3, filetype);

            if(!file3.fail()){
                //Reading the Colony line
                getline(file3,sentence3);
                colonyNode* tailCol = nullptr;
                colonyNode* headCol = nullptr;

                //Counting the empty blocks to the left with colony line
                int count = 0;
                for(int i = 0; i < sentence3.length(); i++){
                    if(sentence3[i] == '-'){
                        count++;
                    } else {
                        //Adding new nodes
                        colonyNode* node = new colonyNode(); //Dynamic Allocation
                        node->buildType = sentence3[i];
                        node->emptyBlocks2TheLeft = count;
                        count = 0; //Updating the count when using it for the next building
                        node->next = nullptr;
                        node->prev = tailCol;

                        if(tailCol == nullptr)
                            headCol = node;
                        else
                            tailCol->next = node;
                        tailCol = node;
                    }
                }

                //Checking the resources, promting if they are not enough
                suffStock(headStock, headCons, headCol, flag2);
                if(!flag2)
                    return deletDLL(headStock, headCons, headCol);

                //Displaying the menu
                cout << "Please enter your choice:\n";
                cout << "1. Construct a new building on the colony\n";
                cout << "2. Destruct/Disassemble a building from the colony\n";
                cout << "3. Print the colony\n";
                cout << "4. Print the colony in reverse\n";
                cout << "5. Print the colony while showing inner empty blocks\n";
                cout << "6. Print the colony while showing inner empty blocks in reverse\n";
                cout << "7. Print the stock\n";
                cout << "8. Exit\n";

                //Getting the input
                int choice = 0;
                cin >> choice;

                //Options
                while(choice != 8){

                    //Construct a new building
                    if(choice == 1){
                        string buildingType;
                        int index;
                        bool flag2 = false;

                        cout << "Please enter the building type:\n";
                        cin >> buildingType;
                        consumpNode* checker1 = headCons;

                        //Checking if building type is valid
                        while(!buildCheck(checker1,buildingType)){
                            checker1 = headCons;
                            cout << "Building type " << buildingType << " is not found in the consumption DLL. Please enter a valid building type:\n";
                            cin >> buildingType;
                        }

                        // Checking the stock
                        checker1 = headCons;
                        consume = true;
                        string insufRes;


                        while (checker1 != nullptr) {//consumption DLL
                            if (buildingType[0] == checker1->buildType) {
                                stockNode* checker2 = headStock; // Reset checker2 to headStock for each checker1 iteration


                                int j = 0;
                                while (checker2 != nullptr) {

                                    if (checker2->resourceQuantity < checker1->consumpQtys[j]) {
                                        consume = false;
                                        insufRes = checker2->resourceName;
                                        break;
                                    }
                                    j++;
                                    checker2 = checker2->next;
                                }
                            }
                            checker1 = checker1->next;
                        }


                        //If the stock is sufficient, consume the resources
                        if(consume){
                            cout << "Please enter the index of the empty block where you want to construct a building of type " << buildingType << " \n";
                            cin >> index;

                            //Adding the building
                            colonyNode* findempty = headCol;
                            int counter = 0;
                            bool inRange = false;
                            while(findempty != nullptr){//if index is in the range
                                if(findempty->emptyBlocks2TheLeft > 0){
                                    counter += findempty->emptyBlocks2TheLeft;
                                    if(counter >= index){
                                        inRange = true;
                                        break;
                                    }
                                }
                                findempty = findempty->next;
                            }

                            //Two Cases, if index is in range or we need to expand the colony
                            //Index is in the range
                            if(inRange){
                                colonyNode* newBuild = new colonyNode();
                                findempty->emptyBlocks2TheLeft = counter - index;
                                newBuild->prev = findempty->prev;
                                findempty->prev = newBuild;
                                newBuild->next = findempty;
                                newBuild->buildType = buildingType[0];
                                if(newBuild->prev != nullptr)
                                    newBuild->prev->next = newBuild;

                                newBuild->next->prev = newBuild;
                                counter -= 1;

                                if(counter > newBuild->next->emptyBlocks2TheLeft){
                                    newBuild->emptyBlocks2TheLeft = counter - newBuild->next->emptyBlocks2TheLeft -1;
                                }

                                if(index == 1 && newBuild->prev == nullptr){
                                    headCol = newBuild;
                                    newBuild->emptyBlocks2TheLeft = 0;
                                }

                            } else {//Index is out of the range
                                colonyNode* newBuild = new colonyNode();
                                newBuild->buildType = buildingType[0];
                                newBuild->emptyBlocks2TheLeft = index - counter - 1;
                                tailCol->next = newBuild ;
                                newBuild->prev = tailCol;
                                newBuild->next = nullptr;
                                tailCol = newBuild;
                            }

                            //Consuming the resources after adding the building to the colony
                            changeRes(headStock, headCons, buildingType, consume);

                            //Promting the building construction message
                            cout << "Building of type " << buildingType[0] << " has been added at the empty block number: " << index << endl;

                        } else { //The resources are insufficient
                            cout << "Insufficient resource " << insufRes << endl;
                            cout << "Failed to add the building due to insufficient resources.\n";
                        }

                        //Destroying a building
                    }else if(choice == 2){
                        string desBuildType;
                        cout << "Please enter the building type:\n";
                        cin >> desBuildType;

                        colonyNode* checker2 = headCol;
                        if(! buildCheckCol(checker2, desBuildType)){ //Checking the building type
                            cout << "The building of type " << desBuildType[0] << " is not found in the colony.\n" ;
                        } else {
                            //Removing the building from colony DLL
                            colonyNode* traverser = headCol;
                            while(traverser != nullptr){
                                if(traverser->buildType == desBuildType[0]){
                                    if(traverser->next != nullptr){//not in the last
                                        if(traverser == headCol){
                                            headCol = traverser->next;
                                            headCol->emptyBlocks2TheLeft += traverser->emptyBlocks2TheLeft+ 1;
                                            headCol->prev = nullptr;
                                        } else {
                                            colonyNode* previous = traverser->prev;
                                            previous->next = traverser->next;
                                            colonyNode* nextNode = previous->next;
                                            nextNode->emptyBlocks2TheLeft +=  traverser->emptyBlocks2TheLeft + 1;
                                            nextNode->prev = previous;
                                        }
                                        delete traverser;
                                    } else {
                                        colonyNode* previous = traverser->prev;
                                        tailCol->prev = previous->prev;
                                        tailCol = previous;
                                        tailCol->next = nullptr;
                                        tailCol->emptyBlocks2TheLeft += traverser->emptyBlocks2TheLeft + 1;
                                        delete traverser;
                                    }
                                    break;
                                }
                                traverser = traverser->next;
                            }

                            consume = false; //In order to use in function to load the resources back to the stock
                            changeRes(headStock, headCons, desBuildType, consume);
                            cout << "The building of type " << desBuildType[0] << " has been deleted from the colony.\n";
                        }


                        //Printing Colony DLL
                    } else if(choice == 3){
                        printDLL(headCol);

                        //Printing Colony DLL Reversed
                    } else if(choice == 4){
                        printRevDLL(tailCol);

                        //Printing Colony DLL with Dashes
                    } else if(choice == 5){
                        printWDashes(headCol);

                        //Printing Colony DLL with Dashes Reversed
                    } else if(choice == 6){
                        printRevWDashes(tailCol);

                        //Displaying the Stock DLL
                    } else if(choice == 7){
                        stockNode* traverser = headStock;
                        cout << "Stock DLL:\n";
                        while(traverser != nullptr){
                            cout << traverser->resourceName << '(' << traverser->resourceQuantity << ')' << endl;
                            traverser = traverser->next;
                        }
                    }


                    //Asking for option input
                    cin >> choice;
                }

                //Terminating the program
                if(choice == 8){
                    return deletDLL(headStock, headCons, headCol); //Returning 0
                }

            }

        }

    }

    return 0;
}
