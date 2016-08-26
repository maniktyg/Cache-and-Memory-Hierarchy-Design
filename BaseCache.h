#ifndef __BASE_CACHE_H__
#define __BASE_CACHE_H__

#include <iostream>
#include<stdint.h>
#define ADDR_BITS 32
typedef struct _cacheLine {
    uint32_t tag;
    uint32_t *data; // data points to data stored in 
    		    // cache line. cache line size is
    		    // multiple of 32bits.
    uint32_t LRUStackBits;
    		    // These bits keep track of usage position
    		    // of cache line in LRU stack. MRU cache
    		    // line is represented by the top of the 
    		    // stack, while LRU is the bottom of the
    		    // stack. 'LRUStackBits=0' represents the
    		    // LRU cache line. 
} cacheLine;

class BaseCache{
    private:
    	//cache base parameters
    	uint32_t cacheSize_L1; //in Bytes
    	uint32_t associativity_L1;
    	uint32_t blockSize_L1;  //in Bytes
		
		uint32_t cacheSize_L2; //in Bytes
    	uint32_t associativity_L2;
    	uint32_t blockSize_L2;  //in Bytes
		
		cacheLine **cache_L1;
    	cacheLine **cache_L2;
    	//cache derived parameters
	   //define any additional parameters 
 	   //needed as part of your design
 	   //WRITE ME
	uint32_t *cacheArray;
	uint32_t *lruArray;
	uint32_t lruCnt;
	
	uint32_t readHit_L1;
	unsigned int readMiss_L1;
	uint32_t writeHit_L1;
	uint32_t writeMiss_L1;
	uint32_t hitFlag_L1;
	uint32_t index_L1;
	uint32_t tag_L1;
	uint32_t numLines_L1;
	uint32_t tagBits_L1;
	uint32_t offsetBits_L1;
	uint32_t offset_L1;
	uint32_t numBlocks_L1;
	uint32_t missRate_L1;
	
	uint32_t readHit_L2;
	uint32_t readMiss_L2;
	uint32_t writeHit_L2;
	uint32_t writeMiss_L2;
	uint32_t hitFlag_L2;
	uint32_t index_L2;
	uint32_t tag_L2;
	uint32_t numLines_L2;
	uint32_t tagBits_L2;
	uint32_t offsetBits_L2;
	uint32_t offset_L2;
	uint32_t numBlocks_L2;
	uint32_t missRate_L2;
	
	uint32_t maxHitTime;
	uint32_t minHitTime;
	uint32_t hitTime;
	uint32_t memAccessTime;
	uint32_t memArray[262144][2];
	uint32_t memCnt;
	//cache access statistics
	
	uint32_t numReads;
	uint32_t numWrites;
	uint32_t numReadHits;
	uint32_t numReadMisses;
	uint32_t numWriteHits;
	uint32_t numWriteMisses;

    public:
        //Default constructor to set everything to '0'
        BaseCache();        
        //Constructor to initialize cache parameters and to create the cache 
        BaseCache(uint32_t _cacheSizeL1, uint32_t _associativityL1, uint32_t _blockSizeL1, uint32_t _cacheSizeL2, uint32_t _associativityL2, uint32_t _blockSizeL2);
	//Set cache base parameters
        void setCacheSize(uint32_t _cacheSize); 
        void setAssociativity(uint32_t _associativity);
        void setBlockSize(uint32_t _blockSize);
        
        //Get cache base parameters
	uint32_t getCacheSize(); 
        uint32_t getAssociativity(); 
        uint32_t getBlockSize(); 
	
	//Get cache access statistics
	double getReadHits_L1(); 
	double getReadMisses_L1(); 
	double getWriteHits_L1(); 
	double getWriteMisses_L1(); 
	double getReadHitRate_L1();
	double getReadMissRate_L1();
	double getWriteHitRate_L1();
	double getWriteMissRate_L1();
	double getOverallHitRate_L1();
	double getOverallMissRate_L1();
	
	double getReadHits_L2(); 
	double getReadMisses_L2(); 
	double getWriteHits_L2(); 
	double getWriteMisses_L2(); 
	double getReadHitRate_L2();
	double getReadMissRate_L2();
	double getWriteHitRate_L2();
	double getWriteMissRate_L2();
	double getOverallHitRate_L2();
	double getOverallMissRate_L2();

	//Initialize cache derived parameters
	void initDerivedParams();
	//Reset cache access statistics
	void resetStats();
	//Create cache and clear it
	void createCache();
	//Reset cache
	void clearCache();
	//Read data
	//return true if it was a hit, false if it was a miss
	//data is only valid if it was a hit, input data pointer
	//is not updated upon miss.
	bool read(uint32_t addr, uint32_t *data);
	//Write data
	//Function returns write hit or miss status. 
	bool write(uint32_t addr, uint32_t data);
	bool writeToMem(uint32_t addr, uint32_t data);
	void lruUpdate();
	int writeToL1(uint32_t addr, uint32_t data);
	int writeToL2(uint32_t addr, uint32_t data);
	double getHitTime();
	double getMaxAccessTime();
	double getMinAccessTime();
	/********ADD ANY ADDITIONAL METHODS IF REQUIRED*********/
	
	
	//Destructor to free all allocated memeroy.
	~BaseCache();
};
#endif
