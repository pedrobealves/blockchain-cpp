//
// Created by pedrobernardi on 16/05/22.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_HPP
#define BLOCKCHAIN_BLOCKCHAIN_HPP

#include "Transaction.hpp"
#include "Block.hpp"
#include "nlohmann/json.hpp"

#include <filesystem>
#include <fstream>

class Blockchain
{
private:
    // Difficulty for mined transactions
    std::uint32_t difficulty = 3;
    // Max transacations for block
    std::uint32_t maxTransactionsCount = 2;
    // List blocks
    std::vector<Block> chain;
    Block createGenesis()
    {
        // If block created is first
        return Block(0, sha256("Genesis"), difficulty, maxTransactionsCount,{0.0, "Genesis", "Genesis"});
    }
public:

    Blockchain(std::uint32_t difficulty, std::uint32_t maxTransactionsCount)
    {
        this->difficulty = difficulty;
        this->maxTransactionsCount = maxTransactionsCount;
        chain.push_back(createGenesis());
    }

    Blockchain(const std::string filename = "blockchain.json")
    {
        //load(filename);
    }

    void modify(double amount, int indexBlock, int indexTransaction){
        // With index block, access the block and set transaction amount with index
        chain[indexBlock].set_transaction(indexTransaction, amount);
    }

    void push_transaction(Transaction transaction)
    {
        if(chain.back().push_transaction(transaction))
            return;

        // Set difficulty for mined
        chain.back().mine(difficulty);
        chain.push_back({chain.size(), chain.back().calculateHash(), difficulty, maxTransactionsCount, transaction});
    }

    bool validate()
    {
        std::vector<Block>::iterator it;
        // Iterate in blocks
        for(it = chain.begin(); it != chain.end(); ++it)
        {
            Block & currentBlock = *it;
            if(it == (chain.end() - 1))
                continue;

            // Current block for recurse return is invalid
            if(!currentBlock.validate())
            {
                std::cout << "Block " << currentBlock << " is invalid\n";
                return false;
            }

            if(chain.size() > 1 && it != chain.begin())
            {
                Block previousBlock = *(it-1);
                // Is previous hash not equal to current hash
                if(currentBlock.previousHash() != previousBlock.calculateHash())
                {
                    std::cout << "Block " << currentBlock << " is invalid\n";
                    return false;
                }
            }

        }
        // If block not modify data, the block is valid
        return true;
    }

    std::string dump(std::int16_t indent = 4) const
    {
        // For lib nlohmann create pattern json with the attributes
        nlohmann::json output_json = {{"difficulty", difficulty}, {"maxTransactionsCount",maxTransactionsCount}, {"blocks", nlohmann::json::array({})}};
        std::for_each(chain.begin(), chain.end(), std::bind(std::mem_fn(&Block::dump), std::placeholders::_1, std::ref(output_json)));
        return output_json.dump(indent);
    }

    void save(const std::string output_filename = "blockchain", const std::int16_t indent = 4)
    {
        // Set file name with difficulty in name
        std::string file = output_filename + "_" + std::to_string(difficulty) + ".json";
        // Path to save blockchain in folder
        std::filesystem::path output_path = std::filesystem::path(std::filesystem::current_path() / "blockchain" / file);

        if(!std::filesystem::exists(output_path.parent_path()))
            std::filesystem::create_directories(output_path.parent_path());

        // Save file in folder
        std::ofstream output_file(output_path);
        output_file << dump();
    }

    void save(const std::int16_t indent, const std::string output_filename = "blockchain")
    {
        save(output_filename, indent);
    }

    void load(const std::string input_filename = "blockchain.json")
    {
        // Load blockchain in disk to structure
        std::filesystem::path input_path = std::filesystem::path(std::filesystem::current_path() / "blockchain" / input_filename);

        if(!std::filesystem::exists(input_path))
        {
            std::cerr << "Blockchain file does not exists!" << std::endl;
            return;
        }

        nlohmann::json input_json;

        std::ifstream input_file(input_path);
        input_file >> input_json;

        this->difficulty = input_json["difficulty"];
        this->maxTransactionsCount = input_json["maxTransactionsCount"];

        for(const auto & block_json : input_json["blocks"])
            chain.push_back(Block(block_json));
    }

};

#endif //BLOCKCHAIN_BLOCKCHAIN_HPP
