#include <iostream>

#include "Blockchain.hpp"


Blockchain transationsRandom(Blockchain blockchain){
    //add transactions
    //the block is mined when the transaction count reaches maximum value
    blockchain.push_transaction({6.0, "Dotty", "Dowling"});
    blockchain.push_transaction({3.14, "Dowling", "Mcguire"});
    blockchain.push_transaction({5.32, "Dotty", "Mcguire"});
    blockchain.push_transaction({2.52, "Steve", "Dotty"});
    blockchain.push_transaction({3.7, "Mcguire", "Steve"});
    blockchain.push_transaction({8.82, "Dotty", "Steve"});
    blockchain.push_transaction({25.1, "Kirkpatrick", "Siana"});
    blockchain.push_transaction({1.10, "Siana", "Kirkpatrick"});
    blockchain.push_transaction({10.7, "Pratt", "Kirkpatrick"});
    blockchain.push_transaction({15.52, "Garfield", "Kirkpatrick"});
    blockchain.push_transaction({8.0, "Gonzales", "Amit"});
    blockchain.push_transaction({8.14, "Amit", "Pratt"});
    blockchain.push_transaction({1.0, "Felix", "Albert"});
    blockchain.push_transaction({12.14, "Albert", "Marriott"});
    blockchain.push_transaction({2.0, "Turnbull", "Zakariyya"});
    blockchain.push_transaction({6.14, "Zakariyya", "Lutz"});
    blockchain.push_transaction({4.32, "Turnbull", "Lutz"});
    blockchain.push_transaction({8.52, "Steve", "Dotty"});
    blockchain.push_transaction({1.7, "Mcguire", "Reilly"});
    blockchain.push_transaction({6.82, "Turnbull", "Reilly"});
    blockchain.push_transaction({20.1, "Devon", "Siana"});
    blockchain.push_transaction({10.10, "Siana", "Devon"});
    blockchain.push_transaction({1.7, "Pratt", "Devon"});
    blockchain.push_transaction({5.52, "Gilmour", "Devon"});
    blockchain.push_transaction({18.0, "Gonzales", "Amit"});
    blockchain.push_transaction({6.14, "Amit", "Pratt"});
    blockchain.push_transaction({8.0, "Tucker", "Albert"});
    blockchain.push_transaction({12.14, "Ieuan", "Emilee"});

    return blockchain;
}

Blockchain createTransation(Blockchain blockchain, double amount, std::string senderKey,  std::string receiverKey ){
    //the block with user data input is mined when the transaction count reaches maximum value
    blockchain.push_transaction({amount, senderKey, receiverKey});

    return blockchain;
}

void validBlock(Blockchain blockchain){
    //validates the blockchain
    std::cout << "Is blockchain valid? " << blockchain.validate() << std::endl;
}

Blockchain loadBlock(std::string file){
    //load blockchain from disk
    Blockchain blockchain;
    blockchain.load(file);

    return blockchain;
}

void showBlock(Blockchain blockchain){
    //Show the blockchain in terminal
    std::cout << blockchain.dump() << std::endl;
}

Blockchain create(std::uint32_t difficulty, std::uint32_t maxTransactionsCount){
    //Create blockchain with difficulty level and transactions per block max
    Blockchain blockchain(difficulty, maxTransactionsCount);
    return blockchain;
}

Blockchain modify(Blockchain blockchain, double amount, int indexBlock, int indexTransaction){
    //Modify amount transaction in block
    blockchain.modify(amount, indexBlock, indexTransaction);
    return blockchain;
}


int main() {
    Blockchain blockchain;
    char selection;

    do {
        //Menu user
        std::cout << "\n Menu";
        std::cout << "\n========";
        std::cout << "\n C - Create";
        std::cout << "\n A - Add";
        std::cout << "\n M - Modify";
        std::cout << "\n V - Verify";
        std::cout << "\n S - Show";
        std::cout << "\n L - Load";
        std::cout << "\n R - Random";
        std::cout << "\n X - Exit";
        std::cout << "\n Enter selection: ";
        std::cin >> selection;

        switch (selection) {
            case 'A' :
            case 'a' : {
                double amount;
                std::string senderKey;
                std::string receiverKey;

                std::cout << "\n Select amount\n";
                std::cin >> amount;
                std::cout << "\n Select sender\n";
                std::cin >> senderKey;
                std::cout << "\n Select receiver\n";
                std::cin >> receiverKey;

                blockchain = createTransation(blockchain, amount, senderKey, receiverKey);
            }
                break;
            case 'C' :
            case 'c' : {
                std::uint32_t difficulty;
                std::uint32_t maxTransactionsCount;
                std::cout << "\n Select difficulty\n";
                std::cin >> difficulty;
                std::cout << "\n Select Max Transactions Count\n";
                std::cin >> maxTransactionsCount;
                blockchain = create(difficulty, maxTransactionsCount);
            }
                break;
            case 'S' :
            case 's' : {
                showBlock(blockchain);
            }
                break;
            case 'M' :
            case 'm' : {
                double amount;
                int indexBlock;
                int indexTransaction;

                std::cout << "\n Select amount\n";
                std::cin >> amount;
                std::cout << "\n Select index block\n";
                std::cin >> indexBlock;
                std::cout << "\n Select index transaction\n";
                std::cin >> indexTransaction;

                blockchain = modify(blockchain, amount, indexBlock, indexTransaction);
            }
                break;
            case 'R' :
            case 'r' : {
                blockchain = transationsRandom(blockchain);
            }
                break;
            case 'L' :
            case 'l' : {
                std::string fileName;

                std::cout << "\n Select file name in blockchain folder\n";
                std::cin >> fileName;

                blockchain = loadBlock(fileName);
            }
                break;
            case 'V' :
            case 'v' : {
                validBlock(blockchain);
            }
                break;
            case 'X' :
            case 'x' : {
                std::cout << "\n To exit the menu";
            }
                return 0;
            default :
                std::cout << "\n Invalid selection";
        }
        std::cout << "\n";
        blockchain.save();
    }while(selection != 'x' && selection !=  'X');
}

