# KoMemPool
very very simple c++ memory pool


### Usage ###

see sample directory

```cpp
KoMemPool<UserData, 1000> mem_pool;
mem_pool.InitMemPool();

auto user_data = mem_pool.GetFromMemPool();

//use user data

mem_pool.PutBackMemPool(user_data);

```
