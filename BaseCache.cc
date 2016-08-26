#include <iostream>
#include "BaseCache.h"
#include<math.h>
using namespace std;

//WRITE ME
//Default constructor to set everything to '0'
BaseCache::BaseCache() {
cacheSize_L1 = 0;
associativity_L1 = 0;
blockSize_L1 = 0;

cacheSize_L2 = 0;
associativity_L2 = 0;
blockSize_L2 = 0;
}


//WRITE ME
//Constructor to initialize cache parameters, create the cache and clears it
BaseCache::BaseCache(uint32_t _cacheSizeL1, uint32_t _associativityL1, uint32_t _blockSizeL1, uint32_t _cacheSizeL2, uint32_t _associativityL2, uint32_t _blockSizeL2) {
cacheSize_L1 = _cacheSizeL1;
associativity_L1 = _associativityL1;
blockSize_L1 = _blockSizeL1;

cacheSize_L2 = _cacheSizeL2;
associativity_L2 = _associativityL2;
blockSize_L2 = _blockSizeL2;

createCache();

}

//WRITE ME
//Set cache base parameters
void BaseCache::setCacheSize(uint32_t _cacheSize) {}
void BaseCache::setAssociativity(uint32_t _associativity) {}
void BaseCache::setBlockSize(uint32_t _blockSize) {}

//WRITE ME
//Get cache base parameters
//uint32_t BaseCache::getCacheSize() {}
//uint32_t BaseCache::getAssociativity() {}
//uint32_t BaseCache::getBlockSize() {}

//WRITE ME
//Get cache access statistics
double BaseCache::getReadHits_L1() 
{
  return readHit_L1;
}
double BaseCache::getReadMisses_L1() 
{
  return readMiss_L1;
}
double BaseCache::getWriteHits_L1() 
{
  return writeHit_L1;
}
double BaseCache::getWriteMisses_L1() 
{
  return writeMiss_L1;
}
double BaseCache::getReadHitRate_L1() 
{
	unsigned int temp = (readHit_L1*100)/(readHit_L1 + readMiss_L1);
  return (temp);
}
double BaseCache::getReadMissRate_L1() 
{
	unsigned int temp = (readMiss_L1*100)/(readHit_L1 + readMiss_L1);
	missRate_L1 = (readMiss_L1*100)/(readHit_L1 + readMiss_L1);
	return (temp);
}
double BaseCache::getWriteHitRate_L1() 
{
	unsigned int temp = (writeHit_L1*100)/(writeHit_L1 + writeMiss_L1);
  return (temp);
}
double BaseCache::getWriteMissRate_L1() 
{
	unsigned int temp = (writeMiss_L1*100)/(writeHit_L1 + writeMiss_L1);
  return (temp);
}
double BaseCache::getOverallHitRate_L1() 
{
	unsigned int temp = ((readHit_L1 + writeHit_L1)*100)/(readHit_L1 + readMiss_L1 + writeHit_L1 + writeMiss_L1);
  return (temp);
}
double BaseCache::getOverallMissRate_L1() 
{
	unsigned int temp = ((readMiss_L1 + writeMiss_L1)*100)/(readHit_L1 + readMiss_L1 + writeHit_L1 + writeMiss_L1);
  return (temp);
}

/////////////////////////////////////////////////

double BaseCache::getReadHits_L2() 
{
  return readHit_L2;
}
double BaseCache::getReadMisses_L2() 
{
  return readMiss_L2;
}
double BaseCache::getWriteHits_L2() 
{
  return writeHit_L2;
}
double BaseCache::getWriteMisses_L2() 
{
  return writeMiss_L2;
}
double BaseCache::getReadHitRate_L2() 
{
  unsigned int temp = (readHit_L2*100)/(readHit_L2 + readMiss_L2);
  return (temp);
}
double BaseCache::getReadMissRate_L2() 
{
  unsigned int temp = (readMiss_L2*100)/(readHit_L2 + readMiss_L2);
  missRate_L2 = (readMiss_L2*100)/(readHit_L2 + readMiss_L2);
  return (temp);
}
double BaseCache::getWriteHitRate_L2() 
{
  unsigned int temp = (writeHit_L2*100)/(writeHit_L2 + writeMiss_L2);
  return (temp);
}
double BaseCache::getWriteMissRate_L2() 
{
  unsigned int temp = (writeMiss_L2*100)/(writeHit_L2 + writeMiss_L2);
  return (temp);
}
double BaseCache::getOverallHitRate_L2() 
{
  unsigned int temp = ((readHit_L2 + writeHit_L2)*100)/(readHit_L2 + readMiss_L2 + writeHit_L2 + writeMiss_L2);
  return (temp);
}
double BaseCache::getOverallMissRate_L2() 
{
  unsigned int temp = ((readMiss_L2 + writeMiss_L2)*100)/(readHit_L2 + readMiss_L2 + writeHit_L2 + writeMiss_L2);
  return (temp);
}

