
#ifndef KO_MEW_POOL_H
#define KO_MEW_POOL_H

#include <cstddef>
#include <cstdlib>
#include <deque> 

////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t MAX_POOL_CNT>
class KoMemPool {
    public:
        ~KoMemPool() {
            ClearAllocMem();
        }
        //---------------------
        size_t GetSize(){
            return mem_pool_.size();
        }
        //---------------------
        bool InitMemPool(){
            for(size_t i=0; i < MAX_POOL_CNT ; i++){
                T* data = new (std::nothrow) T();
                if(data ==nullptr) {
                    return false;
                }
                mem_pool_.push_back(data);
            }
            return true;
        }
        //---------------------
        T* GetFromMemPool() {
            if(!mem_pool_.empty()){
                T* data = mem_pool_.front();
                mem_pool_.pop_front();
                return data;
            }else{
                //re-alloc start
                for(size_t i=0; i < (MAX_POOL_CNT / 2) ; i++){
                    T* alloc_data = new (std::nothrow) T();
                    if(alloc_data ==nullptr) {
                        return nullptr;
                    }
                    mem_pool_.push_back(alloc_data);
                }
                T* data = mem_pool_.front();
                mem_pool_.pop_front();
                return data;
            }
        }
        //---------------------
        void PutBackMemPool(T* data) {
            mem_pool_.push_back(data);
        }
    protected:
        //---------------------
        void ClearAllocMem(){
            auto it_del = mem_pool_.begin();
            for(; it_del != mem_pool_.end(); ++it_del){
                delete *it_del;
                *it_del = nullptr;
            }
            mem_pool_.clear();
        }
    protected:
        size_t max_pool_cnt_ = MAX_POOL_CNT ;
    private:    
        std::deque<T*> mem_pool_ ;
};

#endif // KO_MEW_POOL_H




