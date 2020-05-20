#include "ko_mem_pool.h"
#include <iostream>
#include <string>
#include <vector>

struct UserData {
    std::string str_data;
    size_t      num_data;
};

int main () {
    std::vector<UserData*> vec_other_usages;
    const size_t MAX_POOL = 10 ;
    KoMemPool<UserData, MAX_POOL> mem_pool;
    mem_pool.InitMemPool();
    for(size_t i = 0; i < MAX_POOL; i++){
        auto user_data = mem_pool.GetFromMemPool();
        user_data->str_data = std::to_string(i);
        user_data->num_data = i;
        vec_other_usages.push_back(user_data); 
    }
    //used elsewhere via vec_other_usages.
    std::cout << "all usages done, put back data";
    auto it_vec = vec_other_usages.begin();
    for(; it_vec != vec_other_usages.end(); ++it_vec){
        mem_pool.PutBackMemPool(*it_vec);
    }
    //debug pool
    for(size_t i = 0; i < MAX_POOL; i++){
        auto user_data = mem_pool.GetFromMemPool();
        std::cout << user_data->str_data 
            << "," << user_data->num_data << "\n" ;
        mem_pool.PutBackMemPool(user_data);
    }
    return 0;
}