double BaseCache::getHitTime() 
{
	unsigned int temp = 1 + missRate_L1*(15 + (missRate_L2*(70))/100)/100;
	return (temp);
}

double BaseCache::getMaxAccessTime() 
{
	
	if(numReads == 1)
	{
		maxHitTime = hitTime;
	}
	else if(hitTime > maxHitTime)
	{
		maxHitTime = hitTime;
	}
	return maxHitTime;
}

double BaseCache::getMinAccessTime() 
{
	
	if(numReads == 1)
	{
		minHitTime = hitTime;
	}
	else if(hitTime < minHitTime)
	{
		minHitTime = hitTime;
	}
	return minHitTime;
}

//WRITE ME
//Initialize cache derived parameters
void BaseCache::initDerivedParams() {
}

//WRITE ME
//Reset cache access statistics
void BaseCache::resetStats() {
}

//WRITE ME
//Create cache and clear it
void BaseCache::createCache() 
{
	numLines_L1 = cacheSize_L1/(blockSize_L1 * associativity_L1);
	index_L1 = log2(numLines_L1);
	offsetBits_L1 = log2(blockSize_L1);									//no. of offset bits
	numBlocks_L1 = blockSize_L2/4;										//each array position has 4B.
	tagBits_L1 = 32 - (numLines_L1 + offset_L1);
	cache_L1 = new cacheLine*[numLines_L1];
	for(unsigned int i=0;i< numLines_L1; i++)
	{
		cache_L1[i]=new cacheLine[associativity_L1];
	}
	
	
	numLines_L2 = cacheSize_L2/(blockSize_L2 * associativity_L2);
	index_L2 = log2(numLines_L2);
	offsetBits_L2 = log2(blockSize_L2);									//no. of offset bits
	numBlocks_L2 = blockSize_L2/4;										//each array position has 4B.
	tagBits_L2 = 32 - (numLines_L2 + offset_L2);
	cache_L2 = new cacheLine*[numLines_L2];
	for(unsigned int j=0;j< numLines_L2; j++)
	{
		cache_L2[j]=new cacheLine[associativity_L2];
	}
	
	clearCache();
	
	readHit_L1 = 0;
	readMiss_L1 = 0;
	writeHit_L1 = 0;
	writeMiss_L1 = 0;
	
	readHit_L2 = 0;
	readMiss_L2 = 0;
	writeHit_L2 = 0;
	writeMiss_L2 = 0;
	
	numReads = 0;
	numWrites = 0;
	lruCnt = 0;
	memCnt = 0;
	hitTime = 0;
	maxHitTime = 0;
	minHitTime = 0;
	memAccessTime = 0;
}

//WRITE ME
//Reset cache
void BaseCache::clearCache() 
{
	for(unsigned int i=0;i< numLines_L1;i++)
	{
		for(unsigned int j=0;j<associativity_L1;j++)
		{
			(cache_L1[i][j]).data=new uint32_t[numBlocks_L1];
			(cache_L1[i][j]).LRUStackBits = 0;
			(cache_L1[i][j]).tag = 100000;
			for(unsigned int k=0;k<numBlocks_L1;k++)
			{
				(cache_L1[i][j]).data[k]=0;
			}
		}
	}
	
	for(unsigned int l=0;l< numLines_L2;l++)
	{
		for(unsigned int m=0;m<associativity_L2;m++)
		{
			(cache_L2[l][m]).data=new uint32_t[numBlocks_L2];
			(cache_L2[l][m]).LRUStackBits = 0;
			(cache_L2[l][m]).tag = 100000;
			for(unsigned int n=0;n<numBlocks_L2;n++)
			{
				(cache_L2[l][m]).data[n]=0;
			}
		}
	}
	
}

