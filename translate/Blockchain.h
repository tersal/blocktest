#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <vector>

using namespace std;

class Blockchain {
	public:
	
	Blockchain();
	void AddBlock(Block bNew);
	
	private:
	
	uint32_t nDifficulty;
	vector<Block> _vChain;
	
	Block _GetLastBlock() const;
}
	

#endif