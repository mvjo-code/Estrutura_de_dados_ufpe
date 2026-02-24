#include <cassert>
#include <utility>
#include <iostream>

using namespace std;

using uint = unsigned int;
using ipair = pair<int, int>;

// ---------------------------------------------------------------------------
//  Hash Table Base
// ---------------------------------------------------------------------------

class HashTable {
public:
    using Status = enum {
        FREE,   
        BUSY,   
        DEAD    
    };

    struct HashEntry {
        Status status; 
        uint   key;     
        string value;   
        uint   dist;    
    };

    // Esta funcao precisa ser publica para o solver usar
    static uint HashKey(string const &value)
    {
        uint pow = 1;
        uint res = 0;
        for (int i = 0; i < (int)value.size(); i++) {
            res += (static_cast<uint>(value[i] - 'A') * pow);
            pow *= 26;
        }
        return res;
    }

protected:
    HashTable(uint initCap, uint aMin, uint aMax)
        : size(0), nUsed(0), minCap(initCap), cap(initCap), minLoad(aMin), maxLoad(aMax)
    {
        table = new HashEntry[cap];
        for (uint i = 0; i < cap; i++) {
            table[i].status = FREE;
        }
    }

    virtual ~HashTable() {
        delete[] table;
    }

    virtual void checkAndDouble() = 0;
    virtual void checkAndHalf() = 0;
    
    HashEntry *table;   
    uint minCap;        
    uint cap;           
    uint size;          
    uint nUsed;         
    uint minLoad;       
    uint maxLoad;       
    
public:
    virtual ipair add(string const &value) = 0;
    virtual ipair del(string const &value) = 0;
    virtual ipair get(string const &value) = 0;
};

// ---------------------------------------------------------------------------
// Linear Probing Hash Table
// ---------------------------------------------------------------------------

class LPHashTable: public HashTable { 
public:
    LPHashTable(uint initCap, uint minLoad, uint maxLoad):
        HashTable(initCap, minLoad, maxLoad)
    {
    }

    ipair add(string const &value) override {
        checkAndDouble();
        uint k = HashKey(value);
        uint d = 0;
        while (true) {
            uint idx = (k % cap + d) % cap;
            if (table[idx].status == FREE) {
                table[idx] = {BUSY, k, value, d};
                nUsed++;
                size++;
                return {(int)idx, (int)d};
            }
            d++;
        }
    }

    ipair del(string const &value) override {
        ipair res = get(value);
        if (res.first != -1) {
            table[res.first].status = DEAD;
            size--;
            checkAndHalf();
        }
        return res;
    }

    ipair get(string const &value) override {
        uint k = HashKey(value);
        uint d = 0;
        for (uint i = 0; i < cap; i++, d++) {
            uint idx = (k % cap + d) % cap;
            if (table[idx].status == FREE) return {-1, -1};
            if (table[idx].status == BUSY && table[idx].key == k) {
                return {(int)idx, (int)d};
            }
        }
        return {-1, -1};
    }

protected:
    virtual void checkAndDouble() override {
        if (100 * nUsed <= cap * maxLoad) return;
        
        uint oldCap = cap;
        HashEntry* oldTable = table;
        
        cap = oldCap * 2;
        table = new HashEntry[cap];
        for (uint i = 0; i < cap; i++) table[i].status = FREE;
        nUsed = 0;
        size = 0; 
        
        for (uint i = 0; i < oldCap; i++) {
            if (oldTable[i].status == BUSY) {
                uint k = oldTable[i].key;
                uint d = 0;
                while (true) {
                    uint idx = (k % cap + d) % cap;
                    if (table[idx].status == FREE) {
                        table[idx] = {BUSY, k, oldTable[i].value, d};
                        nUsed++; size++;
                        break;
                    }
                    d++;
                }
            }
        }
        delete[] oldTable;
    }

    virtual void checkAndHalf() override {
        if (cap == minCap || 100 * size >= cap * minLoad) return;
        
        uint oldCap = cap;
        HashEntry* oldTable = table;
        
        cap = oldCap / 2;
        if (cap < minCap) cap = minCap;
        
        table = new HashEntry[cap];
        for (uint i = 0; i < cap; i++) table[i].status = FREE;
        nUsed = 0;
        size = 0;
        
        for (uint i = 0; i < oldCap; i++) {
            if (oldTable[i].status == BUSY) {
                uint k = oldTable[i].key;
                uint d = 0;
                while (true) {
                    uint idx = (k % cap + d) % cap;
                    if (table[idx].status == FREE) {
                        table[idx] = {BUSY, k, oldTable[i].value, d};
                        nUsed++; size++;
                        break;
                    }
                    d++;
                }
            }
        }
        delete[] oldTable;
    }
};