//WRITE ME
//Read data
//return true if it was a hit, false if it was a miss
//data is only valid if it was a hit, input data pointer
//is not updated upon miss. Make sure to update LRU stack
//bits. You can choose to separate the LRU bits update into
// a separate function that can be used from both read() and write().
bool BaseCache::read(uint32_t addr, uint32_t *data) 
{
	hitFlag_L1=0;
	hitFlag_L2=0;
	
	unsigned int i,j,k, tagShift1, tagShift2;
	offset_L1 = addr & (numBlocks_L1 - 1);					//numBlocks_L1, not original no. of bits as each position in array has 4B.
	uint32_t temp = addr >> offsetBits_L1;					// shifted by original bits to get index.
	index_L1 = (temp & (numLines_L1 - 1));
	tagShift1 = (log2(numLines_L1));
	tag_L1 = temp >> tagShift1;
	
	offset_L2 = addr & (numBlocks_L2 - 1);
	temp = addr >> offsetBits_L2;
	index_L2 = (temp & (numLines_L2 - 1));
	tagShift2 = (log2(numLines_L2));
	tag_L2 = temp >> tagShift2;
	
	numReads++;
	for(j=0;j<associativity_L1;j++)
	{
		if(cache_L1[index_L1][j].tag == tag_L1)
		{
			hitFlag_L1=1;
			readHit_L1++;
			hitTime = 1;
			cache_L1[index_L1][j].LRUStackBits = associativity_L1;
			for(k=j+1;k<associativity_L1;k++)												//update LRUStackBits
			{
				cache_L1[index_L1][j].LRUStackBits = cache_L1[index_L1][j].LRUStackBits - 1;
			}
			*data = 1;
		}
	}
	
	if(hitFlag_L1 == 0)
	{
		for(j=0;j<associativity_L2;j++)
		{
			if(cache_L2[index_L2][j].tag == tag_L2)
			{
				hitFlag_L2=1;
				readHit_L2++;
				readMiss_L1++;
				hitTime = 16;
				cache_L2[index_L2][j].LRUStackBits = associativity_L2;
				for(k=j+1;k<associativity_L1;k++)												//update LRUStackBits
				{
					cache_L2[index_L2][j].LRUStackBits = cache_L2[index_L2][j].LRUStackBits - 1;
				}
				writeToL1(addr, cache_L2[index_L2][j].data[offset_L2]);
				*data = 2;
			}
		}
	}
	
	if(hitFlag_L1 == 0 && hitFlag_L2 == 0)
	{
		for(i=0;i<212144;i++)
		{
			if(memArray[i][0] == addr)
			{
				writeToL1(addr, memArray[i][1]);
				writeToL2(addr, memArray[i][1]);
				break;
			}
		}
		readMiss_L1++;
		readMiss_L2++;
		hitTime = 86;
		return 0;
	}
	else
	{
		return 1;
	}

	

}

//WRITE ME
//Write data
//Function returns write hit or miss status. 
bool BaseCache::write(uint32_t addr, uint32_t data) 
{
	hitFlag_L1=0;
	hitFlag_L2=0;
	
	unsigned int i,j,k, tagShift1, tagShift2;
	offset_L1 = addr & (numBlocks_L1 - 1);					//numBlocks_L1, not original no. of bits as each position in array has 4B.
	uint32_t temp = addr >> offsetBits_L1;					// shifted by original bits to get index.
	index_L1 = (temp & (numLines_L1 - 1));
	tagShift1 = (log2(numLines_L1));
	tag_L1 = temp >> tagShift1;
	
	offset_L2 = addr & (numBlocks_L2 - 1);
	temp = addr >> offsetBits_L2;
	index_L2 = (temp & (numLines_L2 - 1));
	tagShift2 = (log2(numLines_L2));
	tag_L2 = temp >> tagShift2;
	
	numWrites++;
	for(j=0;j<associativity_L1;j++)
	{
		if(cache_L1[index_L1][j].tag == tag_L1)
		{
			hitFlag_L1=1;
			cache_L1[index_L1][j].data[offset_L1] = data;
			cache_L1[index_L1][j].LRUStackBits = associativity_L1;
			for(k=j+1;k<associativity_L1;k++)												//update LRUStackBits
			{
				cache_L1[index_L1][j].LRUStackBits = cache_L1[index_L1][j].LRUStackBits - 1;
			}
			break;
		}
	}
	
	for(j=0;j<associativity_L2;j++)
	{
		if(cache_L2[index_L2][j].tag == tag_L2)
		{
			hitFlag_L2=1;	
			
			cache_L2[index_L2][j].data[offset_L2] = data;
			cache_L2[index_L2][j].LRUStackBits = associativity_L2;
			for(k=j+1;k<associativity_L1;k++)												//update LRUStackBits
			{
				cache_L2[index_L2][j].LRUStackBits = cache_L2[index_L2][j].LRUStackBits - 1;
			}
		}
	}
	
	if(hitFlag_L1==1 && hitFlag_L2 == 1)													//hit in both L1 and L2
	{
		for(i=0;i<262144;i++)
		{
			if(memArray[memCnt][0] == addr)
			{
				memArray[memCnt][1] = data;
			}
		}
		writeHit_L1++;
		writeHit_L2++;
		
		return 1;
	}
	else if(hitFlag_L1==1)																	//L1 hit
	{
		for(i=0;i<262144;i++)																//write data to memory 
		{
			if(memArray[memCnt][0] == addr)
			{
				memArray[memCnt][1] = data;
			}
		}
		writeHit_L1++;
		writeToL2(addr,data);																// write data to lower level cache
		return 1;
	}
	else if(hitFlag_L2==1)																	//L2 hit
	{
		for(i=0;i<262144;i++)																//write data to memory 
		{
			if(memArray[memCnt][0] == addr)
			{
				memArray[memCnt][1] = data;
			}
		}
		writeHit_L2++;
		writeMiss_L1++;
		writeToL1(addr,data);
		return 1;
	}
	else																					//write miss
	{
		for(i=0;i<262144;i++)																//write data to memory
		{
			if(memArray[memCnt][0] == addr)
			{
				memArray[memCnt][1] = data;
			}
		}
		writeMiss_L1++;
		writeMiss_L2++;
		//writeToL2(addr,data);
		return 0;
	}
	
}

