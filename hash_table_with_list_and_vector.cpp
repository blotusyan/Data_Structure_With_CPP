#include<iostream>
#include<list>
#include<vector>
template <typename K, typename V>
class Entry{
    private:
        K _key;
        V _val;
    public:
        Entry(const K key_, const V val_): _key(key_), _val(val_){}
        K getKey(){
            return this->_key;
        }
        V getValue(){
            return this->_val;
        }
        void setKey(const K key_){
            this->_key = key_;
        }
        void setValue(const V val_){
            this->_val = val_;
        }

};

template <typename K, typename V, typename H>
class HashMap{
    public:
        typedef Entry<K, V> Entry;

        //iterator
        class Iterator{
            private:
                EItor ent;
                BItor bkt;
                BkrArray* ba;
            public:
                Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor()): ent(q), bkt(b), ba(&a){}
                Entry& operator*(){
                    return *ent; //*EItor
                }
                bool operator==(const Iterator& p) const{ //diy operator overload
                    if (ba != p.ba || bkt != p.bkt) return false;
                    else if (bkt == ba->end()) return true;
                    else return (ent == p.ent);
                }
                Iterator& operator++(){
                    ++ent;
                    if (endOfBkt(*this)){
                        ++bkt;
                        while (bkt != ba->end() && bkt->empty()){
                            ++bkt;
                        }
                        if (bkt == ba->end()) return *this;
                        ent = blt->begin();
                    }
                    return *this;
                }
                friend class HashMap;
        };
        HashMap(int capacity = 100): n(0), B(capacity){}
        int size() const{
            return n;
        }
        bool empty() const{
            return n == 0;
        }
        Iterator find(const K& k){
            Iterator p = finder(k);
            if (endOfBkt(p)){
                return end();
            }
            return p;

        }
        Iterator put(const K& k, const V& v){
            Iterator p = finder(k);
            if (endOfBkt(p)){
                return inserter(p, Entry(k,v));
            }
            else{
                p.ent->setValue(v);
                return p;
            }
        }
        void erase(const K& k){
            Iterator& p = finder(k);
            if (endOfBkt(p)){
                //
            }
            erase(p);
        }
        void erase(const Iterator& p){
            eraser(p);
        }
        Iterator begin(){
            if (empty()) return end();
            BItor bkt = B.begin();
            while(bkt->empty()) ++bkt;
            return Iterator(B, bkt, bkt->begin());
        }
        Iterator end(){
            return Iterator(B, B.end());
        }
    protected:
        typedef std::list<Entry> Bucket;
        typedef std::vector<Bucket> BktArray;

        // utility functions
        Iterator finder(const K& k){
            int i = hash(k) % B.size();
            BItor bkt = B.begin() + i;
            Iterator p(B, bkt, bkt.begin());
            while (!endOfBkt(p) && *(p).key() != k){ //*p already overloaded
                nextEntry(p);
            }
            return p;
        }
        Iterator inserter(const Iterator& p, K& k, const Entry& e){
            EItor ins = p.bky->insert(p.ent, e);
            n++;
            return Iterator(B, p.bkt, ins);
        }
        void eraser(const Iterator& p){
            p.bkt->erase(p.ent);
            n--;
        }
        typedef typename BktArray::iterator BItor;
        typedef typename Bucket::iterator EItor;
        static void nextEntry(Iterator& p){
            ++p.ent;
        }
        static void endOfBkt(Iterator& p){
            return p.ent == p.bkt->end();
        }
    private:
        int n;
        H hash;
        BktArray B;

};