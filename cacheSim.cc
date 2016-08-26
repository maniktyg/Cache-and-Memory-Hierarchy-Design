#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BaseCache.h"
using namespace std;

int main(int argc, char **argv) {
    string inp_line, parsed_line, memfoot_line, mem_parsed;
    string command;
    unsigned int address, data;
	unsigned int mem_addr, mem_data;
    uint32_t cacheSize_L1, associativity_L1, blockSize_L1,cacheSize_L2, associativity_L2, blockSize_L2;
    cacheSize_L1 = atoi(argv[1]);
    associativity_L1 = atoi(argv[2]);
    blockSize_L1 = atoi(argv[3]);
	cacheSize_L2 = atoi(argv[4]);
    associativity_L2 = atoi(argv[5]);
    blockSize_L2 = atoi(argv[6]);
    ifstream fp_inp(argv[7]);
    
    BaseCache BaseCache(cacheSize_L1, associativity_L1, blockSize_L1,cacheSize_L2, associativity_L2, blockSize_L2);
	
	ifstream memfoot_inp;
	memfoot_inp.open("memfoot.dat");
	
	if(memfoot_inp.is_open())
	{
		while(getline(memfoot_inp, memfoot_line))
		{ 
			stringstream inp_mem(memfoot_line);
			if(getline(inp_mem,mem_parsed, ' '))
			{
				mem_addr = stoul(mem_parsed, NULL, 16);
			}	
			if(getline(inp_mem,mem_parsed, ' ')) 
			{
				mem_data = stoul(mem_parsed, NULL, 16);
			}	
			
			BaseCache.writeToMem(mem_addr, mem_data);
		}
		memfoot_inp.close();
	}
	
	

    if(fp_inp.is_open()) {
        while(getline(fp_inp, inp_line)) {
            stringstream inp_string(inp_line);
    	    if(getline(inp_string,parsed_line, ' ')) 
			command = parsed_line;
			if(getline(inp_string,parsed_line, ' ')) 
			address = stoul(parsed_line, NULL, 16);
			if (!(command.compare("w")))
			{
				if(getline(inp_string,parsed_line, ' ')) 
				{
					data = stoul(parsed_line, NULL, 16);
				}
			}
	   
			//Issue read/write command
			if (!(command.compare("w"))) 
			{ 
				(BaseCache.write(address, data));
				
			}
			
			if (!(command.compare("r"))) 
			{ 
				(BaseCache.read(address, &data));
				BaseCache.getMaxAccessTime();
				BaseCache.getMinAccessTime();
			}
        }
        fp_inp.close();
    }
    cout <<endl;
    cout << "L1 Read Hits (HitRate): "<<BaseCache.getReadHits_L1()<<" ("<<BaseCache.getReadHitRate_L1()<<"%)"<<endl;
    cout << "L1 Read Misses (MissRate): "<<BaseCache.getReadMisses_L1() <<" ("<<BaseCache.getReadMissRate_L1()<<"%)"<<endl;
    cout << "L1 Write Hits (HitRate): "<<BaseCache.getWriteHits_L1()<<" ("<<BaseCache.getWriteHitRate_L1()<<"%)"<<endl;
    cout << "L1 Write Misses (MissRate): "<<BaseCache.getWriteMisses_L1() <<" ("<<BaseCache.getWriteMissRate_L1()<<"%)"<<endl;
    cout << "L1 Overall Hit Rate: "<<BaseCache.getOverallHitRate_L1() <<"%" << endl;
    cout << "L1 Overall Miss Rate: "<<BaseCache.getOverallMissRate_L1()<<"%"<<endl;
	
	cout <<endl;
    cout << "L2 Read Hits (HitRate): "<<BaseCache.getReadHits_L2()<<" ("<<BaseCache.getReadHitRate_L2()<<"%)"<<endl;
    cout << "L2 Read Misses (MissRate): "<<BaseCache.getReadMisses_L2() <<" ("<<BaseCache.getReadMissRate_L2()<<"%)"<<endl;
    cout << "L2 Write Hits (HitRate): "<<BaseCache.getWriteHits_L2()<<" ("<<BaseCache.getWriteHitRate_L2()<<"%)"<<endl;
    cout << "L2 Write Misses (MissRate): "<<BaseCache.getWriteMisses_L2() <<" ("<<BaseCache.getWriteMissRate_L2()<<"%)"<<endl;
    cout << "L2 Overall Hit Rate: "<<BaseCache.getOverallHitRate_L2() <<"%" << endl;
    cout << "L2 Overall Miss Rate: "<<BaseCache.getOverallMissRate_L2()<<"%"<<endl;
	
	cout <<endl;
	cout << "Average memory access time (AMAT) (Reads): "<<BaseCache.getHitTime()<<"ns"<<endl;
	cout << "Minimum access time: "<<BaseCache.getMinAccessTime()<<"ns"<<endl;
	cout << "Maximum access time: "<<BaseCache.getMaxAccessTime()<<"ns"<<endl;
    return 1;
}