bool BaseCache::writeToMem(uint32_t addr, uint32_t data) 
{
	memArray[memCnt][0]=addr;
	memArray[memCnt][1]=data;
	memCnt++;
	return 0;
}

int BaseCache::writeToL2(uint32_t addr, uint32_t data)
{
	unsigned int i, lruEmpty=0, tagShift2;
	
	offset_L2 = addr & (numBlocks_L2 - 1);
	uint32_t temp = addr >> offsetBits_L2;
	index_L2 = (temp & (numLines_L2 - 1));
	tagShift2 = (log2(numLines_L2));
	tag_L2 = temp >> tagShift2;
	
	for(i=0;i<associativity_L2;i++)										//if LRU is empty. write to L2
	{
		if(cache_L2[index_L2][i].LRUStackBits == 0)
		{
			cache_L2[index_L2][i].data[offset_L2] = data; 
			cache_L2[index_L2][i].LRUStackBits = i+1;
			cache_L2[index_L2][i].tag = tag_L2;
			lruEmpty = 1;
			break;
		}
	}
			
	if(lruEmpty == 0)														//write L2 if lru not empty
	{
		for(i=0;i<associativity_L2;i++)										
		{
			if(cache_L2[index_L2][i].LRUStackBits == 1)
			{
				cache_L2[index_L2][i].data[offset_L2] = data; 
				cache_L2[index_L2][i].LRUStackBits = i+1;
				cache_L2[index_L2][i].tag = tag_L2;
			}
		}
		
		for(i=0;i<associativity_L2;i++)										//update lrubits							
		{
			cache_L2[index_L2][i].LRUStackBits = cache_L2[index_L2][i].LRUStackBits - 1;
			if(cache_L2[index_L2][i].LRUStackBits == 0)
			{
				cache_L2[index_L2][i].LRUStackBits = associativity_L2;
			}
		}
	}
	
	return 0;
}

int BaseCache::writeToL1(uint32_t addr, uint32_t data)
{
	unsigned int i, tagShift1 ,lruEmpty=0;
	offset_L1 = addr & (numBlocks_L1 - 1);					//numBlocks_L1, not original no. of bits as each position in array has 4B.
	uint32_t temp = addr >> offsetBits_L1;					// shifted by original bits to get index.
	index_L1 = (temp & (numLines_L1 - 1));
	tagShift1 = (log2(numLines_L1));
	tag_L1 = temp >> tagShift1;
	
	for(i=0;i<associativity_L1;i++)										//if LRU is empty. write to L1
	{
		if(cache_L1[index_L1][i].LRUStackBits == 0)
		{
			cache_L1[index_L1][i].data[offset_L1] = data; 
			cache_L1[index_L1][i].LRUStackBits = i+1;
			cache_L1[index_L1][i].tag = tag_L1;
			lruEmpty = 1;
			break;
		}
	}
	
	if(lruEmpty == 0)														//write L1 if lru not empty
	{
		for(i=0;i<associativity_L1;i++)										
		{
			if(cache_L1[index_L1][i].LRUStackBits == 1)
			{
				cache_L1[index_L1][i].data[offset_L1] = data; 
				cache_L1[index_L1][i].LRUStackBits = i+1;
				cache_L1[index_L1][i].tag = tag_L1;
			}
		}
		
		for(i=0;i<associativity_L1;i++)										//update lrubits							
		{
			cache_L1[index_L1][i].LRUStackBits = cache_L1[index_L1][i].LRUStackBits - 1;
			if(cache_L1[index_L1][i].LRUStackBits == 0)
			{
				cache_L1[index_L1][i].LRUStackBits = associativity_L1;
			}
		}
	}
	
	return 0;
}


//WRITE ME
//Destructor to free all allocated memeroy.
BaseCache::~BaseCache() {
}