// ----------------------------------------------------------------
// Robin Hood Hash Table
// ----------------------------------------------------------------

class RHHashTable: public HashTable {
public:
    RHHashTable(uint initCap, uint minLoad, uint maxLoad):
        HashTable(initCap, minLoad, maxLoad)
    {
    }

    ipair add(string const &value) override {
        checkAndDouble();
        uint k = HashKey(value);
        string v = value;
        uint d = 0;
        
        int resIdx = -1;
        int resDist = -1;
        
        while(true) {
            uint idx = (k % cap + d) % cap;
            
            if (table[idx].status == FREE) {
                table[idx] = {BUSY, k, v, d};
                nUsed++;
                size++;
                if (resIdx == -1) { resIdx = idx; resDist = d; }
                return {resIdx, resDist};
            }
            
            if (table[idx].status == BUSY) {
                if (d > table[idx].dist) {
                    if (resIdx == -1) { resIdx = idx; resDist = d; }
                    
                    uint tmpK = table[idx].key; table[idx].key = k; k = tmpK;
                    string tmpV = table[idx].value; table[idx].value = v; v = tmpV;
                    uint tmpD = table[idx].dist; table[idx].dist = d; d = tmpD;
                }
            }
            d++;
        }
    }

    ipair del(string const &value) override {
        ipair res = get(value);
        if (res.first != -1) {
            table[res.first].status = DEAD;
            size--;
            checkAndHalf();
        }
        return res;
    }

    ipair get(string const &value) override {
        uint k = HashKey(value);
        uint d = 0;
        
        for (uint i = 0; i < cap; i++, d++) {
            uint idx = (k % cap + d) % cap;
            
            if (table[idx].status == FREE) return {-1, -1};
            
            if (table[idx].status == BUSY) {
                 if (table[idx].key == k) return {(int)idx, (int)d};
                 if (table[idx].dist < d) return {-1, -1};
            }
        }
        return {-1, -1};
    }

protected:
    void insertInternal(HashEntry* t, uint c, uint k, string v) {
        uint d = 0;
        while(true) {
            uint idx = (k % c + d) % c;
            if (t[idx].status == FREE) {
                t[idx] = {BUSY, k, v, d};
                return;
            }
            if (t[idx].status == BUSY && d > t[idx].dist) {
                uint tmpK = t[idx].key; t[idx].key = k; k = tmpK;
                string tmpV = t[idx].value; t[idx].value = v; v = tmpV;
                uint tmpD = t[idx].dist; t[idx].dist = d; d = tmpD;
            }
            d++;
        }
    }

    virtual void checkAndDouble() override {
        if (100 * nUsed <= cap * maxLoad) return;
        
        uint oldCap = cap;
        HashEntry* oldTable = table;
        
        cap = oldCap * 2;
        table = new HashEntry[cap];
        for (uint i = 0; i < cap; i++) table[i].status = FREE;
        nUsed = 0; size = 0;
        
        for (uint i = 0; i < oldCap; i++) {
            if (oldTable[i].status == BUSY) {
                insertInternal(table, cap, oldTable[i].key, oldTable[i].value);
                nUsed++; size++;
            }
        }
        delete[] oldTable;
    }

    virtual void checkAndHalf() override {
        if (cap == minCap || 100 * size >= cap * minLoad) return;
        
        uint oldCap = cap;
        HashEntry* oldTable = table;
        
        cap = oldCap / 2;
        if (cap < minCap) cap = minCap;
        
        table = new HashEntry[cap];
        for (uint i = 0; i < cap; i++) table[i].status = FREE;
        nUsed = 0; size = 0;
        
        for (uint i = 0; i < oldCap; i++) {
            if (oldTable[i].status == BUSY) {
                insertInternal(table, cap, oldTable[i].key, oldTable[i].value);
                nUsed++; size++;
            }
        }
        delete[] oldTable;
    }
};